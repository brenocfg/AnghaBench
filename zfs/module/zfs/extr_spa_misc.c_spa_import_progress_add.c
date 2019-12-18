#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  spa_config; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_load_state; int /*<<< orphan*/  pool_name; int /*<<< orphan*/  pool_guid; } ;
typedef  TYPE_2__ spa_import_progress_t ;
struct TYPE_15__ {int /*<<< orphan*/  pl_lock; } ;
struct TYPE_14__ {TYPE_9__ procfs_list; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  procfs_list_add (TYPE_9__*,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_guid (TYPE_1__*) ; 
 TYPE_3__* spa_import_progress_list ; 
 int /*<<< orphan*/  spa_load_state (TYPE_1__*) ; 
 char* spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_strdup (char*) ; 

void
spa_import_progress_add(spa_t *spa)
{
	spa_history_list_t *shl = spa_import_progress_list;
	spa_import_progress_t *sip;
	char *poolname = NULL;

	sip = kmem_zalloc(sizeof (spa_import_progress_t), KM_SLEEP);
	sip->pool_guid = spa_guid(spa);

	(void) nvlist_lookup_string(spa->spa_config, ZPOOL_CONFIG_POOL_NAME,
	    &poolname);
	if (poolname == NULL)
		poolname = spa_name(spa);
	sip->pool_name = spa_strdup(poolname);
	sip->spa_load_state = spa_load_state(spa);

	mutex_enter(&shl->procfs_list.pl_lock);
	procfs_list_add(&shl->procfs_list, sip);
	shl->size++;
	mutex_exit(&shl->procfs_list.pl_lock);
}