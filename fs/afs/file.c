/* AFS filesystem file handling
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/writeback.h>
#include <linux/gfp.h>
#include <linux/task_io_accounting_ops.h>
#include "internal.h"

static int afs_readpage(struct file *file, struct page *page);
static void afs_invalidatepage(struct page *page, unsigned int offset,
			       unsigned int length);
static int afs_releasepage(struct page *page, gfp_t gfp_flags);
static int afs_launder_page(struct page *page);

static int afs_readpages(struct file *filp, struct address_space *mapping,
			 struct list_head *pages, unsigned nr_pages);

const struct file_operations afs_file_operations = {
	.open		= afs_open,
	.flush		= afs_flush,
	.release	= afs_release,
	.llseek		= generic_file_llseek,
	.read_iter	= generic_file_read_iter,
	.write_iter	= afs_file_write,
	.mmap		= generic_file_readonly_mmap,
	.splice_read	= generic_file_splice_read,
	.fsync		= afs_fsync,
	.lock		= afs_lock,
	.flock		= afs_flock,
};

const struct inode_operations afs_file_inode_operations = {
	.getattr	= afs_getattr,
	.setattr	= afs_setattr,
	.permission	= afs_permission,
	.listxattr	= afs_listxattr,
};

const struct address_space_operations afs_fs_aops = {
	.readpage	= afs_readpage,
	.readpages	= afs_readpages,
	.set_page_dirty	= afs_set_page_dirty,
	.launder_page	= afs_launder_page,
	.releasepage	= afs_releasepage,
	.invalidatepage	= afs_invalidatepage,
	.write_begin	= afs_write_begin,
	.write_end	= afs_write_end,
	.writepage	= afs_writepage,
	.writepages	= afs_writepages,
};

/*
 * open an AFS file or directory and attach a key to it
 */
int afs_open(struct inode *inode, struct file *file)
{
	struct afs_vnode *vnode = AFS_FS_I(inode);
	struct key *key;
	int ret;

	_enter("{%x:%u},", vnode->fid.vid, vnode->fid.vnode);

	key = afs_request_key(vnode->volume->cell);
	if (IS_ERR(key)) {
		_leave(" = %ld [key]", PTR_ERR(key));
		return PTR_ERR(key);
	}

	ret = afs_validate(vnode, key);
	if (ret < 0) {
		_leave(" = %d [val]", ret);
		return ret;
	}

	file->private_data = key;
	_leave(" = 0");
	return 0;
}

/*
 * release an AFS file or directory and discard its key
 */
int afs_release(struct inode *inode, struct file *file)
{
	struct afs_vnode *vnode = AFS_FS_I(inode);

	_enter("{%x:%u},", vnode->fid.vid, vnode->fid.vnode);

	key_put(file->private_data);
	_leave(" = 0");
	return 0;
}

/*
 * Dispose of a ref to a read record.
 */
void afs_put_read(struct afs_read *req)
{
	int i;

	if (atomic_dec_and_test(&req->usage)) {
		for (i = 0; i < req->nr_pages; i++)
			if (req->pages[i])
				put_page(req->pages[i]);
		kfree(req);
	}
}

#ifdef CONFIG_AFS_FSCACHE
/*
 * deal with notification that a page was read from the cache
 */
static void afs_file_readpage_read_complete(struct page *page,
					    void *data,
					    int error)
{
	_enter("%p,%p,%d", page, data, error);

	/* if the read completes with an error, we just unlock the page and let
	 * the VM reissue the readpage */
	if (!error)
		SetPageUptodate(page);
	unlock_page(page);
}
#endif

/*
 * read page from file, directory or symlink, given a key to use
 */
<<<<<<< HEAD
static int __afs_page_filler(struct key *key, struct page *page)
=======
int afs_page_filler(void *data, struct page *page)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	struct inode *inode = page->mapping->host;
	struct afs_vnode *vnode = AFS_FS_I(inode);
	struct afs_read *req;
<<<<<<< HEAD
=======
	struct key *key = data;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	int ret;

	_enter("{%x},{%lu},{%lu}", key_serial(key), inode->i_ino, page->index);

	BUG_ON(!PageLocked(page));

	ret = -ESTALE;
	if (test_bit(AFS_VNODE_DELETED, &vnode->flags))
		goto error;

	/* is it cached? */
#ifdef CONFIG_AFS_FSCACHE
	ret = fscache_read_or_alloc_page(vnode->cache,
					 page,
					 afs_file_readpage_read_complete,
					 NULL,
					 GFP_KERNEL);
#else
	ret = -ENOBUFS;
