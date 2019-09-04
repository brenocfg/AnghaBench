#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_7__ {int initialized; } ;
typedef  TYPE_1__ ctl_arena_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_8__ {int /*<<< orphan*/  destroyed; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned int MALLCTL_ARENAS_DESTROYED ; 
 int /*<<< orphan*/  arena_decay (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  arena_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int arena_i_reset_destroy_helper (int /*<<< orphan*/ *,size_t const*,size_t,void*,size_t*,void*,size_t,unsigned int*,int /*<<< orphan*/ **) ; 
 scalar_t__ arena_nthreads_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  arena_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_reset_finish_background_thread (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  arena_reset_prepare_background_thread (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* arenas_i (unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctl_arena_refresh (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,unsigned int,int) ; 
 TYPE_4__* ctl_arenas ; 
 int /*<<< orphan*/  destroyed_link ; 
 int /*<<< orphan*/  ql_elm_new (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_tail_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arena_i_destroy_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;
	arena_t *arena;
	ctl_arena_t *ctl_darena, *ctl_arena;

	ret = arena_i_reset_destroy_helper(tsd, mib, miblen, oldp, oldlenp,
	    newp, newlen, &arena_ind, &arena);
	if (ret != 0) {
		goto label_return;
	}

	if (arena_nthreads_get(arena, false) != 0 || arena_nthreads_get(arena,
	    true) != 0) {
		ret = EFAULT;
		goto label_return;
	}

	arena_reset_prepare_background_thread(tsd, arena_ind);
	/* Merge stats after resetting and purging arena. */
	arena_reset(tsd, arena);
	arena_decay(tsd_tsdn(tsd), arena, false, true);
	ctl_darena = arenas_i(MALLCTL_ARENAS_DESTROYED);
	ctl_darena->initialized = true;
	ctl_arena_refresh(tsd_tsdn(tsd), arena, ctl_darena, arena_ind, true);
	/* Destroy arena. */
	arena_destroy(tsd, arena);
	ctl_arena = arenas_i(arena_ind);
	ctl_arena->initialized = false;
	/* Record arena index for later recycling via arenas.create. */
	ql_elm_new(ctl_arena, destroyed_link);
	ql_tail_insert(&ctl_arenas->destroyed, ctl_arena, destroyed_link);
	arena_reset_finish_background_thread(tsd, arena_ind);

	assert(ret == 0);
label_return:
	return ret;
}