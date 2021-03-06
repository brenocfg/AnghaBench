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
struct TYPE_3__ {int /*<<< orphan*/  spa_import_flags; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IMPORT_SKIP_MMP ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* spa_lookup (char*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 

__attribute__((used)) static void
zdb_set_skip_mmp(char *target)
{
	spa_t *spa;

	/*
	 * Disable the activity check to allow examination of
	 * active pools.
	 */
	mutex_enter(&spa_namespace_lock);
	if ((spa = spa_lookup(target)) != NULL) {
		spa->spa_import_flags |= ZFS_IMPORT_SKIP_MMP;
	}
	mutex_exit(&spa_namespace_lock);
}