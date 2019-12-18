#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_6__ {scalar_t__ curobjs; } ;
struct TYPE_7__ {scalar_t__ prepared; TYPE_2__ cnts; TYPE_1__* tdata; } ;
typedef  TYPE_3__ prof_tctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_prof_accum ; 

__attribute__((used)) static bool
prof_tctx_should_destroy(tsdn_t *tsdn, prof_tctx_t *tctx) {
	malloc_mutex_assert_owner(tsdn, tctx->tdata->lock);

	if (opt_prof_accum) {
		return false;
	}
	if (tctx->cnts.curobjs != 0) {
		return false;
	}
	if (tctx->prepared) {
		return false;
	}
	return true;
}