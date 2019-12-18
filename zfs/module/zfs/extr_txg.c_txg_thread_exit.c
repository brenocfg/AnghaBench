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
struct TYPE_3__ {int /*<<< orphan*/  tx_exit_cv; int /*<<< orphan*/  tx_threads; } ;
typedef  TYPE_1__ tx_state_t ;
typedef  int /*<<< orphan*/  kthread_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALLB_CPR_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
txg_thread_exit(tx_state_t *tx, callb_cpr_t *cpr, kthread_t **tpp)
{
	ASSERT(*tpp != NULL);
	*tpp = NULL;
	tx->tx_threads--;
	cv_broadcast(&tx->tx_exit_cv);
	CALLB_CPR_EXIT(cpr);		/* drops &tx->tx_sync_lock */
	thread_exit();
}