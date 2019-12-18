#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  CALLB_CPR_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLB_CPR_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALLB_CPR_SAFE_BEGIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLB_CPR_SAFE_END (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MSEC2NSEC (int) ; 
 int /*<<< orphan*/  SEC2NSEC (int) ; 
 int /*<<< orphan*/  callb_generic_cpr ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_timedwait_sig_hires (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dbuf_cache_above_lowater () ; 
 int /*<<< orphan*/  dbuf_evict_cv ; 
 int /*<<< orphan*/  dbuf_evict_lock ; 
 int /*<<< orphan*/  dbuf_evict_one () ; 
 scalar_t__ dbuf_evict_thread_exit ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
dbuf_evict_thread(void *unused)
{
	callb_cpr_t cpr;

	CALLB_CPR_INIT(&cpr, &dbuf_evict_lock, callb_generic_cpr, FTAG);

	mutex_enter(&dbuf_evict_lock);
	while (!dbuf_evict_thread_exit) {
		while (!dbuf_cache_above_lowater() && !dbuf_evict_thread_exit) {
			CALLB_CPR_SAFE_BEGIN(&cpr);
			(void) cv_timedwait_sig_hires(&dbuf_evict_cv,
			    &dbuf_evict_lock, SEC2NSEC(1), MSEC2NSEC(1), 0);
			CALLB_CPR_SAFE_END(&cpr, &dbuf_evict_lock);
		}
		mutex_exit(&dbuf_evict_lock);

		/*
		 * Keep evicting as long as we're above the low water mark
		 * for the cache. We do this without holding the locks to
		 * minimize lock contention.
		 */
		while (dbuf_cache_above_lowater() && !dbuf_evict_thread_exit) {
			dbuf_evict_one();
		}

		mutex_enter(&dbuf_evict_lock);
	}

	dbuf_evict_thread_exit = B_FALSE;
	cv_broadcast(&dbuf_evict_cv);
	CALLB_CPR_EXIT(&cpr);	/* drops dbuf_evict_lock */
	thread_exit();
}