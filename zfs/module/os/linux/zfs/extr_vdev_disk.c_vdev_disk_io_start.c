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
struct TYPE_11__ {int io_error; int io_type; int io_trim_flags; int io_offset; int io_size; int /*<<< orphan*/  io_target_timestamp; int /*<<< orphan*/  io_cmd; TYPE_2__* io_vd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_12__ {int /*<<< orphan*/  vdev_nowritecache; TYPE_3__* vdev_tsd; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_13__ {int /*<<< orphan*/  vd_lock; int /*<<< orphan*/ * vd_bdev; } ;
typedef  TYPE_3__ vdev_disk_t ;

/* Variables and functions */
 unsigned long BLKDEV_DISCARD_SECURE ; 
#define  DKIOCFLUSHWRITECACHE 132 
 void* ENOTSUP ; 
 void* ENXIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int READ ; 
 int /*<<< orphan*/  RW_READER ; 
 void* SET_ERROR (void*) ; 
 int WRITE ; 
 int ZIO_TRIM_SECURE ; 
#define  ZIO_TYPE_IOCTL 131 
#define  ZIO_TYPE_READ 130 
#define  ZIO_TYPE_TRIM 129 
#define  ZIO_TYPE_WRITE 128 
 int __vdev_disk_physio (int /*<<< orphan*/ *,TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int blkdev_issue_discard (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int vdev_disk_io_flush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_readable (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_nocacheflush ; 
 int /*<<< orphan*/  zio_execute (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_handle_io_delay (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_interrupt (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_disk_io_start(zio_t *zio)
{
	vdev_t *v = zio->io_vd;
	vdev_disk_t *vd = v->vdev_tsd;
	unsigned long trim_flags = 0;
	int rw, error;

	/*
	 * If the vdev is closed, it's likely in the REMOVED or FAULTED state.
	 * Nothing to be done here but return failure.
	 */
	if (vd == NULL) {
		zio->io_error = ENXIO;
		zio_interrupt(zio);
		return;
	}

	rw_enter(&vd->vd_lock, RW_READER);

	/*
	 * If the vdev is closed, it's likely due to a failed reopen and is
	 * in the UNAVAIL state.  Nothing to be done here but return failure.
	 */
	if (vd->vd_bdev == NULL) {
		rw_exit(&vd->vd_lock);
		zio->io_error = ENXIO;
		zio_interrupt(zio);
		return;
	}

	switch (zio->io_type) {
	case ZIO_TYPE_IOCTL:

		if (!vdev_readable(v)) {
			rw_exit(&vd->vd_lock);
			zio->io_error = SET_ERROR(ENXIO);
			zio_interrupt(zio);
			return;
		}

		switch (zio->io_cmd) {
		case DKIOCFLUSHWRITECACHE:

			if (zfs_nocacheflush)
				break;

			if (v->vdev_nowritecache) {
				zio->io_error = SET_ERROR(ENOTSUP);
				break;
			}

			error = vdev_disk_io_flush(vd->vd_bdev, zio);
			if (error == 0) {
				rw_exit(&vd->vd_lock);
				return;
			}

			zio->io_error = error;

			break;

		default:
			zio->io_error = SET_ERROR(ENOTSUP);
		}

		rw_exit(&vd->vd_lock);
		zio_execute(zio);
		return;
	case ZIO_TYPE_WRITE:
		rw = WRITE;
		break;

	case ZIO_TYPE_READ:
		rw = READ;
		break;

	case ZIO_TYPE_TRIM:
#if defined(BLKDEV_DISCARD_SECURE)
		if (zio->io_trim_flags & ZIO_TRIM_SECURE)
			trim_flags |= BLKDEV_DISCARD_SECURE;
#endif
		zio->io_error = -blkdev_issue_discard(vd->vd_bdev,
		    zio->io_offset >> 9, zio->io_size >> 9, GFP_NOFS,
		    trim_flags);

		rw_exit(&vd->vd_lock);
		zio_interrupt(zio);
		return;

	default:
		rw_exit(&vd->vd_lock);
		zio->io_error = SET_ERROR(ENOTSUP);
		zio_interrupt(zio);
		return;
	}

	zio->io_target_timestamp = zio_handle_io_delay(zio);
	error = __vdev_disk_physio(vd->vd_bdev, zio,
	    zio->io_size, zio->io_offset, rw, 0);
	rw_exit(&vd->vd_lock);

	if (error) {
		zio->io_error = error;
		zio_interrupt(zio);
		return;
	}
}