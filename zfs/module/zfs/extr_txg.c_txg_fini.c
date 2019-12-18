#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* tx_cpu; int /*<<< orphan*/ * tx_commit_cb_taskq; int /*<<< orphan*/  tx_exit_cv; int /*<<< orphan*/  tx_quiesce_done_cv; int /*<<< orphan*/  tx_quiesce_more_cv; int /*<<< orphan*/  tx_sync_done_cv; int /*<<< orphan*/  tx_sync_more_cv; int /*<<< orphan*/  tx_sync_lock; int /*<<< orphan*/  tx_threads; } ;
typedef  TYPE_1__ tx_state_t ;
typedef  int /*<<< orphan*/  tx_cpu_t ;
struct TYPE_7__ {TYPE_1__ dp_tx; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/ * tc_callbacks; int /*<<< orphan*/ * tc_cv; int /*<<< orphan*/  tc_lock; int /*<<< orphan*/  tc_open_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int max_ncpus ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_free (TYPE_3__*,int) ; 

void
txg_fini(dsl_pool_t *dp)
{
	tx_state_t *tx = &dp->dp_tx;
	int c;

	ASSERT0(tx->tx_threads);

	mutex_destroy(&tx->tx_sync_lock);

	cv_destroy(&tx->tx_sync_more_cv);
	cv_destroy(&tx->tx_sync_done_cv);
	cv_destroy(&tx->tx_quiesce_more_cv);
	cv_destroy(&tx->tx_quiesce_done_cv);
	cv_destroy(&tx->tx_exit_cv);

	for (c = 0; c < max_ncpus; c++) {
		int i;

		mutex_destroy(&tx->tx_cpu[c].tc_open_lock);
		mutex_destroy(&tx->tx_cpu[c].tc_lock);
		for (i = 0; i < TXG_SIZE; i++) {
			cv_destroy(&tx->tx_cpu[c].tc_cv[i]);
			list_destroy(&tx->tx_cpu[c].tc_callbacks[i]);
		}
	}

	if (tx->tx_commit_cb_taskq != NULL)
		taskq_destroy(tx->tx_commit_cb_taskq);

	vmem_free(tx->tx_cpu, max_ncpus * sizeof (tx_cpu_t));

	bzero(tx, sizeof (tx_state_t));
}