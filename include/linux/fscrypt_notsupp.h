/* SPDX-License-Identifier: GPL-2.0 */
/*
 * fscrypt_notsupp.h
 *
 * This stubs out the fscrypt functions for filesystems configured without
 * encryption support.
<<<<<<< HEAD
 *
 * Do not include this file directly. Use fscrypt.h instead!
 */
#ifndef _LINUX_FSCRYPT_H
#error "Incorrect include of linux/fscrypt_notsupp.h!"
#endif
=======
 */
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

#ifndef _LINUX_FSCRYPT_NOTSUPP_H
#define _LINUX_FSCRYPT_NOTSUPP_H

<<<<<<< HEAD
static inline bool fscrypt_has_encryption_key(const struct inode *inode)
{
	return false;
}

static inline bool fscrypt_dummy_context_enabled(struct inode *inode)
{
	return false;
}

/* crypto.c */
static inline void fscrypt_enqueue_decrypt_work(struct work_struct *work)
{
}

=======
#include <linux/fscrypt_common.h>

/* crypto.c */
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
static inline struct fscrypt_ctx *fscrypt_get_ctx(const struct inode *inode,
						  gfp_t gfp_flags)
{
	return ERR_PTR(-EOPNOTSUPP);
}

static inline void fscrypt_release_ctx(struct fscrypt_ctx *ctx)
{
	return;
}

static inline struct page *fscrypt_encrypt_page(const struct inode *inode,
						struct page *page,
						unsigned int len,
						unsigned int offs,
						u64 lblk_num, gfp_t gfp_flags)
{
	return ERR_PTR(-EOPNOTSUPP);
}

static inline int fscrypt_decrypt_page(const struct inode *inode,
				       struct page *page,
				       unsigned int len, unsigned int offs,
				       u64 lblk_num)
{
	return -EOPNOTSUPP;
}

<<<<<<< HEAD
static inline struct page *fscrypt_control_page(struct page *page)
{
	WARN_ON_ONCE(1);
	return ERR_PTR(-EINVAL);
}

static inline void fscrypt_restore_control_page(struct page *page)
=======

static inline void fscrypt_restore_control_page(struct page *page)
{
	return;
}

static inline void fscrypt_set_d_op(struct dentry *dentry)
{
	return;
}

static inline void fscrypt_set_encrypted_dentry(struct dentry *dentry)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	return;
}

/* policy.c */
static inline int fscrypt_ioctl_set_policy(struct file *filp,
					   const void __user *arg)
{
	return -EOPNOTSUPP;
}

static inline int fscrypt_ioctl_get_policy(struct file *filp, void __user *arg)
{
	return -EOPNOTSUPP;
}

static inline int fscrypt_has_permitted_context(struct inode *parent,
						struct inode *child)
{
	return 0;
}

static inline int fscrypt_inherit_context(struct inode *parent,
					  struct inode *child,
					  void *fs_data, bool preload)
{
	return -EOPNOTSUPP;
}

/* keyinfo.c */
static inline int fscrypt_get_encryption_info(struct inode *inode)
{
	return -EOPNOTSUPP;
}

<<<<<<< HEAD
static inline void fscrypt_put_encryption_info(struct inode *inode)
=======
static inline void fscrypt_put_encryption_info(struct inode *inode,
					       struct fscrypt_info *ci)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	return;
}

 /* fname.c */
static inline int fscrypt_setup_filename(struct inode *dir,
					 const struct qstr *iname,
					 int lookup, struct fscrypt_name *fname)
{
<<<<<<< HEAD
	if (IS_ENCRYPTED(dir))
=======
	if (dir->i_sb->s_cop->is_encrypted(dir))
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		return -EOPNOTSUPP;

	memset(fname, 0, sizeof(struct fscrypt_name));
	fname->usr_fname = iname;
	fname->disk_name.name = (unsigned char *)iname->name;
	fname->disk_name.len = iname->len;
	return 0;
}

static inline void fscrypt_free_filename(struct fscrypt_name *fname)
{
	return;
}

<<<<<<< HEAD
static inline int fscrypt_fname_alloc_buffer(const struct inode *inode,
					     u32 max_encrypted_len,
=======
static inline u32 fscrypt_fname_encrypted_size(const struct inode *inode,
					       u32 ilen)
{
	/* never happens */
	WARN_ON(1);
	return 0;
}

static inline int fscrypt_fname_alloc_buffer(const struct inode *inode,
					     u32 ilen,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
					     struct fscrypt_str *crypto_str)
{
	return -EOPNOTSUPP;
}

static inline void fscrypt_fname_free_buffer(struct fscrypt_str *crypto_str)
{
	return;
}

static inline int fscrypt_fname_disk_to_usr(struct inode *inode,
					    u32 hash, u32 minor_hash,
					    const struct fscrypt_str *iname,
					    struct fscrypt_str *oname)
{
	return -EOPNOTSUPP;
}

<<<<<<< HEAD
=======
static inline int fscrypt_fname_usr_to_disk(struct inode *inode,
					    const struct qstr *iname,
					    struct fscrypt_str *oname)
{
	return -EOPNOTSUPP;
}

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
static inline bool fscrypt_match_name(const struct fscrypt_name *fname,
				      const u8 *de_name, u32 de_name_len)
{
	/* Encryption support disabled; use standard comparison */
	if (de_name_len != fname->disk_name.len)
		return false;
	return !memcmp(de_name, fname->disk_name.name, fname->disk_name.len);
}

/* bio.c */
<<<<<<< HEAD
static inline void fscrypt_decrypt_bio(struct bio *bio)
{
}

static inline void fscrypt_enqueue_decrypt_bio(struct fscrypt_ctx *ctx,
					       struct bio *bio)
{
=======
static inline void fscrypt_decrypt_bio_pages(struct fscrypt_ctx *ctx,
					     struct bio *bio)
{
	return;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static inline void fscrypt_pullback_bio_page(struct page **page, bool restore)
{
	return;
}

static inline int fscrypt_zeroout_range(const struct inode *inode, pgoff_t lblk,
					sector_t pblk, unsigned int len)
{
	return -EOPNOTSUPP;
}

<<<<<<< HEAD
/* hooks.c */

static inline int fscrypt_file_open(struct inode *inode, struct file *filp)
{
	if (IS_ENCRYPTED(inode))
		return -EOPNOTSUPP;
	return 0;
}

static inline int __fscrypt_prepare_link(struct inode *inode,
					 struct inode *dir)
{
	return -EOPNOTSUPP;
}

static inline int __fscrypt_prepare_rename(struct inode *old_dir,
					   struct dentry *old_dentry,
					   struct inode *new_dir,
					   struct dentry *new_dentry,
					   unsigned int flags)
{
	return -EOPNOTSUPP;
}

static inline int __fscrypt_prepare_lookup(struct inode *dir,
					   struct dentry *dentry)
{
	return -EOPNOTSUPP;
}

static inline int __fscrypt_prepare_symlink(struct inode *dir,
					    unsigned int len,
					    unsigned int max_len,
					    struct fscrypt_str *disk_link)
{
	return -EOPNOTSUPP;
}

static inline int __fscrypt_encrypt_symlink(struct inode *inode,
					    const char *target,
					    unsigned int len,
					    struct fscrypt_str *disk_link)
{
	return -EOPNOTSUPP;
}

static inline const char *fscrypt_get_symlink(struct inode *inode,
					      const void *caddr,
					      unsigned int max_size,
					      struct delayed_call *done)
{
	return ERR_PTR(-EOPNOTSUPP);
}

=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif	/* _LINUX_FSCRYPT_NOTSUPP_H */
