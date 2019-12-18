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
struct TYPE_5__ {int /*<<< orphan*/  kc_in_use_lock; TYPE_2__* kc_req_chain_last; TYPE_2__* kc_req_chain_first; } ;
typedef  TYPE_1__ kcf_context_t ;
struct TYPE_6__ {struct TYPE_6__* an_ctxchain_next; } ;
typedef  TYPE_2__ kcf_areq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
kcf_removereq_in_ctxchain(kcf_context_t *ictx, kcf_areq_node_t *areq)
{
	kcf_areq_node_t *cur, *prev;

	/*
	 * Get context lock, search for areq in the chain and remove it.
	 */
	ASSERT(ictx != NULL);
	mutex_enter(&ictx->kc_in_use_lock);
	prev = cur = ictx->kc_req_chain_first;

	while (cur != NULL) {
		if (cur == areq) {
			if (prev == cur) {
				if ((ictx->kc_req_chain_first =
				    cur->an_ctxchain_next) == NULL)
					ictx->kc_req_chain_last = NULL;
			} else {
				if (cur == ictx->kc_req_chain_last)
					ictx->kc_req_chain_last = prev;
				prev->an_ctxchain_next = cur->an_ctxchain_next;
			}

			break;
		}
		prev = cur;
		cur = cur->an_ctxchain_next;
	}
	mutex_exit(&ictx->kc_in_use_lock);
}