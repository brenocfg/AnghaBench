#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vdev_children; unsigned long long vdev_ms_shift; scalar_t__ vdev_asize; scalar_t__ vdev_max_asize; TYPE_2__* vdev_mg; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {TYPE_3__* mg_class; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_10__ {TYPE_5__* mc_spa; } ;
typedef  TYPE_3__ metaslab_class_t ;
struct TYPE_11__ {TYPE_1__* spa_root_vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ P2ALIGN (scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_1__*) ; 

uint64_t
metaslab_class_expandable_space(metaslab_class_t *mc)
{
	vdev_t *rvd = mc->mc_spa->spa_root_vdev;
	uint64_t space = 0;

	spa_config_enter(mc->mc_spa, SCL_VDEV, FTAG, RW_READER);
	for (int c = 0; c < rvd->vdev_children; c++) {
		vdev_t *tvd = rvd->vdev_child[c];
		metaslab_group_t *mg = tvd->vdev_mg;

		if (!vdev_is_concrete(tvd) || tvd->vdev_ms_shift == 0 ||
		    mg->mg_class != mc) {
			continue;
		}

		/*
		 * Calculate if we have enough space to add additional
		 * metaslabs. We report the expandable space in terms
		 * of the metaslab size since that's the unit of expansion.
		 */
		space += P2ALIGN(tvd->vdev_max_asize - tvd->vdev_asize,
		    1ULL << tvd->vdev_ms_shift);
	}
	spa_config_exit(mc->mc_spa, SCL_VDEV, FTAG);
	return (space);
}