#endif
	switch (ret) {
		/* read BIO submitted (page in cache) */
	case 0:
		break;

		/* page not yet cached */
	case -ENODATA:
		_debug("cache said ENODATA");
		goto go_on;

		/* page will not be cached */
	case -ENOBUFS:
		_debug("cache said ENOBUFS");
	default:
	go_on:
		req = kzalloc(sizeof(struct afs_read) + sizeof(struct page *),
			      GFP_KERNEL);
		if (!req)
			goto enomem;

		/* We request a full page.  If the page is a partial one at the
		 * end of the file, the server will return a short read and the
		 * unmarshalling code will clear the unfilled space.
		 */
		atomic_set(&req->usage, 1);
		req->pos = (loff_t)page->index << PAGE_SHIFT;
		req->len = PAGE_SIZE;
		req->nr_pages = 1;
		req->pages[0] = page;
		get_page(page);

		/* read the contents of the file from the server into the
		 * page */
		ret = afs_vnode_fetch_data(vnode, key, req);
		afs_put_read(req);
		if (ret < 0) {
			if (ret == -ENOENT) {
				_debug("got NOENT from server"
				       " - marking file deleted and stale");
				set_bit(AFS_VNODE_DELETED, &vnode->flags);
				ret = -ESTALE;
			}

#ifdef CONFIG_AFS_FSCACHE
			fscache_uncache_page(vnode->cache, page);
#endif
			BUG_ON(PageFsCache(page));

			if (ret == -EINTR ||
			    ret == -ENOMEM ||
			    ret == -ERESTARTSYS ||
			    ret == -EAGAIN)
				goto error;
			goto io_error;
		}

		SetPageUptodate(page);

		/* send the page to the cache */
#ifdef CONFIG_AFS_FSCACHE
		if (PageFsCache(page) &&
		    fscache_write_page(vnode->cache, page, GFP_KERNEL) != 0) {
			fscache_uncache_page(vnode->cache, page);
			BUG_ON(PageFsCache(page));
		}
#endif
		unlock_page(page);
	}

	_leave(" = 0");
	return 0;

io_error:
	SetPageError(page);
	goto error;
enomem:
	ret = -ENOMEM;
error:
	unlock_page(page);
	_leave(" = %d", ret);
	return ret;
}

<<<<<<< HEAD
int afs_page_filler(struct file *data, struct page *page)
{
	struct key *key = (struct key *)data;

	return __afs_page_filler(key, page);
}

=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
/*
 * read page from file, directory or symlink, given a file to nominate the key
 * to be used
 */
static int afs_readpage(struct file *file, struct page *page)
{
	struct key *key;
	int ret;

	if (file) {
		key = file->private_data;
		ASSERT(key != NULL);
<<<<<<< HEAD
		ret = __afs_page_filler(key, page);
=======
		ret = afs_page_filler(key, page);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	} else {
		struct inode *inode = page->mapping->host;
		key = afs_request_key(AFS_FS_S(inode->i_sb)->volume->cell);
		if (IS_ERR(key)) {
			ret = PTR_ERR(key);
		} else {
<<<<<<< HEAD
			ret = __afs_page_filler(key, page);
=======
			ret = afs_page_filler(key, page);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			key_put(key);
		}
	}
	return ret;
}

/*
 * Make pages available as they're filled.
 */
static void afs_readpages_page_done(struct afs_call *call, struct afs_read *req)
{
#ifdef CONFIG_AFS_FSCACHE
	struct afs_vnode *vnode = call->reply;
#endif
	struct page *page = req->pages[req->index];

	req->pages[req->index] = NULL;
	SetPageUptodate(page);

	/* send the page to the cache */
#ifdef CONFIG_AFS_FSCACHE
	if (PageFsCache(page) &&
	    fscache_write_page(vnode->cache, page, GFP_KERNEL) != 0) {
		fscache_uncache_page(vnode->cache, page);
		BUG_ON(PageFsCache(page));
	}
#endif
	unlock_page(page);
	put_page(page);
}

/*
 * Read a contiguous set of pages.
 */
static int afs_readpages_one(struct file *file, struct address_space *mapping,
			     struct list_head *pages)
{
	struct afs_vnode *vnode = AFS_FS_I(mapping->host);
	struct afs_read *req;
	struct list_head *p;
	struct page *first, *page;
	struct key *key = file->private_data;
	pgoff_t index;
	int ret, n, i;

	/* Count the number of contiguous pages at the front of the list.  Note
	 * that the list goes prev-wards rather than next-wards.
	 */
	first = list_entry(pages->prev, struct page, lru);
	index = first->index + 1;
	n = 1;
	for (p = first->lru.prev; p != pages; p = p->prev) {
		page = list_entry(p, struct page, lru);
		if (page->index != index)
			break;
		index++;
		n++;
	}

	req = kzalloc(sizeof(struct afs_read) + sizeof(struct page *) * n,
		      GFP_NOFS);
	if (!req)
		return -ENOMEM;

	atomic_set(&req->usage, 1);
	req->page_done = afs_readpages_page_done;
	req->pos = first->index;
	req->pos <<= PAGE_SHIFT;

