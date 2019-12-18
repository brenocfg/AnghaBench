#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;
struct TYPE_7__ {int /*<<< orphan*/  kc_in_use_lock; TYPE_2__* kc_req_chain_last; TYPE_2__* kc_req_chain_first; } ;
typedef  TYPE_1__ kcf_context_t ;
struct TYPE_8__ {int an_refcnt; struct TYPE_8__* an_ctxchain_next; int /*<<< orphan*/  an_is_my_turn; int /*<<< orphan*/ * an_idprev; int /*<<< orphan*/  an_idnext; int /*<<< orphan*/ * an_tried_plist; int /*<<< orphan*/ * an_provider; int /*<<< orphan*/ * an_prev; int /*<<< orphan*/  an_next; int /*<<< orphan*/  an_isdual; TYPE_1__* an_context; int /*<<< orphan*/  an_params; int /*<<< orphan*/  an_reqarg; int /*<<< orphan*/  an_state; } ;
typedef  TYPE_2__ kcf_areq_node_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KCF_CONTEXT_REFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int /*<<< orphan*/  REQ_ALLOCATED ; 
 int /*<<< orphan*/  kcf_areq_cache ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static kcf_areq_node_t *
kcf_areqnode_alloc(kcf_provider_desc_t *pd, kcf_context_t *ictx,
    crypto_call_req_t *crq, kcf_req_params_t *req, boolean_t isdual)
{
	kcf_areq_node_t	*arptr, *areq;

	ASSERT(crq != NULL);
	arptr = kmem_cache_alloc(kcf_areq_cache, KM_NOSLEEP);
	if (arptr == NULL)
		return (NULL);

	arptr->an_state = REQ_ALLOCATED;
	arptr->an_reqarg = *crq;
	arptr->an_params = *req;
	arptr->an_context = ictx;
	arptr->an_isdual = isdual;

	arptr->an_next = arptr->an_prev = NULL;
	KCF_PROV_REFHOLD(pd);
	arptr->an_provider = pd;
	arptr->an_tried_plist = NULL;
	arptr->an_refcnt = 1;
	arptr->an_idnext = arptr->an_idprev = NULL;

	/*
	 * Requests for context-less operations do not use the
	 * fields - an_is_my_turn, and an_ctxchain_next.
	 */
	if (ictx == NULL)
		return (arptr);

	KCF_CONTEXT_REFHOLD(ictx);
	/*
	 * Chain this request to the context.
	 */
	mutex_enter(&ictx->kc_in_use_lock);
	arptr->an_ctxchain_next = NULL;
	if ((areq = ictx->kc_req_chain_last) == NULL) {
		arptr->an_is_my_turn = B_TRUE;
		ictx->kc_req_chain_last =
		    ictx->kc_req_chain_first = arptr;
	} else {
		ASSERT(ictx->kc_req_chain_first != NULL);
		arptr->an_is_my_turn = B_FALSE;
		/* Insert the new request to the end of the chain. */
		areq->an_ctxchain_next = arptr;
		ictx->kc_req_chain_last = arptr;
	}
	mutex_exit(&ictx->kc_in_use_lock);

	return (arptr);
}