#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ vs_space; scalar_t__ vs_dspace; } ;
struct TYPE_15__ {TYPE_1__ vdev_stat; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_16__ {scalar_t__ spa_dspace; TYPE_2__* spa_vdev_removal; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_14__ {int /*<<< orphan*/  svr_vdev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 scalar_t__ ddt_get_dedup_dspace (TYPE_4__*) ; 
 scalar_t__ metaslab_class_get_dspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_deflate (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_4__*) ; 
 TYPE_3__* vdev_lookup_top (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
spa_update_dspace(spa_t *spa)
{
	spa->spa_dspace = metaslab_class_get_dspace(spa_normal_class(spa)) +
	    ddt_get_dedup_dspace(spa);
	if (spa->spa_vdev_removal != NULL) {
		/*
		 * We can't allocate from the removing device, so
		 * subtract its size.  This prevents the DMU/DSL from
		 * filling up the (now smaller) pool while we are in the
		 * middle of removing the device.
		 *
		 * Note that the DMU/DSL doesn't actually know or care
		 * how much space is allocated (it does its own tracking
		 * of how much space has been logically used).  So it
		 * doesn't matter that the data we are moving may be
		 * allocated twice (on the old device and the new
		 * device).
		 */
		spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);
		vdev_t *vd =
		    vdev_lookup_top(spa, spa->spa_vdev_removal->svr_vdev_id);
		spa->spa_dspace -= spa_deflate(spa) ?
		    vd->vdev_stat.vs_dspace : vd->vdev_stat.vs_space;
		spa_config_exit(spa, SCL_VDEV, FTAG);
	}
}