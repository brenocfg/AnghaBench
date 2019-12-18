#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * times; int /*<<< orphan*/  state; int /*<<< orphan*/  txg; } ;
typedef  TYPE_2__ spa_txg_history_t ;
struct TYPE_14__ {int /*<<< orphan*/  pl_lock; } ;
struct TYPE_13__ {scalar_t__ size; TYPE_7__ procfs_list; } ;
struct TYPE_10__ {TYPE_4__ txg_history; } ;
struct TYPE_12__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_4__ spa_history_list_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 size_t TXG_STATE_BIRTH ; 
 int /*<<< orphan*/  TXG_STATE_OPEN ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_list_add (TYPE_7__*,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_txg_history_truncate (TYPE_4__*,scalar_t__) ; 
 scalar_t__ zfs_txg_history ; 

void
spa_txg_history_add(spa_t *spa, uint64_t txg, hrtime_t birth_time)
{
	spa_history_list_t *shl = &spa->spa_stats.txg_history;
	spa_txg_history_t *sth;

	if (zfs_txg_history == 0 && shl->size == 0)
		return;

	sth = kmem_zalloc(sizeof (spa_txg_history_t), KM_SLEEP);
	sth->txg = txg;
	sth->state = TXG_STATE_OPEN;
	sth->times[TXG_STATE_BIRTH] = birth_time;

	mutex_enter(&shl->procfs_list.pl_lock);
	procfs_list_add(&shl->procfs_list, sth);
	shl->size++;
	spa_txg_history_truncate(shl, zfs_txg_history);
	mutex_exit(&shl->procfs_list.pl_lock);
}