#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ io_type; int io_flags; int /*<<< orphan*/  io_priority; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; int /*<<< orphan*/ * io_bp; int /*<<< orphan*/  io_spa; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_12__ {int mm_children; TYPE_3__* mm_child; int /*<<< orphan*/  mm_resilvering; } ;
typedef  TYPE_2__ mirror_map_t ;
struct TYPE_13__ {int /*<<< orphan*/  mc_offset; int /*<<< orphan*/  mc_vd; } ;
typedef  TYPE_3__ mirror_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ZIO_FLAG_SCRUB ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  abd_alloc_sametype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_trust_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_mirror_child_done ; 
 int vdev_mirror_child_select (TYPE_1__*) ; 
 TYPE_2__* vdev_mirror_map_init (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_mirror_scrub_done ; 
 int /*<<< orphan*/  zio_execute (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vdev_child_io (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
vdev_mirror_io_start(zio_t *zio)
{
	mirror_map_t *mm;
	mirror_child_t *mc;
	int c, children;

	mm = vdev_mirror_map_init(zio);

	if (mm == NULL) {
		ASSERT(!spa_trust_config(zio->io_spa));
		ASSERT(zio->io_type == ZIO_TYPE_READ);
		zio_execute(zio);
		return;
	}

	if (zio->io_type == ZIO_TYPE_READ) {
		if (zio->io_bp != NULL &&
		    (zio->io_flags & ZIO_FLAG_SCRUB) && !mm->mm_resilvering) {
			/*
			 * For scrubbing reads (if we can verify the
			 * checksum here, as indicated by io_bp being
			 * non-NULL) we need to allocate a read buffer for
			 * each child and issue reads to all children.  If
			 * any child succeeds, it will copy its data into
			 * zio->io_data in vdev_mirror_scrub_done.
			 */
			for (c = 0; c < mm->mm_children; c++) {
				mc = &mm->mm_child[c];
				zio_nowait(zio_vdev_child_io(zio, zio->io_bp,
				    mc->mc_vd, mc->mc_offset,
				    abd_alloc_sametype(zio->io_abd,
				    zio->io_size), zio->io_size,
				    zio->io_type, zio->io_priority, 0,
				    vdev_mirror_scrub_done, mc));
			}
			zio_execute(zio);
			return;
		}
		/*
		 * For normal reads just pick one child.
		 */
		c = vdev_mirror_child_select(zio);
		children = (c >= 0);
	} else {
		ASSERT(zio->io_type == ZIO_TYPE_WRITE);

		/*
		 * Writes go to all children.
		 */
		c = 0;
		children = mm->mm_children;
	}

	while (children--) {
		mc = &mm->mm_child[c];
		zio_nowait(zio_vdev_child_io(zio, zio->io_bp,
		    mc->mc_vd, mc->mc_offset, zio->io_abd, zio->io_size,
		    zio->io_type, zio->io_priority, 0,
		    vdev_mirror_child_done, mc));
		c++;
	}

	zio_execute(zio);
}