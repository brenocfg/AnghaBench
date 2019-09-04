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
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * extent_split_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int,int) ; 

extent_t *
extent_split_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t size_a,
    szind_t szind_a, bool slab_a, size_t size_b, szind_t szind_b, bool slab_b) {
	return extent_split_impl(tsdn, arena, r_extent_hooks, extent, size_a,
	    szind_a, slab_a, size_b, szind_b, slab_b, false);
}