#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int ms_weight; int ms_loaded; int ms_allocator; int /*<<< orphan*/  ms_group; int /*<<< orphan*/  ms_allocatable; int /*<<< orphan*/  ms_primary; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EQUIV (int,int /*<<< orphan*/ ) ; 
 int METASLAB_ACTIVE_MASK ; 
 int METASLAB_WEIGHT_PRIMARY ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int metaslab_activate_allocator (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  metaslab_group_sort (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int metaslab_load (TYPE_1__*) ; 
 int /*<<< orphan*/  range_tree_space (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
metaslab_activate(metaslab_t *msp, int allocator, uint64_t activation_weight)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/*
	 * The current metaslab is already activated for us so there
	 * is nothing to do. Already activated though, doesn't mean
	 * that this metaslab is activated for our allocator nor our
	 * requested activation weight. The metaslab could have started
	 * as an active one for our allocator but changed allocators
	 * while we were waiting to grab its ms_lock or we stole it
	 * [see find_valid_metaslab()]. This means that there is a
	 * possibility of passivating a metaslab of another allocator
	 * or from a different activation mask, from this thread.
	 */
	if ((msp->ms_weight & METASLAB_ACTIVE_MASK) != 0) {
		ASSERT(msp->ms_loaded);
		return (0);
	}

	int error = metaslab_load(msp);
	if (error != 0) {
		metaslab_group_sort(msp->ms_group, msp, 0);
		return (error);
	}

	/*
	 * When entering metaslab_load() we may have dropped the
	 * ms_lock because we were loading this metaslab, or we
	 * were waiting for another thread to load it for us. In
	 * that scenario, we recheck the weight of the metaslab
	 * to see if it was activated by another thread.
	 *
	 * If the metaslab was activated for another allocator or
	 * it was activated with a different activation weight (e.g.
	 * we wanted to make it a primary but it was activated as
	 * secondary) we return error (EBUSY).
	 *
	 * If the metaslab was activated for the same allocator
	 * and requested activation mask, skip activating it.
	 */
	if ((msp->ms_weight & METASLAB_ACTIVE_MASK) != 0) {
		if (msp->ms_allocator != allocator)
			return (EBUSY);

		if ((msp->ms_weight & activation_weight) == 0)
			return (SET_ERROR(EBUSY));

		EQUIV((activation_weight == METASLAB_WEIGHT_PRIMARY),
		    msp->ms_primary);
		return (0);
	}

	/*
	 * If the metaslab has literally 0 space, it will have weight 0. In
	 * that case, don't bother activating it. This can happen if the
	 * metaslab had space during find_valid_metaslab, but another thread
	 * loaded it and used all that space while we were waiting to grab the
	 * lock.
	 */
	if (msp->ms_weight == 0) {
		ASSERT0(range_tree_space(msp->ms_allocatable));
		return (SET_ERROR(ENOSPC));
	}

	if ((error = metaslab_activate_allocator(msp->ms_group, msp,
	    allocator, activation_weight)) != 0) {
		return (error);
	}

	ASSERT(msp->ms_loaded);
	ASSERT(msp->ms_weight & METASLAB_ACTIVE_MASK);

	return (0);
}