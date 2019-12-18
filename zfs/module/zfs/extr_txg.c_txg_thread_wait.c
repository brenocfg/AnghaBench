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
struct TYPE_3__ {int /*<<< orphan*/  tx_sync_lock; } ;
typedef  TYPE_1__ tx_state_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLB_CPR_SAFE_BEGIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLB_CPR_SAFE_END (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ddi_get_lbolt () ; 

__attribute__((used)) static void
txg_thread_wait(tx_state_t *tx, callb_cpr_t *cpr, kcondvar_t *cv, clock_t time)
{
	CALLB_CPR_SAFE_BEGIN(cpr);

	/*
	 * cv_wait_sig() is used instead of cv_wait() in order to prevent
	 * this process from incorrectly contributing to the system load
	 * average when idle.
	 */
	if (time) {
		(void) cv_timedwait_sig(cv, &tx->tx_sync_lock,
		    ddi_get_lbolt() + time);
	} else {
		cv_wait_sig(cv, &tx->tx_sync_lock);
	}

	CALLB_CPR_SAFE_END(cpr, &tx->tx_sync_lock);
}