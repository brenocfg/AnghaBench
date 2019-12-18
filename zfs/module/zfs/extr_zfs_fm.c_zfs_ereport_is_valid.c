#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ io_type; scalar_t__ io_error; int /*<<< orphan*/  io_timestamp; int /*<<< orphan*/  io_txg; TYPE_3__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_14__ {scalar_t__ vdev_state; scalar_t__ vdev_remove_wanted; TYPE_1__* vdev_ops; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_15__ {scalar_t__ spa_last_open_failed; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DTL_MISSING ; 
 scalar_t__ ECKSUM ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_DELAY ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_PROBE_FAILURE ; 
 scalar_t__ SPA_LOAD_NONE ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 scalar_t__ VDEV_STATE_REMOVED ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 scalar_t__ spa_load_state (TYPE_4__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_accessible (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ vdev_dtl_contains (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

boolean_t
zfs_ereport_is_valid(const char *subclass, spa_t *spa, vdev_t *vd, zio_t *zio)
{
#ifdef _KERNEL
	/*
	 * If we are doing a spa_tryimport() or in recovery mode,
	 * ignore errors.
	 */
	if (spa_load_state(spa) == SPA_LOAD_TRYIMPORT ||
	    spa_load_state(spa) == SPA_LOAD_RECOVER)
		return (B_FALSE);

	/*
	 * If we are in the middle of opening a pool, and the previous attempt
	 * failed, don't bother logging any new ereports - we're just going to
	 * get the same diagnosis anyway.
	 */
	if (spa_load_state(spa) != SPA_LOAD_NONE &&
	    spa->spa_last_open_failed)
		return (B_FALSE);

	if (zio != NULL) {
		/*
		 * If this is not a read or write zio, ignore the error.  This
		 * can occur if the DKIOCFLUSHWRITECACHE ioctl fails.
		 */
		if (zio->io_type != ZIO_TYPE_READ &&
		    zio->io_type != ZIO_TYPE_WRITE)
			return (B_FALSE);

		if (vd != NULL) {
			/*
			 * If the vdev has already been marked as failing due
			 * to a failed probe, then ignore any subsequent I/O
			 * errors, as the DE will automatically fault the vdev
			 * on the first such failure.  This also catches cases
			 * where vdev_remove_wanted is set and the device has
			 * not yet been asynchronously placed into the REMOVED
			 * state.
			 */
			if (zio->io_vd == vd && !vdev_accessible(vd, zio))
				return (B_FALSE);

			/*
			 * Ignore checksum errors for reads from DTL regions of
			 * leaf vdevs.
			 */
			if (zio->io_type == ZIO_TYPE_READ &&
			    zio->io_error == ECKSUM &&
			    vd->vdev_ops->vdev_op_leaf &&
			    vdev_dtl_contains(vd, DTL_MISSING, zio->io_txg, 1))
				return (B_FALSE);
		}
	}

	/*
	 * For probe failure, we want to avoid posting ereports if we've
	 * already removed the device in the meantime.
	 */
	if (vd != NULL &&
	    strcmp(subclass, FM_EREPORT_ZFS_PROBE_FAILURE) == 0 &&
	    (vd->vdev_remove_wanted || vd->vdev_state == VDEV_STATE_REMOVED))
		return (B_FALSE);

	/* Ignore bogus delay events (like from ioctls or unqueued IOs) */
	if ((strcmp(subclass, FM_EREPORT_ZFS_DELAY) == 0) &&
	    (zio != NULL) && (!zio->io_timestamp)) {
		return (B_FALSE);
	}
#endif
	return (B_TRUE);
}