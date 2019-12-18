#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tx_commit_cb_taskq; } ;
typedef  TYPE_1__ tx_state_t ;
struct TYPE_5__ {TYPE_1__ dp_tx; } ;
typedef  TYPE_2__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskq_wait_outstanding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
txg_wait_callbacks(dsl_pool_t *dp)
{
	tx_state_t *tx = &dp->dp_tx;

	if (tx->tx_commit_cb_taskq != NULL)
		taskq_wait_outstanding(tx->tx_commit_cb_taskq, 0);
}