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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_dalloc_bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 

void
arena_dalloc_small(tsdn_t *tsdn, void *ptr) {
	extent_t *extent = iealloc(tsdn, ptr);
	arena_t *arena = extent_arena_get(extent);

	arena_dalloc_bin(tsdn, arena, extent, ptr);
	arena_decay_tick(tsdn, arena);
}