#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  prof_tctx_tree_t ;
struct TYPE_6__ {int state; TYPE_5__* gctx; } ;
typedef  TYPE_1__ prof_tctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/  prof_tctx_merge_gctx (int /*<<< orphan*/ *,TYPE_1__*,TYPE_5__*) ; 
#define  prof_tctx_state_dumping 130 
#define  prof_tctx_state_nominal 129 
#define  prof_tctx_state_purgatory 128 

__attribute__((used)) static prof_tctx_t *
prof_tctx_merge_iter(prof_tctx_tree_t *tctxs, prof_tctx_t *tctx, void *arg) {
	tsdn_t *tsdn = (tsdn_t *)arg;

	malloc_mutex_assert_owner(tsdn, tctx->gctx->lock);

	switch (tctx->state) {
	case prof_tctx_state_nominal:
		/* New since dumping started; ignore. */
		break;
	case prof_tctx_state_dumping:
	case prof_tctx_state_purgatory:
		prof_tctx_merge_gctx(tsdn, tctx, tctx->gctx);
		break;
	default:
		not_reached();
	}

	return NULL;
}