	/* Transfer the pages to the request.  We add them in until one fails
	 * to add to the LRU and then we stop (as that'll make a hole in the
	 * contiguous run.
	 *
	 * Note that it's possible for the file size to change whilst we're
	 * doing this, but we rely on the server returning less than we asked
	 * for if the file shrank.  We also rely on this to deal with a partial
	 * page at the end of the file.
	 */
	do {
		page = list_entry(pages->prev, struct page, lru);
		list_del(&page->lru);
		index = page->index;
		if (add_to_page_cache_lru(page, mapping, index,
					  readahead_gfp_mask(mapping))) {
#ifdef CONFIG_AFS_FSCACHE
			fscache_uncache_page(vnode->cache, page);
#endif
			put_page(page);
			break;
		}

		req->pages[req->nr_pages++] = page;
		req->len += PAGE_SIZE;
	} while (req->nr_pages < n);

	if (req->nr_pages == 0) {
		kfree(req);
		return 0;
	}

	ret = afs_vnode_fetch_data(vnode, key, req);
	if (ret < 0)
		goto error;

	task_io_account_read(PAGE_SIZE * req->nr_pages);
	afs_put_read(req);
	return 0;

error:
	if (ret == -ENOENT) {
		_debug("got NOENT from server"
		       " - marking file deleted and stale");
		set_bit(AFS_VNODE_DELETED, &vnode->flags);
		ret = -ESTALE;
	}

	for (i = 0; i < req->nr_pages; i++) {
		page = req->pages[i];
		if (page) {
#ifdef CONFIG_AFS_FSCACHE
			fscache_uncache_page(vnode->cache, page);
#endif
			SetPageError(page);
			unlock_page(page);
		}
	}

	afs_put_read(req);
	return ret;
}

/*
 * read a set of pages
 */
static int afs_readpages(struct file *file, struct address_space *mapping,
			 struct list_head *pages, unsigned nr_pages)
{
	struct key *key = file->private_data;
	struct afs_vnode *vnode;
	int ret = 0;

	_enter("{%d},{%lu},,%d",
	       key_serial(key), mapping->host->i_ino, nr_pages);

	ASSERT(key != NULL);

	vnode = AFS_FS_I(mapping->host);
	if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		_leave(" = -ESTALE");
		return -ESTALE;
	}

	/* attempt to read as many of the pages as possible */
#ifdef CONFIG_AFS_FSCACHE
	ret = fscache_read_or_alloc_pages(vnode->cache,
					  mapping,
					  pages,
					  &nr_pages,
					  afs_file_readpage_read_complete,
					  NULL,
					  mapping_gfp_mask(mapping));
#else
	ret = -ENOBUFS;
#endif

	switch (ret) {
		/* all pages are being read from the cache */
	case 0:
		BUG_ON(!list_empty(pages));
		BUG_ON(nr_pages != 0);
		_leave(" = 0 [reading all]");
		return 0;

		/* there were pages that couldn't be read from the cache */
	case -ENODATA:
	case -ENOBUFS:
		break;

		/* other error */
	default:
		_leave(" = %d", ret);
		return ret;
	}

	while (!list_empty(pages)) {
		ret = afs_readpages_one(file, mapping, pages);
		if (ret < 0)
			break;
	}

	_leave(" = %d [netting]", ret);
	return ret;
}

/*
 * write back a dirty page
 */
static int afs_launder_page(struct page *page)
{
	_enter("{%lu}", page->index);

	return 0;
}

/*
 * invalidate part or all of a page
 * - release a page and clean up its private data if offset is 0 (indicating
 *   the entire page)
 */
static void afs_invalidatepage(struct page *page, unsigned int offset,
			       unsigned int length)
{
	struct afs_writeback *wb = (struct afs_writeback *) page_private(page);

	_enter("{%lu},%u,%u", page->index, offset, length);

	BUG_ON(!PageLocked(page));

	/* we clean up only if the entire page is being invalidated */
	if (offset == 0 && length == PAGE_SIZE) {
#ifdef CONFIG_AFS_FSCACHE
		if (PageFsCache(page)) {
			struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);
			fscache_wait_on_page_write(vnode->cache, page);
			fscache_uncache_page(vnode->cache, page);
		}
#endif

		if (PagePrivate(page)) {
			if (wb && !PageWriteback(page)) {
				set_page_private(page, 0);
				afs_put_writeback(wb);
			}

			if (!page_private(page))
				ClearPagePrivate(page);
		}
	}

	_leave("");
}

/*
 * release a page and clean up its private state if it's not busy
 * - return true if the page can now be released, false if not
 */
static int afs_releasepage(struct page *page, gfp_t gfp_flags)
{
	struct afs_writeback *wb = (struct afs_writeback *) page_private(page);
	struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);

	_enter("{{%x:%u}[%lu],%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, page->index, page->flags,
	       gfp_flags);

	/* deny if page is being written to the cache and the caller hasn't
	 * elected to wait */
#ifdef CONFIG_AFS_FSCACHE
	if (!fscache_maybe_release_page(vnode->cache, page, gfp_flags)) {
		_leave(" = F [cache busy]");
		return 0;
	}
#endif

	if (PagePrivate(page)) {
		if (wb) {
			set_page_private(page, 0);
			afs_put_writeback(wb);
		}
		ClearPagePrivate(page);
	}

	/* indicate that the page can be released */
	_leave(" = T");
	return 1;
}
