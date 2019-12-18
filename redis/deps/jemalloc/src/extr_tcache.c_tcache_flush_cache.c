#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_14__ {scalar_t__ prof_accumbytes; int /*<<< orphan*/ * arena; } ;
typedef  TYPE_2__ tcache_t ;
struct TYPE_13__ {scalar_t__ nrequests; } ;
struct TYPE_15__ {TYPE_1__ tstats; } ;
typedef  TYPE_3__ cache_bin_t ;

/* Variables and functions */
 unsigned int NBINS ; 
 scalar_t__ arena_prof_accum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_prof ; 
 scalar_t__ config_stats ; 
 unsigned int nhbins ; 
 int /*<<< orphan*/  prof_idump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache_bin_flush_large (int /*<<< orphan*/ *,TYPE_3__*,unsigned int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  tcache_bin_flush_small (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcache_large_bin_get (TYPE_2__*,unsigned int) ; 
 TYPE_3__* tcache_small_bin_get (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcache_flush_cache(tsd_t *tsd, tcache_t *tcache) {
	assert(tcache->arena != NULL);

	for (unsigned i = 0; i < NBINS; i++) {
		cache_bin_t *tbin = tcache_small_bin_get(tcache, i);
		tcache_bin_flush_small(tsd, tcache, tbin, i, 0);

		if (config_stats) {
			assert(tbin->tstats.nrequests == 0);
		}
	}
	for (unsigned i = NBINS; i < nhbins; i++) {
		cache_bin_t *tbin = tcache_large_bin_get(tcache, i);
		tcache_bin_flush_large(tsd, tbin, i, 0, tcache);

		if (config_stats) {
			assert(tbin->tstats.nrequests == 0);
		}
	}

	if (config_prof && tcache->prof_accumbytes > 0 &&
	    arena_prof_accum(tsd_tsdn(tsd), tcache->arena,
	    tcache->prof_accumbytes)) {
		prof_idump(tsd_tsdn(tsd));
	}
}