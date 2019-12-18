#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {scalar_t__ pool_guid; scalar_t__ pool_name; } ;
typedef  TYPE_2__ spa_import_progress_t ;
struct TYPE_10__ {int /*<<< orphan*/  pl_lock; int /*<<< orphan*/  pl_list; } ;
struct TYPE_12__ {TYPE_1__ procfs_list; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 TYPE_2__* list_prev (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_3__* spa_import_progress_list ; 
 int /*<<< orphan*/  spa_strfree (scalar_t__) ; 

void
spa_import_progress_remove(uint64_t pool_guid)
{
	spa_history_list_t *shl = spa_import_progress_list;
	spa_import_progress_t *sip;

	mutex_enter(&shl->procfs_list.pl_lock);
	for (sip = list_tail(&shl->procfs_list.pl_list); sip != NULL;
	    sip = list_prev(&shl->procfs_list.pl_list, sip)) {
		if (sip->pool_guid == pool_guid) {
			if (sip->pool_name)
				spa_strfree(sip->pool_name);
			list_remove(&shl->procfs_list.pl_list, sip);
			shl->size--;
			kmem_free(sip, sizeof (spa_import_progress_t));
			break;
		}
	}
	mutex_exit(&shl->procfs_list.pl_lock);
}