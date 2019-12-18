#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vdev_ashift; int vdev_deflate_ratio; int /*<<< orphan*/  vdev_ishole; struct TYPE_4__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int SPA_MINBLOCKSHIFT ; 
 int vdev_psize_to_asize (TYPE_1__*,int) ; 

__attribute__((used)) static void
vdev_set_deflate_ratio(vdev_t *vd)
{
	if (vd == vd->vdev_top && !vd->vdev_ishole && vd->vdev_ashift != 0) {
		vd->vdev_deflate_ratio = (1 << 17) /
		    (vdev_psize_to_asize(vd, 1 << 17) >> SPA_MINBLOCKSHIFT);
	}
}