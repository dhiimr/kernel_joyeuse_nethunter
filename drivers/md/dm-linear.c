/*
 * Copyright (C) 2001-2003 Sistina Software (UK) Limited.
 *
 * This file is released under the GPL.
 */

#include "dm.h"
#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/bio.h>
#include <linux/dax.h>
#include <linux/slab.h>
#include <linux/device-mapper.h>

#define DM_MSG_PREFIX "linear"

/*
 * Linear: maps a linear range of a device.
 */
struct linear_c {
	struct dm_dev *dev;
	sector_t start;
};

/*
 * Construct a linear mapping: <dev_path> <offset>
 */
<<<<<<< HEAD
int dm_linear_ctr(struct dm_target *ti, unsigned int argc, char **argv)
=======
static int linear_ctr(struct dm_target *ti, unsigned int argc, char **argv)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	struct linear_c *lc;
	unsigned long long tmp;
	char dummy;
	int ret;

	if (argc != 2) {
		ti->error = "Invalid argument count";
		return -EINVAL;
	}

	lc = kmalloc(sizeof(*lc), GFP_KERNEL);
	if (lc == NULL) {
		ti->error = "Cannot allocate linear context";
		return -ENOMEM;
	}

	ret = -EINVAL;
	if (sscanf(argv[1], "%llu%c", &tmp, &dummy) != 1) {
		ti->error = "Invalid device sector";
		goto bad;
	}
	lc->start = tmp;

	ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &lc->dev);
	if (ret) {
		ti->error = "Device lookup failed";
		goto bad;
	}

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_write_same_bios = 1;
	ti->num_write_zeroes_bios = 1;
	ti->private = lc;
	return 0;

      bad:
	kfree(lc);
	return ret;
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_ctr);

void dm_linear_dtr(struct dm_target *ti)
=======

static void linear_dtr(struct dm_target *ti)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	struct linear_c *lc = (struct linear_c *) ti->private;

	dm_put_device(ti, lc->dev);
	kfree(lc);
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_dtr);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

static sector_t linear_map_sector(struct dm_target *ti, sector_t bi_sector)
{
	struct linear_c *lc = ti->private;

	return lc->start + dm_target_offset(ti, bi_sector);
}

static void linear_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct linear_c *lc = ti->private;

	bio_set_dev(bio, lc->dev->bdev);
	if (bio_sectors(bio) || bio_op(bio) == REQ_OP_ZONE_RESET)
		bio->bi_iter.bi_sector =
			linear_map_sector(ti, bio->bi_iter.bi_sector);
}

<<<<<<< HEAD
int dm_linear_map(struct dm_target *ti, struct bio *bio)
=======
static int linear_map(struct dm_target *ti, struct bio *bio)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	linear_map_bio(ti, bio);

	return DM_MAPIO_REMAPPED;
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_map);

