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
typedef  int /*<<< orphan*/  spa_history_list_t ;
struct TYPE_3__ {int /*<<< orphan*/  pl_lock; int /*<<< orphan*/ * pl_private; } ;
typedef  TYPE_1__ procfs_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_txg_history_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_txg_history_clear(procfs_list_t *procfs_list)
{
	spa_history_list_t *shl = procfs_list->pl_private;
	mutex_enter(&procfs_list->pl_lock);
	spa_txg_history_truncate(shl, 0);
	mutex_exit(&procfs_list->pl_lock);
	return (0);
}