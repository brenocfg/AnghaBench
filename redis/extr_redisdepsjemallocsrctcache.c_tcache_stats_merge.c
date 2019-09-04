#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tcache_t ;
struct TYPE_10__ {scalar_t__ nrequests; } ;
struct TYPE_11__ {TYPE_2__ tstats; } ;
typedef  TYPE_3__ cache_bin_t ;
struct TYPE_9__ {int /*<<< orphan*/  nrequests; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;
typedef  TYPE_4__ bin_t ;
struct TYPE_13__ {int /*<<< orphan*/  stats; TYPE_4__* bins; } ;
typedef  TYPE_5__ arena_t ;

/* Variables and functions */
 unsigned int NBINS ; 
 int /*<<< orphan*/  arena_stats_large_nrequests_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_stats ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int nhbins ; 
 TYPE_3__* tcache_large_bin_get (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_3__* tcache_small_bin_get (int /*<<< orphan*/ *,unsigned int) ; 

void
tcache_stats_merge(tsdn_t *tsdn, tcache_t *tcache, arena_t *arena) {
	unsigned i;

	cassert(config_stats);

	/* Merge and reset tcache stats. */
	for (i = 0; i < NBINS; i++) {
		bin_t *bin = &arena->bins[i];
		cache_bin_t *tbin = tcache_small_bin_get(tcache, i);
		malloc_mutex_lock(tsdn, &bin->lock);
		bin->stats.nrequests += tbin->tstats.nrequests;
		malloc_mutex_unlock(tsdn, &bin->lock);
		tbin->tstats.nrequests = 0;
	}

	for (; i < nhbins; i++) {
		cache_bin_t *tbin = tcache_large_bin_get(tcache, i);
		arena_stats_large_nrequests_add(tsdn, &arena->stats, i,
		    tbin->tstats.nrequests);
		tbin->tstats.nrequests = 0;
	}
}