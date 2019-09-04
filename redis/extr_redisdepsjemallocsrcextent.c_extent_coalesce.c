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
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ extents_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_activate_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_can_coalesce (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deactivate_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int extent_merge_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
extent_coalesce(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    extents_t *extents, extent_t *inner, extent_t *outer, bool forward,
    bool growing_retained) {
	assert(extent_can_coalesce(arena, extents, inner, outer));

	extent_activate_locked(tsdn, arena, extents, outer);

	malloc_mutex_unlock(tsdn, &extents->mtx);
	bool err = extent_merge_impl(tsdn, arena, r_extent_hooks,
	    forward ? inner : outer, forward ? outer : inner, growing_retained);
	malloc_mutex_lock(tsdn, &extents->mtx);

	if (err) {
		extent_deactivate_locked(tsdn, arena, extents, outer);
	}

	return err;
}