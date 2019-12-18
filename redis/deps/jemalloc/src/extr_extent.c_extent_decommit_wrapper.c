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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_6__ {scalar_t__ (* decommit ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_base_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_committed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__ extent_hooks_default ; 
 int /*<<< orphan*/  extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
extent_decommit_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_hooks_assure_initialized(arena, r_extent_hooks);

	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_pre_reentrancy(tsdn, arena);
	}
	bool err = ((*r_extent_hooks)->decommit == NULL ||
	    (*r_extent_hooks)->decommit(*r_extent_hooks,
	    extent_base_get(extent), extent_size_get(extent), offset, length,
	    arena_ind_get(arena)));
	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_post_reentrancy(tsdn);
	}
	extent_committed_set(extent, extent_committed_get(extent) && err);
	return err;
}