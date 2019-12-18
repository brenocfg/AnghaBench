#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct request_queue {int dummy; } ;
struct block_device {int dummy; } ;
struct bio {int /*<<< orphan*/ * bi_private; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_flush (struct bio*) ; 
 int /*<<< orphan*/  invalidate_bdev (struct block_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_disk_io_flush_completion ; 
 int /*<<< orphan*/  vdev_submit_bio (struct bio*) ; 

__attribute__((used)) static int
vdev_disk_io_flush(struct block_device *bdev, zio_t *zio)
{
	struct request_queue *q;
	struct bio *bio;

	q = bdev_get_queue(bdev);
	if (!q)
		return (SET_ERROR(ENXIO));

	bio = bio_alloc(GFP_NOIO, 0);
	/* bio_alloc() with __GFP_WAIT never returns NULL */
	if (unlikely(bio == NULL))
		return (SET_ERROR(ENOMEM));

	bio->bi_end_io = vdev_disk_io_flush_completion;
	bio->bi_private = zio;
	bio_set_dev(bio, bdev);
	bio_set_flush(bio);
	vdev_submit_bio(bio);
	invalidate_bdev(bdev);

	return (0);
}