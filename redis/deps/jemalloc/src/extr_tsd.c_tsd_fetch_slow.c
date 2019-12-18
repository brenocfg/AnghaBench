#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ state; } ;
typedef  TYPE_1__ tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_tsd_data_cleanup_done (TYPE_1__*) ; 
 scalar_t__ malloc_slow ; 
 scalar_t__* tsd_arenas_tdata_bypassp_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_data_init (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_data_init_nocleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_fast (TYPE_1__*) ; 
 scalar_t__ tsd_reentrancy_level_get (TYPE_1__*) ; 
 int* tsd_reentrancy_levelp_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_set (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_slow_update (TYPE_1__*) ; 
 scalar_t__ tsd_state_minimal_initialized ; 
 void* tsd_state_nominal ; 
 scalar_t__ tsd_state_nominal_slow ; 
 scalar_t__ tsd_state_purgatory ; 
 scalar_t__ tsd_state_reincarnated ; 
 scalar_t__ tsd_state_uninitialized ; 
 int /*<<< orphan*/  tsd_tcache_enabled_get (TYPE_1__*) ; 

tsd_t *
tsd_fetch_slow(tsd_t *tsd, bool minimal) {
	assert(!tsd_fast(tsd));

	if (tsd->state == tsd_state_nominal_slow) {
		/* On slow path but no work needed. */
		assert(malloc_slow || !tsd_tcache_enabled_get(tsd) ||
		    tsd_reentrancy_level_get(tsd) > 0 ||
		    *tsd_arenas_tdata_bypassp_get(tsd));
	} else if (tsd->state == tsd_state_uninitialized) {
		if (!minimal) {
			tsd->state = tsd_state_nominal;
			tsd_slow_update(tsd);
			/* Trigger cleanup handler registration. */
			tsd_set(tsd);
			tsd_data_init(tsd);
		} else {
			tsd->state = tsd_state_minimal_initialized;
			tsd_set(tsd);
			tsd_data_init_nocleanup(tsd);
		}
	} else if (tsd->state == tsd_state_minimal_initialized) {
		if (!minimal) {
			/* Switch to fully initialized. */
			tsd->state = tsd_state_nominal;
			assert(*tsd_reentrancy_levelp_get(tsd) >= 1);
			(*tsd_reentrancy_levelp_get(tsd))--;
			tsd_slow_update(tsd);
			tsd_data_init(tsd);
		} else {
			assert_tsd_data_cleanup_done(tsd);
		}
	} else if (tsd->state == tsd_state_purgatory) {
		tsd->state = tsd_state_reincarnated;
		tsd_set(tsd);
		tsd_data_init_nocleanup(tsd);
	} else {
		assert(tsd->state == tsd_state_reincarnated);
	}

	return tsd;
}