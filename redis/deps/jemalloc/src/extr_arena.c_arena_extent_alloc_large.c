#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_11__ {int /*<<< orphan*/  mapped; } ;
struct TYPE_10__ {TYPE_4__ stats; int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EXTENT_HOOKS_INITIALIZER ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_large_malloc_stats_update (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  arena_nactive_add (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  arena_stats_add_zu (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  arena_stats_lock (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  arena_stats_unlock (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/ * extent_alloc_wrapper (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * extents_alloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*) ; 
 size_t sz_large_pad ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extent_t *
arena_extent_alloc_large(tsdn_t *tsdn, arena_t *arena, size_t usize,
    size_t alignment, bool *zero) {
	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;

	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	szind_t szind = sz_size2index(usize);
	size_t mapped_add;
	bool commit = true;
	extent_t *extent = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_dirty, NULL, usize, sz_large_pad, alignment, false,
	    szind, zero, &commit);
	if (extent == NULL) {
		extent = extents_alloc(tsdn, arena, &extent_hooks,
		    &arena->extents_muzzy, NULL, usize, sz_large_pad, alignment,
		    false, szind, zero, &commit);
	}
	size_t size = usize + sz_large_pad;
	if (extent == NULL) {
		extent = extent_alloc_wrapper(tsdn, arena, &extent_hooks, NULL,
		    usize, sz_large_pad, alignment, false, szind, zero,
		    &commit);
		if (config_stats) {
			/*
			 * extent may be NULL on OOM, but in that case
			 * mapped_add isn't used below, so there's no need to
			 * conditionlly set it to 0 here.
			 */
			mapped_add = size;
		}
	} else if (config_stats) {
		mapped_add = 0;
	}

	if (extent != NULL) {
		if (config_stats) {
			arena_stats_lock(tsdn, &arena->stats);
			arena_large_malloc_stats_update(tsdn, arena, usize);
			if (mapped_add != 0) {
				arena_stats_add_zu(tsdn, &arena->stats,
				    &arena->stats.mapped, mapped_add);
			}
			arena_stats_unlock(tsdn, &arena->stats);
		}
		arena_nactive_add(arena, size >> LG_PAGE);
	}

	return extent;
}