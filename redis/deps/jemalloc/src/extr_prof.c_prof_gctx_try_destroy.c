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
typedef  int /*<<< orphan*/  prof_tdata_t ;
struct TYPE_4__ {int nlimbo; int /*<<< orphan*/  lock; int /*<<< orphan*/  bt; int /*<<< orphan*/  tctxs; } ;
typedef  TYPE_1__ prof_gctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bt2gctx ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 scalar_t__ ckh_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/  prof_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_leave (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tctx_tree_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_gctx_try_destroy(tsd_t *tsd, prof_tdata_t *tdata_self, prof_gctx_t *gctx,
    prof_tdata_t *tdata) {
	cassert(config_prof);

	/*
	 * Check that gctx is still unused by any thread cache before destroying
	 * it.  prof_lookup() increments gctx->nlimbo in order to avoid a race
	 * condition with this function, as does prof_tctx_destroy() in order to
	 * avoid a race between the main body of prof_tctx_destroy() and entry
	 * into this function.
	 */
	prof_enter(tsd, tdata_self);
	malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
	assert(gctx->nlimbo != 0);
	if (tctx_tree_empty(&gctx->tctxs) && gctx->nlimbo == 1) {
		/* Remove gctx from bt2gctx. */
		if (ckh_remove(tsd, &bt2gctx, &gctx->bt, NULL, NULL)) {
			not_reached();
		}
		prof_leave(tsd, tdata_self);
		/* Destroy gctx. */
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		idalloctm(tsd_tsdn(tsd), gctx, NULL, NULL, true, true);
	} else {
		/*
		 * Compensate for increment in prof_tctx_destroy() or
		 * prof_lookup().
		 */
		gctx->nlimbo--;
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		prof_leave(tsd, tdata_self);
	}
}