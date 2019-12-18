#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_space_check_t ;
typedef  int /*<<< orphan*/  txg_list_t ;
typedef  int /*<<< orphan*/  dsl_syncfunc_t ;
struct TYPE_6__ {int dst_space; int /*<<< orphan*/  dst_txg; int /*<<< orphan*/  dst_nowaiter; scalar_t__ dst_error; void* dst_arg; int /*<<< orphan*/ * dst_syncfunc; int /*<<< orphan*/  dst_checkfunc; int /*<<< orphan*/  dst_space_check; TYPE_2__* dst_pool; } ;
typedef  TYPE_1__ dsl_sync_task_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_sync_tasks; int /*<<< orphan*/  dp_early_sync_tasks; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int DST_AVG_BLKSHIFT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_null_checkfunc ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_list_add_tail (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_sync_task_nowait_common(dsl_pool_t *dp, dsl_syncfunc_t *syncfunc, void *arg,
    int blocks_modified, zfs_space_check_t space_check, dmu_tx_t *tx,
    boolean_t early)
{
	dsl_sync_task_t *dst = kmem_zalloc(sizeof (*dst), KM_SLEEP);

	dst->dst_pool = dp;
	dst->dst_txg = dmu_tx_get_txg(tx);
	dst->dst_space = blocks_modified << DST_AVG_BLKSHIFT;
	dst->dst_space_check = space_check;
	dst->dst_checkfunc = dsl_null_checkfunc;
	dst->dst_syncfunc = syncfunc;
	dst->dst_arg = arg;
	dst->dst_error = 0;
	dst->dst_nowaiter = B_TRUE;

	txg_list_t *task_list = (early) ?
	    &dp->dp_early_sync_tasks : &dp->dp_sync_tasks;
	VERIFY(txg_list_add_tail(task_list, dst, dst->dst_txg));
}