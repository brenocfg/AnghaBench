#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t vdev_children; scalar_t__ vdev_islog; struct TYPE_6__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_7__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 scalar_t__ vdev_is_concrete (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_1__*) ; 

__attribute__((used)) static uint64_t
spa_healthy_core_tvds(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;
	uint64_t tvds = 0;

	for (uint64_t i = 0; i < rvd->vdev_children; i++) {
		vdev_t *vd = rvd->vdev_child[i];
		if (vd->vdev_islog)
			continue;
		if (vdev_is_concrete(vd) && !vdev_is_dead(vd))
			tvds++;
	}

	return (tvds);
}