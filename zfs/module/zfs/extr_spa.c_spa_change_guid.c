#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  spa_vdev_top_lock; int /*<<< orphan*/  spa_name; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ESC_ZFS_POOL_REGUID ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_change_guid_check ; 
 int /*<<< orphan*/  spa_change_guid_sync ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_generate_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_write_cachefile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spa_change_guid(spa_t *spa)
{
	int error;
	uint64_t guid;

	mutex_enter(&spa->spa_vdev_top_lock);
	mutex_enter(&spa_namespace_lock);
	guid = spa_generate_guid(NULL);

	error = dsl_sync_task(spa->spa_name, spa_change_guid_check,
	    spa_change_guid_sync, &guid, 5, ZFS_SPACE_CHECK_RESERVED);

	if (error == 0) {
		spa_write_cachefile(spa, B_FALSE, B_TRUE);
		spa_event_notify(spa, NULL, NULL, ESC_ZFS_POOL_REGUID);
	}

	mutex_exit(&spa_namespace_lock);
	mutex_exit(&spa->spa_vdev_top_lock);

	return (error);
}