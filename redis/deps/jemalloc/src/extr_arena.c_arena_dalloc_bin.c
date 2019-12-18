#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ bin_t ;
struct TYPE_6__ {TYPE_1__* bins; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_dalloc_bin_locked_impl (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,void*,int) ; 
 size_t extent_szind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_dalloc_bin(tsdn_t *tsdn, arena_t *arena, extent_t *extent, void *ptr) {
	szind_t binind = extent_szind_get(extent);
	bin_t *bin = &arena->bins[binind];

	malloc_mutex_lock(tsdn, &bin->lock);
	arena_dalloc_bin_locked_impl(tsdn, arena, extent, ptr, false);
	malloc_mutex_unlock(tsdn, &bin->lock);
}