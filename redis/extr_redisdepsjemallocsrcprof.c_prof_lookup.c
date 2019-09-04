#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  bt2tctx; int /*<<< orphan*/  tctx_uid_next; int /*<<< orphan*/  thr_discrim; int /*<<< orphan*/  thr_uid; } ;
typedef  TYPE_1__ prof_tdata_t ;
struct TYPE_13__ {int prepared; int /*<<< orphan*/  state; scalar_t__ tctx_uid; TYPE_3__* gctx; int /*<<< orphan*/  cnts; int /*<<< orphan*/  thr_discrim; int /*<<< orphan*/  thr_uid; TYPE_1__* tdata; } ;
typedef  TYPE_2__ prof_tctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  nlimbo; int /*<<< orphan*/  tctxs; } ;
typedef  TYPE_3__ prof_gctx_t ;
typedef  int /*<<< orphan*/  prof_cnt_t ;
typedef  int /*<<< orphan*/  prof_bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_ichoose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int ckh_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 int ckh_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  config_prof ; 
 void* iallocztm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prof_gctx_try_destroy (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ prof_lookup_global (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,void**,TYPE_3__**,int*) ; 
 int /*<<< orphan*/  prof_tctx_state_initializing ; 
 int /*<<< orphan*/  prof_tctx_state_nominal ; 
 TYPE_1__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sz_size2index (int) ; 
 int /*<<< orphan*/  tctx_tree_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

prof_tctx_t *
prof_lookup(tsd_t *tsd, prof_bt_t *bt) {
	union {
		prof_tctx_t	*p;
		void		*v;
	} ret;
	prof_tdata_t *tdata;
	bool not_found;

	cassert(config_prof);

	tdata = prof_tdata_get(tsd, false);
	if (tdata == NULL) {
		return NULL;
	}

	malloc_mutex_lock(tsd_tsdn(tsd), tdata->lock);
	not_found = ckh_search(&tdata->bt2tctx, bt, NULL, &ret.v);
	if (!not_found) { /* Note double negative! */
		ret.p->prepared = true;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);
	if (not_found) {
		void *btkey;
		prof_gctx_t *gctx;
		bool new_gctx, error;

		/*
		 * This thread's cache lacks bt.  Look for it in the global
		 * cache.
		 */
		if (prof_lookup_global(tsd, bt, tdata, &btkey, &gctx,
		    &new_gctx)) {
			return NULL;
		}

		/* Link a prof_tctx_t into gctx for this thread. */
		ret.v = iallocztm(tsd_tsdn(tsd), sizeof(prof_tctx_t),
		    sz_size2index(sizeof(prof_tctx_t)), false, NULL, true,
		    arena_ichoose(tsd, NULL), true);
		if (ret.p == NULL) {
			if (new_gctx) {
				prof_gctx_try_destroy(tsd, tdata, gctx, tdata);
			}
			return NULL;
		}
		ret.p->tdata = tdata;
		ret.p->thr_uid = tdata->thr_uid;
		ret.p->thr_discrim = tdata->thr_discrim;
		memset(&ret.p->cnts, 0, sizeof(prof_cnt_t));
		ret.p->gctx = gctx;
		ret.p->tctx_uid = tdata->tctx_uid_next++;
		ret.p->prepared = true;
		ret.p->state = prof_tctx_state_initializing;
		malloc_mutex_lock(tsd_tsdn(tsd), tdata->lock);
		error = ckh_insert(tsd, &tdata->bt2tctx, btkey, ret.v);
		malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);
		if (error) {
			if (new_gctx) {
				prof_gctx_try_destroy(tsd, tdata, gctx, tdata);
			}
			idalloctm(tsd_tsdn(tsd), ret.v, NULL, NULL, true, true);
			return NULL;
		}
		malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
		ret.p->state = prof_tctx_state_nominal;
		tctx_tree_insert(&gctx->tctxs, ret.p);
		gctx->nlimbo--;
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
	}

	return ret.p;
}