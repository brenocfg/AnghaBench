#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_7__ {int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_background_thread_inactivity_check (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  arena_decay_dirty (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 scalar_t__ arena_dirty_decay_ms_get (TYPE_1__*) ; 
 int /*<<< orphan*/  extents_dalloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
arena_extents_dirty_dalloc(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extents_dalloc(tsdn, arena, r_extent_hooks, &arena->extents_dirty,
	    extent);
	if (arena_dirty_decay_ms_get(arena) == 0) {
		arena_decay_dirty(tsdn, arena, false, true);
	} else {
		arena_background_thread_inactivity_check(tsdn, arena, false);
	}
}