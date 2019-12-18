#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_1__ tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_tsd_data_cleanup_done (TYPE_1__*) ; 
 int /*<<< orphan*/  rtree_ctx_data_init (int /*<<< orphan*/ ) ; 
 int* tsd_arenas_tdata_bypassp_get (TYPE_1__*) ; 
 int* tsd_reentrancy_levelp_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_rtree_ctxp_get_unsafe (TYPE_1__*) ; 
 scalar_t__ tsd_state_minimal_initialized ; 
 scalar_t__ tsd_state_reincarnated ; 
 int* tsd_tcache_enabledp_get_unsafe (TYPE_1__*) ; 

__attribute__((used)) static bool
tsd_data_init_nocleanup(tsd_t *tsd) {
	assert(tsd->state == tsd_state_reincarnated ||
	    tsd->state == tsd_state_minimal_initialized);
	/*
	 * During reincarnation, there is no guarantee that the cleanup function
	 * will be called (deallocation may happen after all tsd destructors).
	 * We set up tsd in a way that no cleanup is needed.
	 */
	rtree_ctx_data_init(tsd_rtree_ctxp_get_unsafe(tsd));
	*tsd_arenas_tdata_bypassp_get(tsd) = true;
	*tsd_tcache_enabledp_get_unsafe(tsd) = false;
	*tsd_reentrancy_levelp_get(tsd) = 1;
	assert_tsd_data_cleanup_done(tsd);

	return false;
}