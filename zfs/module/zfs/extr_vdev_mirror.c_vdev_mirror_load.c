#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ vdev_nonrot; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ mm_root; } ;
typedef  TYPE_3__ mirror_map_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 scalar_t__ ABS (scalar_t__) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  MIRROR_BUMP (int /*<<< orphan*/ ) ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 int /*<<< orphan*/  vdev_mirror_stat_non_rotating_linear ; 
 int /*<<< orphan*/  vdev_mirror_stat_non_rotating_seek ; 
 int /*<<< orphan*/  vdev_mirror_stat_rotating_linear ; 
 int /*<<< orphan*/  vdev_mirror_stat_rotating_offset ; 
 int /*<<< orphan*/  vdev_mirror_stat_rotating_seek ; 
 scalar_t__ vdev_queue_last_offset (TYPE_2__*) ; 
 int vdev_queue_length (TYPE_2__*) ; 
 int zfs_vdev_mirror_non_rotating_inc ; 
 int zfs_vdev_mirror_non_rotating_seek_inc ; 
 int zfs_vdev_mirror_rotating_inc ; 
 int zfs_vdev_mirror_rotating_seek_inc ; 
 scalar_t__ zfs_vdev_mirror_rotating_seek_offset ; 

__attribute__((used)) static int
vdev_mirror_load(mirror_map_t *mm, vdev_t *vd, uint64_t zio_offset)
{
	uint64_t last_offset;
	int64_t offset_diff;
	int load;

	/* All DVAs have equal weight at the root. */
	if (mm->mm_root)
		return (INT_MAX);

	/*
	 * We don't return INT_MAX if the device is resilvering i.e.
	 * vdev_resilver_txg != 0 as when tested performance was slightly
	 * worse overall when resilvering with compared to without.
	 */

	/* Fix zio_offset for leaf vdevs */
	if (vd->vdev_ops->vdev_op_leaf)
		zio_offset += VDEV_LABEL_START_SIZE;

	/* Standard load based on pending queue length. */
	load = vdev_queue_length(vd);
	last_offset = vdev_queue_last_offset(vd);

	if (vd->vdev_nonrot) {
		/* Non-rotating media. */
		if (last_offset == zio_offset) {
			MIRROR_BUMP(vdev_mirror_stat_non_rotating_linear);
			return (load + zfs_vdev_mirror_non_rotating_inc);
		}

		/*
		 * Apply a seek penalty even for non-rotating devices as
		 * sequential I/O's can be aggregated into fewer operations on
		 * the device, thus avoiding unnecessary per-command overhead
		 * and boosting performance.
		 */
		MIRROR_BUMP(vdev_mirror_stat_non_rotating_seek);
		return (load + zfs_vdev_mirror_non_rotating_seek_inc);
	}

	/* Rotating media I/O's which directly follow the last I/O. */
	if (last_offset == zio_offset) {
		MIRROR_BUMP(vdev_mirror_stat_rotating_linear);
		return (load + zfs_vdev_mirror_rotating_inc);
	}

	/*
	 * Apply half the seek increment to I/O's within seek offset
	 * of the last I/O issued to this vdev as they should incur less
	 * of a seek increment.
	 */
	offset_diff = (int64_t)(last_offset - zio_offset);
	if (ABS(offset_diff) < zfs_vdev_mirror_rotating_seek_offset) {
		MIRROR_BUMP(vdev_mirror_stat_rotating_offset);
		return (load + (zfs_vdev_mirror_rotating_seek_inc / 2));
	}

	/* Apply the full seek increment to all other I/O's. */
	MIRROR_BUMP(vdev_mirror_stat_rotating_seek);
	return (load + zfs_vdev_mirror_rotating_seek_inc);
}