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
typedef  int /*<<< orphan*/  ckhc_t ;
struct TYPE_4__ {unsigned int lg_curbuckets; int /*<<< orphan*/  nshrinkfails; int /*<<< orphan*/ * tab; int /*<<< orphan*/  nshrinks; } ;
typedef  TYPE_1__ ckh_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 size_t LARGE_MAXCLASS ; 
 int LG_CKH_BUCKET_CELLS ; 
 int /*<<< orphan*/  arena_ichoose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ckh_rebuild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ipallocztm (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t sz_sa2u (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ckh_shrink(tsd_t *tsd, ckh_t *ckh) {
	ckhc_t *tab, *ttab;
	size_t usize;
	unsigned lg_prevbuckets, lg_curcells;

	/*
	 * It is possible (though unlikely, given well behaved hashes) that the
	 * table rebuild will fail.
	 */
	lg_prevbuckets = ckh->lg_curbuckets;
	lg_curcells = ckh->lg_curbuckets + LG_CKH_BUCKET_CELLS - 1;
	usize = sz_sa2u(sizeof(ckhc_t) << lg_curcells, CACHELINE);
	if (unlikely(usize == 0 || usize > LARGE_MAXCLASS)) {
		return;
	}
	tab = (ckhc_t *)ipallocztm(tsd_tsdn(tsd), usize, CACHELINE, true, NULL,
	    true, arena_ichoose(tsd, NULL));
	if (tab == NULL) {
		/*
		 * An OOM error isn't worth propagating, since it doesn't
		 * prevent this or future operations from proceeding.
		 */
		return;
	}
	/* Swap in new table. */
	ttab = ckh->tab;
	ckh->tab = tab;
	tab = ttab;
	ckh->lg_curbuckets = lg_curcells - LG_CKH_BUCKET_CELLS;

	if (!ckh_rebuild(ckh, tab)) {
		idalloctm(tsd_tsdn(tsd), tab, NULL, NULL, true, true);
#ifdef CKH_COUNT
		ckh->nshrinks++;
#endif
		return;
	}

	/* Rebuilding failed, so back out partially rebuilt table. */
	idalloctm(tsd_tsdn(tsd), ckh->tab, NULL, NULL, true, true);
	ckh->tab = tab;
	ckh->lg_curbuckets = lg_prevbuckets;
#ifdef CKH_COUNT
	ckh->nshrinkfails++;
#endif
}