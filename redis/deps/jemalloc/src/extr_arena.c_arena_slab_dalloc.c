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
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EXTENT_HOOKS_INITIALIZER ; 
 int LG_PAGE ; 
 int /*<<< orphan*/  arena_extents_dirty_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_nactive_sub (int /*<<< orphan*/ *,int) ; 
 int extent_size_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_slab_dalloc(tsdn_t *tsdn, arena_t *arena, extent_t *slab) {
	arena_nactive_sub(arena, extent_size_get(slab) >> LG_PAGE);

	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;
	arena_extents_dirty_dalloc(tsdn, arena, &extent_hooks, slab);
}