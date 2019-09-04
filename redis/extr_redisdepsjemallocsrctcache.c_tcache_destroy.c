#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  void tcache_t ;
struct TYPE_4__ {scalar_t__ ncached_max; } ;
struct TYPE_3__ {scalar_t__ avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcache_arena_dissociate (int /*<<< orphan*/ ,void*) ; 
 TYPE_2__* tcache_bin_info ; 
 int /*<<< orphan*/  tcache_flush_cache (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* tcache_small_bin_get (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcache_destroy(tsd_t *tsd, tcache_t *tcache, bool tsd_tcache) {
	tcache_flush_cache(tsd, tcache);
	tcache_arena_dissociate(tsd_tsdn(tsd), tcache);

	if (tsd_tcache) {
		/* Release the avail array for the TSD embedded auto tcache. */
		void *avail_array =
		    (void *)((uintptr_t)tcache_small_bin_get(tcache, 0)->avail -
		    (uintptr_t)tcache_bin_info[0].ncached_max * sizeof(void *));
		idalloctm(tsd_tsdn(tsd), avail_array, NULL, NULL, true, true);
	} else {
		/* Release both the tcache struct and avail array. */
		idalloctm(tsd_tsdn(tsd), tcache, NULL, NULL, true, true);
	}
}