int dm_linear_end_io(struct dm_target *ti, struct bio *bio,
=======

#ifdef CONFIG_BLK_DEV_ZONED
static int linear_end_io(struct dm_target *ti, struct bio *bio,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			 blk_status_t *error)
{
	struct linear_c *lc = ti->private;

	if (!*error && bio_op(bio) == REQ_OP_ZONE_REPORT)
		dm_remap_zone_report(ti, bio, lc->start);

	return DM_ENDIO_DONE;
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_end_io);

void dm_linear_status(struct dm_target *ti, status_type_t type,
=======
#endif

static void linear_status(struct dm_target *ti, status_type_t type,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			  unsigned status_flags, char *result, unsigned maxlen)
{
	struct linear_c *lc = (struct linear_c *) ti->private;

	switch (type) {
	case STATUSTYPE_INFO:
		result[0] = '\0';
		break;

	case STATUSTYPE_TABLE:
		snprintf(result, maxlen, "%s %llu", lc->dev->name,
				(unsigned long long)lc->start);
		break;
	}
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_status);

int dm_linear_prepare_ioctl(struct dm_target *ti,
=======

static int linear_prepare_ioctl(struct dm_target *ti,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		struct block_device **bdev, fmode_t *mode)
{
	struct linear_c *lc = (struct linear_c *) ti->private;
	struct dm_dev *dev = lc->dev;

	*bdev = dev->bdev;

	/*
	 * Only pass ioctls through if the device sizes match exactly.
	 */
	if (lc->start ||
	    ti->len != i_size_read(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		return 1;
	return 0;
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_prepare_ioctl);

int dm_linear_iterate_devices(struct dm_target *ti,
=======

static int linear_iterate_devices(struct dm_target *ti,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
				  iterate_devices_callout_fn fn, void *data)
{
	struct linear_c *lc = ti->private;

	return fn(ti, lc->dev, lc->start, ti->len, data);
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_iterate_devices);

long dm_linear_dax_direct_access(struct dm_target *ti, pgoff_t pgoff,
=======

static long linear_dax_direct_access(struct dm_target *ti, pgoff_t pgoff,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		long nr_pages, void **kaddr, pfn_t *pfn)
{
	long ret;
	struct linear_c *lc = ti->private;
	struct block_device *bdev = lc->dev->bdev;
	struct dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	ret = bdev_dax_pgoff(bdev, dev_sector, nr_pages * PAGE_SIZE, &pgoff);
	if (ret)
		return ret;
	return dax_direct_access(dax_dev, pgoff, nr_pages, kaddr, pfn);
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_dax_direct_access);

size_t dm_linear_dax_copy_from_iter(struct dm_target *ti, pgoff_t pgoff,
=======

static size_t linear_dax_copy_from_iter(struct dm_target *ti, pgoff_t pgoff,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		void *addr, size_t bytes, struct iov_iter *i)
{
	struct linear_c *lc = ti->private;
	struct block_device *bdev = lc->dev->bdev;
	struct dax_device *dax_dev = lc->dev->dax_dev;
	sector_t dev_sector, sector = pgoff * PAGE_SECTORS;

	dev_sector = linear_map_sector(ti, sector);
	if (bdev_dax_pgoff(bdev, dev_sector, ALIGN(bytes, PAGE_SIZE), &pgoff))
		return 0;
	return dax_copy_from_iter(dax_dev, pgoff, addr, bytes, i);
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dm_linear_dax_copy_from_iter);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

static struct target_type linear_target = {
	.name   = "linear",
	.version = {1, 4, 0},
<<<<<<< HEAD
	.features = DM_TARGET_PASSES_INTEGRITY | DM_TARGET_ZONED_HM,
	.module = THIS_MODULE,
	.ctr    = dm_linear_ctr,
	.dtr    = dm_linear_dtr,
	.map    = dm_linear_map,
	.status = dm_linear_status,
	.end_io = dm_linear_end_io,
	.prepare_ioctl = dm_linear_prepare_ioctl,
	.iterate_devices = dm_linear_iterate_devices,
	.direct_access = dm_linear_dax_direct_access,
	.dax_copy_from_iter = dm_linear_dax_copy_from_iter,
=======
#ifdef CONFIG_BLK_DEV_ZONED
	.end_io = linear_end_io,
	.features = DM_TARGET_PASSES_INTEGRITY | DM_TARGET_ZONED_HM,
#else
	.features = DM_TARGET_PASSES_INTEGRITY,
#endif
	.module = THIS_MODULE,
	.ctr    = linear_ctr,
	.dtr    = linear_dtr,
	.map    = linear_map,
	.status = linear_status,
	.prepare_ioctl = linear_prepare_ioctl,
	.iterate_devices = linear_iterate_devices,
	.direct_access = linear_dax_direct_access,
	.dax_copy_from_iter = linear_dax_copy_from_iter,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

int __init dm_linear_init(void)
{
	int r = dm_register_target(&linear_target);

	if (r < 0)
		DMERR("register failed %d", r);

	return r;
}

void dm_linear_exit(void)
{
	dm_unregister_target(&linear_target);
}
