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
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ spa_config_guid; scalar_t__ spa_last_synced_guid; TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_5__ {scalar_t__ vdev_guid; } ;

/* Variables and functions */
 scalar_t__ dsl_pool_sync_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_get_dsl (TYPE_2__*) ; 

uint64_t
spa_guid(spa_t *spa)
{
	dsl_pool_t *dp = spa_get_dsl(spa);
	uint64_t guid;

	/*
	 * If we fail to parse the config during spa_load(), we can go through
	 * the error path (which posts an ereport) and end up here with no root
	 * vdev.  We stash the original pool guid in 'spa_config_guid' to handle
	 * this case.
	 */
	if (spa->spa_root_vdev == NULL)
		return (spa->spa_config_guid);

	guid = spa->spa_last_synced_guid != 0 ?
	    spa->spa_last_synced_guid : spa->spa_root_vdev->vdev_guid;

	/*
	 * Return the most recently synced out guid unless we're
	 * in syncing context.
	 */
	if (dp && dsl_pool_sync_context(dp))
		return (spa->spa_root_vdev->vdev_guid);
	else
		return (guid);
}