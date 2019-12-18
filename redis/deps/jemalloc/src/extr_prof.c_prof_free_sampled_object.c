#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_8__ {scalar_t__ curobjs; size_t curbytes; } ;
struct TYPE_9__ {TYPE_1__* tdata; TYPE_2__ cnts; } ;
typedef  TYPE_3__ prof_tctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_tctx_destroy (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ prof_tctx_should_destroy (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
prof_free_sampled_object(tsd_t *tsd, size_t usize, prof_tctx_t *tctx) {
	malloc_mutex_lock(tsd_tsdn(tsd), tctx->tdata->lock);
	assert(tctx->cnts.curobjs > 0);
	assert(tctx->cnts.curbytes >= usize);
	tctx->cnts.curobjs--;
	tctx->cnts.curbytes -= usize;

	if (prof_tctx_should_destroy(tsd_tsdn(tsd), tctx)) {
		prof_tctx_destroy(tsd, tctx);
	} else {
		malloc_mutex_unlock(tsd_tsdn(tsd), tctx->tdata->lock);
	}
}