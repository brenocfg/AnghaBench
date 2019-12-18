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
struct TYPE_5__ {size_t vdev_children; scalar_t__ vdev_ms_count; struct TYPE_5__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_6__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_is_concrete (TYPE_1__*) ; 

uint64_t
spa_total_metaslabs(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;

	uint64_t m = 0;
	for (uint64_t c = 0; c < rvd->vdev_children; c++) {
		vdev_t *vd = rvd->vdev_child[c];
		if (!vdev_is_concrete(vd))
			continue;
		m += vd->vdev_ms_count;
	}
	return (m);
}