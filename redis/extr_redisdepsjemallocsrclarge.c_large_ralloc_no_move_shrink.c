#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/ * split; } ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSIZES ; 
 int /*<<< orphan*/  arena_extent_ralloc_large_shrink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  arena_extents_dirty_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_fill ; 
 int /*<<< orphan*/  extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_arena_get (int /*<<< orphan*/ *) ; 
 TYPE_1__* extent_hooks_get (int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_split_wrapper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int) ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  large_dalloc_maybe_junk (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  opt_junk_free ; 
 size_t sz_large_pad ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
large_ralloc_no_move_shrink(tsdn_t *tsdn, extent_t *extent, size_t usize) {
	arena_t *arena = extent_arena_get(extent);
	size_t oldusize = extent_usize_get(extent);
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	size_t diff = extent_size_get(extent) - (usize + sz_large_pad);

	assert(oldusize > usize);

	if (extent_hooks->split == NULL) {
		return true;
	}

	/* Split excess pages. */
	if (diff != 0) {
		extent_t *trail = extent_split_wrapper(tsdn, arena,
		    &extent_hooks, extent, usize + sz_large_pad,
		    sz_size2index(usize), false, diff, NSIZES, false);
		if (trail == NULL) {
			return true;
		}

		if (config_fill && unlikely(opt_junk_free)) {
			large_dalloc_maybe_junk(extent_addr_get(trail),
			    extent_size_get(trail));
		}

		arena_extents_dirty_dalloc(tsdn, arena, &extent_hooks, trail);
	}

	arena_extent_ralloc_large_shrink(tsdn, arena, extent, oldusize);

	return false;
}