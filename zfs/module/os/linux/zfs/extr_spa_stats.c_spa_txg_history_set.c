#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t txg_state_t ;
struct TYPE_12__ {scalar_t__ txg; int /*<<< orphan*/  state; int /*<<< orphan*/ * times; } ;
typedef  TYPE_3__ spa_txg_history_t ;
struct TYPE_11__ {int /*<<< orphan*/  pl_lock; int /*<<< orphan*/  pl_list; } ;
struct TYPE_14__ {TYPE_2__ procfs_list; } ;
struct TYPE_10__ {TYPE_5__ txg_history; } ;
struct TYPE_13__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_4__ spa_t ;
typedef  TYPE_5__ spa_history_list_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_3__* list_prev (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_txg_history ; 

int
spa_txg_history_set(spa_t *spa, uint64_t txg, txg_state_t completed_state,
    hrtime_t completed_time)
{
	spa_history_list_t *shl = &spa->spa_stats.txg_history;
	spa_txg_history_t *sth;
	int error = ENOENT;

	if (zfs_txg_history == 0)
		return (0);

	mutex_enter(&shl->procfs_list.pl_lock);
	for (sth = list_tail(&shl->procfs_list.pl_list); sth != NULL;
	    sth = list_prev(&shl->procfs_list.pl_list, sth)) {
		if (sth->txg == txg) {
			sth->times[completed_state] = completed_time;
			sth->state++;
			error = 0;
			break;
		}
	}
	mutex_exit(&shl->procfs_list.pl_lock);

	return (error);
}