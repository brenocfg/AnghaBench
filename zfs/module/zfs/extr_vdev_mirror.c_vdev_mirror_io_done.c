#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ io_type; int io_flags; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_bp; int /*<<< orphan*/  io_txg; int /*<<< orphan*/  io_spa; void* io_error; int /*<<< orphan*/  io_priority; int /*<<< orphan*/ * io_vd; TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_13__ {int mm_children; TYPE_3__* mm_child; scalar_t__ mm_resilvering; } ;
typedef  TYPE_2__ mirror_map_t ;
struct TYPE_14__ {scalar_t__ mc_error; int /*<<< orphan*/  mc_offset; TYPE_6__* mc_vd; scalar_t__ mc_tried; int /*<<< orphan*/  mc_skipped; } ;
typedef  TYPE_3__ mirror_child_t ;
struct TYPE_15__ {int /*<<< orphan*/ * vdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTL_PARTIAL ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_IO_REPAIR ; 
 int ZIO_FLAG_RESILVER ; 
 int ZIO_FLAG_SCRUB ; 
 int ZIO_FLAG_SELF_HEAL ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_WRITE ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_dtl_contains (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_indirect_ops ; 
 int /*<<< orphan*/ * vdev_mirror_child_done ; 
 int vdev_mirror_child_select (TYPE_1__*) ; 
 void* vdev_mirror_worst_error (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vdev_child_io (TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zio_vdev_io_redone (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_mirror_io_done(zio_t *zio)
{
	mirror_map_t *mm = zio->io_vsd;
	mirror_child_t *mc;
	int c;
	int good_copies = 0;
	int unexpected_errors = 0;

	if (mm == NULL)
		return;

	for (c = 0; c < mm->mm_children; c++) {
		mc = &mm->mm_child[c];

		if (mc->mc_error) {
			if (!mc->mc_skipped)
				unexpected_errors++;
		} else if (mc->mc_tried) {
			good_copies++;
		}
	}

	if (zio->io_type == ZIO_TYPE_WRITE) {
		/*
		 * XXX -- for now, treat partial writes as success.
		 *
		 * Now that we support write reallocation, it would be better
		 * to treat partial failure as real failure unless there are
		 * no non-degraded top-level vdevs left, and not update DTLs
		 * if we intend to reallocate.
		 */
		/* XXPOLICY */
		if (good_copies != mm->mm_children) {
			/*
			 * Always require at least one good copy.
			 *
			 * For ditto blocks (io_vd == NULL), require
			 * all copies to be good.
			 *
			 * XXX -- for replacing vdevs, there's no great answer.
			 * If the old device is really dead, we may not even
			 * be able to access it -- so we only want to
			 * require good writes to the new device.  But if
			 * the new device turns out to be flaky, we want
			 * to be able to detach it -- which requires all
			 * writes to the old device to have succeeded.
			 */
			if (good_copies == 0 || zio->io_vd == NULL)
				zio->io_error = vdev_mirror_worst_error(mm);
		}
		return;
	}

	ASSERT(zio->io_type == ZIO_TYPE_READ);

	/*
	 * If we don't have a good copy yet, keep trying other children.
	 */
	/* XXPOLICY */
	if (good_copies == 0 && (c = vdev_mirror_child_select(zio)) != -1) {
		ASSERT(c >= 0 && c < mm->mm_children);
		mc = &mm->mm_child[c];
		zio_vdev_io_redone(zio);
		zio_nowait(zio_vdev_child_io(zio, zio->io_bp,
		    mc->mc_vd, mc->mc_offset, zio->io_abd, zio->io_size,
		    ZIO_TYPE_READ, zio->io_priority, 0,
		    vdev_mirror_child_done, mc));
		return;
	}

	/* XXPOLICY */
	if (good_copies == 0) {
		zio->io_error = vdev_mirror_worst_error(mm);
		ASSERT(zio->io_error != 0);
	}

	if (good_copies && spa_writeable(zio->io_spa) &&
	    (unexpected_errors ||
	    (zio->io_flags & ZIO_FLAG_RESILVER) ||
	    ((zio->io_flags & ZIO_FLAG_SCRUB) && mm->mm_resilvering))) {
		/*
		 * Use the good data we have in hand to repair damaged children.
		 */
		for (c = 0; c < mm->mm_children; c++) {
			/*
			 * Don't rewrite known good children.
			 * Not only is it unnecessary, it could
			 * actually be harmful: if the system lost
			 * power while rewriting the only good copy,
			 * there would be no good copies left!
			 */
			mc = &mm->mm_child[c];

			if (mc->mc_error == 0) {
				if (mc->mc_tried)
					continue;
				/*
				 * We didn't try this child.  We need to
				 * repair it if:
				 * 1. it's a scrub (in which case we have
				 * tried everything that was healthy)
				 *  - or -
				 * 2. it's an indirect vdev (in which case
				 * it could point to any other vdev, which
				 * might have a bad DTL)
				 *  - or -
				 * 3. the DTL indicates that this data is
				 * missing from this vdev
				 */
				if (!(zio->io_flags & ZIO_FLAG_SCRUB) &&
				    mc->mc_vd->vdev_ops != &vdev_indirect_ops &&
				    !vdev_dtl_contains(mc->mc_vd, DTL_PARTIAL,
				    zio->io_txg, 1))
					continue;
				mc->mc_error = SET_ERROR(ESTALE);
			}

			zio_nowait(zio_vdev_child_io(zio, zio->io_bp,
			    mc->mc_vd, mc->mc_offset,
			    zio->io_abd, zio->io_size,
			    ZIO_TYPE_WRITE, ZIO_PRIORITY_ASYNC_WRITE,
			    ZIO_FLAG_IO_REPAIR | (unexpected_errors ?
			    ZIO_FLAG_SELF_HEAL : 0), NULL, NULL));
		}
	}
}