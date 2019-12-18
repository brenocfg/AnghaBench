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
typedef  int /*<<< orphan*/  zthr_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* ks_update ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KSTAT_READ ; 
 int /*<<< orphan*/  arc_adjust_needed ; 
 int /*<<< orphan*/  arc_initialized ; 
 TYPE_1__* arc_ksp ; 
 int /*<<< orphan*/  arc_tuning_update () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
arc_adjust_cb_check(void *arg, zthr_t *zthr)
{
	if (!arc_initialized)
		return (B_FALSE);

	/*
	 * This is necessary so that any changes which may have been made to
	 * many of the zfs_arc_* module parameters will be propagated to
	 * their actual internal variable counterparts. Without this,
	 * changing those module params at runtime would have no effect.
	 */
	arc_tuning_update();

	/*
	 * This is necessary in order to keep the kstat information
	 * up to date for tools that display kstat data such as the
	 * mdb ::arc dcmd and the Linux crash utility.  These tools
	 * typically do not call kstat's update function, but simply
	 * dump out stats from the most recent update.  Without
	 * this call, these commands may show stale stats for the
	 * anon, mru, mru_ghost, mfu, and mfu_ghost lists. Even
	 * with this change, the data might be up to 1 second
	 * out of date(the arc_adjust_zthr has a maximum sleep
	 * time of 1 second); but that should suffice.  The
	 * arc_state_t structures can be queried directly if more
	 * accurate information is needed.
	 */
	if (arc_ksp != NULL)
		arc_ksp->ks_update(arc_ksp, KSTAT_READ);

	/*
	 * We have to rely on arc_get_data_impl() to tell us when to adjust,
	 * rather than checking if we are overflowing here, so that we are
	 * sure to not leave arc_get_data_impl() waiting on
	 * arc_adjust_waiters_cv.  If we have become "not overflowing" since
	 * arc_get_data_impl() checked, we need to wake it up.  We could
	 * broadcast the CV here, but arc_get_data_impl() may have not yet
	 * gone to sleep.  We would need to use a mutex to ensure that this
	 * function doesn't broadcast until arc_get_data_impl() has gone to
	 * sleep (e.g. the arc_adjust_lock).  However, the lock ordering of
	 * such a lock would necessarily be incorrect with respect to the
	 * zthr_lock, which is held before this function is called, and is
	 * held by arc_get_data_impl() when it calls zthr_wakeup().
	 */
	return (arc_adjust_needed);
}