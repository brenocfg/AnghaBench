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
typedef  scalar_t__ szind_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 scalar_t__ NSIZES ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extents_rtree ; 
 scalar_t__ rtree_extent_szind_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int,int /*<<< orphan*/ **,scalar_t__*) ; 
 size_t sz_index2size (scalar_t__) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
vsalloc(tsdn_t *tsdn, const void *ptr) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *extent;
	szind_t szind;
	if (rtree_extent_szind_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)ptr, false, &extent, &szind)) {
		return 0;
	}

	if (extent == NULL) {
		return 0;
	}
	if (extent_state_get(extent) != extent_state_active) {
		return 0;
	}

	if (szind == NSIZES) {
		return 0;
	}

	return sz_index2size(szind);
}