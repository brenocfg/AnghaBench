#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_load_state_t ;
struct TYPE_9__ {scalar_t__ pool_guid; int /*<<< orphan*/  spa_load_state; } ;
typedef  TYPE_2__ spa_import_progress_t ;
struct TYPE_8__ {int /*<<< orphan*/  pl_lock; int /*<<< orphan*/  pl_list; } ;
struct TYPE_10__ {scalar_t__ size; TYPE_1__ procfs_list; } ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_2__* list_prev (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_3__* spa_import_progress_list ; 

int
spa_import_progress_set_state(uint64_t pool_guid,
    spa_load_state_t load_state)
{
	spa_history_list_t *shl = spa_import_progress_list;
	spa_import_progress_t *sip;
	int error = ENOENT;

	if (shl->size == 0)
		return (0);

	mutex_enter(&shl->procfs_list.pl_lock);
	for (sip = list_tail(&shl->procfs_list.pl_list); sip != NULL;
	    sip = list_prev(&shl->procfs_list.pl_list, sip)) {
		if (sip->pool_guid == pool_guid) {
			sip->spa_load_state = load_state;
			error = 0;
			break;
		}
	}
	mutex_exit(&shl->procfs_list.pl_lock);

	return (error);
}