#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_ms_shift; int vdev_ashift; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  range_seg_type_t ;
struct TYPE_6__ {int ms_start; } ;
typedef  TYPE_2__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_SEG32 ; 
 int /*<<< orphan*/  RANGE_SEG64 ; 
 int /*<<< orphan*/  zfs_metaslab_force_large_segs ; 

__attribute__((used)) static range_seg_type_t
metaslab_calculate_range_tree_type(vdev_t *vdev, metaslab_t *msp,
    uint64_t *start, uint64_t *shift)
{
	if (vdev->vdev_ms_shift - vdev->vdev_ashift < 32 &&
	    !zfs_metaslab_force_large_segs) {
		*shift = vdev->vdev_ashift;
		*start = msp->ms_start;
		return (RANGE_SEG32);
	} else {
		*shift = 0;
		*start = 0;
		return (RANGE_SEG64);
	}
}