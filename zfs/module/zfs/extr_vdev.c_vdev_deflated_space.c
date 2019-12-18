#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int vdev_deflate_ratio; scalar_t__ vdev_isl2cache; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SPA_MINBLOCKSHIFT ; 
 int SPA_MINBLOCKSIZE ; 

int64_t
vdev_deflated_space(vdev_t *vd, int64_t space)
{
	ASSERT((space & (SPA_MINBLOCKSIZE-1)) == 0);
	ASSERT(vd->vdev_deflate_ratio != 0 || vd->vdev_isl2cache);

	return ((space >> SPA_MINBLOCKSHIFT) * vd->vdev_deflate_ratio);
}