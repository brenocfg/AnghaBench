#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct prof_gctx_merge_iter_arg_s {scalar_t__ tsdn; int /*<<< orphan*/  leak_ngctx; } ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;
struct TYPE_5__ {scalar_t__ curobjs; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ cnt_summed; int /*<<< orphan*/  tctxs; } ;
typedef  TYPE_2__ prof_gctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_tctx_merge_iter ; 
 int /*<<< orphan*/  tctx_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static prof_gctx_t *
prof_gctx_merge_iter(prof_gctx_tree_t *gctxs, prof_gctx_t *gctx, void *opaque) {
	struct prof_gctx_merge_iter_arg_s *arg =
	    (struct prof_gctx_merge_iter_arg_s *)opaque;

	malloc_mutex_lock(arg->tsdn, gctx->lock);
	tctx_tree_iter(&gctx->tctxs, NULL, prof_tctx_merge_iter,
	    (void *)arg->tsdn);
	if (gctx->cnt_summed.curobjs != 0) {
		arg->leak_ngctx++;
	}
	malloc_mutex_unlock(arg->tsdn, gctx->lock);

	return NULL;
}