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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 size_t LARGE_MAXCLASS ; 
 size_t LARGE_MINCLASS ; 
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extent_arena_get (int /*<<< orphan*/ *) ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 scalar_t__ large_ralloc_no_move_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  large_ralloc_no_move_shrink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

bool
large_ralloc_no_move(tsdn_t *tsdn, extent_t *extent, size_t usize_min,
    size_t usize_max, bool zero) {
	size_t oldusize = extent_usize_get(extent);

	/* The following should have been caught by callers. */
	assert(usize_min > 0 && usize_max <= LARGE_MAXCLASS);
	/* Both allocation sizes must be large to avoid a move. */
	assert(oldusize >= LARGE_MINCLASS && usize_max >= LARGE_MINCLASS);

	if (usize_max > oldusize) {
		/* Attempt to expand the allocation in-place. */
		if (!large_ralloc_no_move_expand(tsdn, extent, usize_max,
		    zero)) {
			arena_decay_tick(tsdn, extent_arena_get(extent));
			return false;
		}
		/* Try again, this time with usize_min. */
		if (usize_min < usize_max && usize_min > oldusize &&
		    large_ralloc_no_move_expand(tsdn, extent, usize_min,
		    zero)) {
			arena_decay_tick(tsdn, extent_arena_get(extent));
			return false;
		}
	}

	/*
	 * Avoid moving the allocation if the existing extent size accommodates
	 * the new size.
	 */
	if (oldusize >= usize_min && oldusize <= usize_max) {
		arena_decay_tick(tsdn, extent_arena_get(extent));
		return false;
	}

	/* Attempt to shrink the allocation in-place. */
	if (oldusize > usize_max) {
		if (!large_ralloc_no_move_shrink(tsdn, extent, usize_max)) {
			arena_decay_tick(tsdn, extent_arena_get(extent));
			return false;
		}
	}
	return true;
}