#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tsd_t ;
typedef  size_t szind_t ;
struct TYPE_16__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_7__ bin_t ;
struct TYPE_14__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_13__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_12__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_10__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_17__ {TYPE_7__* bins; TYPE_6__* base; int /*<<< orphan*/  tcache_ql_mtx; TYPE_5__ decay_muzzy; TYPE_4__ decay_dirty; TYPE_3__ extents_retained; TYPE_2__ extents_muzzy; TYPE_1__ extents_dirty; int /*<<< orphan*/  extent_avail_mtx; int /*<<< orphan*/  large_mtx; } ;
typedef  TYPE_8__ arena_t ;
struct TYPE_15__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MUTEX_PROF_RESET (int /*<<< orphan*/ ) ; 
 size_t NBINS ; 
 TYPE_8__* arena_get (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  background_thread_lock ; 
 int /*<<< orphan*/  bt2gctx_mtx ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  config_stats ; 
 int /*<<< orphan*/  ctl_mtx ; 
 scalar_t__ have_background_thread ; 
 unsigned int narenas_total_get () ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/ * tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
stats_mutexes_reset_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	if (!config_stats) {
		return ENOENT;
	}

	tsdn_t *tsdn = tsd_tsdn(tsd);

#define MUTEX_PROF_RESET(mtx)						\
    malloc_mutex_lock(tsdn, &mtx);					\
    malloc_mutex_prof_data_reset(tsdn, &mtx);				\
    malloc_mutex_unlock(tsdn, &mtx);

	/* Global mutexes: ctl and prof. */
	MUTEX_PROF_RESET(ctl_mtx);
	if (have_background_thread) {
		MUTEX_PROF_RESET(background_thread_lock);
	}
	if (config_prof && opt_prof) {
		MUTEX_PROF_RESET(bt2gctx_mtx);
	}


	/* Per arena mutexes. */
	unsigned n = narenas_total_get();

	for (unsigned i = 0; i < n; i++) {
		arena_t *arena = arena_get(tsdn, i, false);
		if (!arena) {
			continue;
		}
		MUTEX_PROF_RESET(arena->large_mtx);
		MUTEX_PROF_RESET(arena->extent_avail_mtx);
		MUTEX_PROF_RESET(arena->extents_dirty.mtx);
		MUTEX_PROF_RESET(arena->extents_muzzy.mtx);
		MUTEX_PROF_RESET(arena->extents_retained.mtx);
		MUTEX_PROF_RESET(arena->decay_dirty.mtx);
		MUTEX_PROF_RESET(arena->decay_muzzy.mtx);
		MUTEX_PROF_RESET(arena->tcache_ql_mtx);
		MUTEX_PROF_RESET(arena->base->mtx);

		for (szind_t i = 0; i < NBINS; i++) {
			bin_t *bin = &arena->bins[i];
			MUTEX_PROF_RESET(bin->lock);
		}
	}
#undef MUTEX_PROF_RESET
	return 0;
}