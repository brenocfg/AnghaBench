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

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_EXTENT_POOL ; 
 int /*<<< orphan*/  extent_dss_boot () ; 
 int /*<<< orphan*/  extent_mutex_pool ; 
 int /*<<< orphan*/  extents_rtree ; 
 scalar_t__ have_dss ; 
 scalar_t__ mutex_pool_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtree_new (int /*<<< orphan*/ *,int) ; 

bool
extent_boot(void) {
	if (rtree_new(&extents_rtree, true)) {
		return true;
	}

	if (mutex_pool_init(&extent_mutex_pool, "extent_mutex_pool",
	    WITNESS_RANK_EXTENT_POOL)) {
		return true;
	}

	if (have_dss) {
		extent_dss_boot();
	}

	return false;
}