#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t vdev_children; int /*<<< orphan*/ * vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_5__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  vdev_is_spacemap_addressable (int /*<<< orphan*/ ) ; 

boolean_t
spa_top_vdevs_spacemap_addressable(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;
	for (uint64_t c = 0; c < rvd->vdev_children; c++) {
		if (!vdev_is_spacemap_addressable(rvd->vdev_child[c]))
			return (B_FALSE);
	}
	return (B_TRUE);
}