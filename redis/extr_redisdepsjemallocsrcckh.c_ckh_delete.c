#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_4__ {int /*<<< orphan*/  tab; } ;
typedef  TYPE_1__ ckh_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_FREE_JUNK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
ckh_delete(tsd_t *tsd, ckh_t *ckh) {
	assert(ckh != NULL);

#ifdef CKH_VERBOSE
	malloc_printf(
	    "%s(%p): ngrows: %"FMTu64", nshrinks: %"FMTu64","
	    " nshrinkfails: %"FMTu64", ninserts: %"FMTu64","
	    " nrelocs: %"FMTu64"\n", __func__, ckh,
	    (unsigned long long)ckh->ngrows,
	    (unsigned long long)ckh->nshrinks,
	    (unsigned long long)ckh->nshrinkfails,
	    (unsigned long long)ckh->ninserts,
	    (unsigned long long)ckh->nrelocs);
#endif

	idalloctm(tsd_tsdn(tsd), ckh->tab, NULL, NULL, true, true);
	if (config_debug) {
		memset(ckh, JEMALLOC_FREE_JUNK, sizeof(ckh_t));
	}
}