#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_10__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_9__ {size_t vdev_children; int /*<<< orphan*/ ** vdev_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_ld_log_sm_data (TYPE_2__*) ; 
 int spa_ld_log_sm_metadata (TYPE_2__*) ; 
 int spa_ld_unflushed_txgs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_log_sm_set_blocklimit (TYPE_2__*) ; 

int
spa_ld_log_spacemaps(spa_t *spa)
{
	int error;

	spa_log_sm_set_blocklimit(spa);

	for (uint64_t c = 0; c < spa->spa_root_vdev->vdev_children; c++) {
		vdev_t *vd = spa->spa_root_vdev->vdev_child[c];
		error = spa_ld_unflushed_txgs(vd);
		if (error != 0)
			return (error);
	}

	error = spa_ld_log_sm_metadata(spa);
	if (error != 0)
		return (error);

	/*
	 * Note: we don't actually expect anything to change at this point
	 * but we grab the config lock so we don't fail any assertions
	 * when using vdev_lookup_top().
	 */
	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
	error = spa_ld_log_sm_data(spa);
	spa_config_exit(spa, SCL_CONFIG, FTAG);

	return (error);
}