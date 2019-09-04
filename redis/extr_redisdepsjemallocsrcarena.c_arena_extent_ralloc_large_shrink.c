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
struct TYPE_5__ {int /*<<< orphan*/  stats; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 size_t LG_PAGE ; 
 int /*<<< orphan*/  arena_large_ralloc_stats_update (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  arena_nactive_sub (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  arena_stats_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_stats_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ config_stats ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 

void
arena_extent_ralloc_large_shrink(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    size_t oldusize) {
	size_t usize = extent_usize_get(extent);
	size_t udiff = oldusize - usize;

	if (config_stats) {
		arena_stats_lock(tsdn, &arena->stats);
		arena_large_ralloc_stats_update(tsdn, arena, oldusize, usize);
		arena_stats_unlock(tsdn, &arena->stats);
	}
	arena_nactive_sub(arena, udiff >> LG_PAGE);
}