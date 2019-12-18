#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_14__ {size_t next_gc_bin; int* lg_fill_div; } ;
typedef  TYPE_1__ tcache_t ;
typedef  size_t szind_t ;
struct TYPE_15__ {int low_water; int ncached; } ;
typedef  TYPE_2__ cache_bin_t ;
struct TYPE_16__ {int ncached_max; } ;
typedef  TYPE_3__ cache_bin_info_t ;

/* Variables and functions */
 size_t NBINS ; 
 scalar_t__ nhbins ; 
 int /*<<< orphan*/  tcache_bin_flush_large (int /*<<< orphan*/ *,TYPE_2__*,size_t,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tcache_bin_flush_small (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,size_t,int) ; 
 TYPE_3__* tcache_bin_info ; 
 TYPE_2__* tcache_large_bin_get (TYPE_1__*,size_t) ; 
 TYPE_2__* tcache_small_bin_get (TYPE_1__*,size_t) ; 

void
tcache_event_hard(tsd_t *tsd, tcache_t *tcache) {
	szind_t binind = tcache->next_gc_bin;

	cache_bin_t *tbin;
	if (binind < NBINS) {
		tbin = tcache_small_bin_get(tcache, binind);
	} else {
		tbin = tcache_large_bin_get(tcache, binind);
	}
	if (tbin->low_water > 0) {
		/*
		 * Flush (ceiling) 3/4 of the objects below the low water mark.
		 */
		if (binind < NBINS) {
			tcache_bin_flush_small(tsd, tcache, tbin, binind,
			    tbin->ncached - tbin->low_water + (tbin->low_water
			    >> 2));
			/*
			 * Reduce fill count by 2X.  Limit lg_fill_div such that
			 * the fill count is always at least 1.
			 */
			cache_bin_info_t *tbin_info = &tcache_bin_info[binind];
			if ((tbin_info->ncached_max >>
			     (tcache->lg_fill_div[binind] + 1)) >= 1) {
				tcache->lg_fill_div[binind]++;
			}
		} else {
			tcache_bin_flush_large(tsd, tbin, binind, tbin->ncached
			    - tbin->low_water + (tbin->low_water >> 2), tcache);
		}
	} else if (tbin->low_water < 0) {
		/*
		 * Increase fill count by 2X for small bins.  Make sure
		 * lg_fill_div stays greater than 0.
		 */
		if (binind < NBINS && tcache->lg_fill_div[binind] > 1) {
			tcache->lg_fill_div[binind]--;
		}
	}
	tbin->low_water = tbin->ncached;

	tcache->next_gc_bin++;
	if (tcache->next_gc_bin == nhbins) {
		tcache->next_gc_bin = 0;
	}
}