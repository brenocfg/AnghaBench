#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  tq_nalloc; } ;
typedef  TYPE_2__ taskq_t ;
struct TYPE_33__ {int sn_rv; int /*<<< orphan*/  sn_lock; int /*<<< orphan*/  sn_cv; int /*<<< orphan*/  sn_state; TYPE_4__* sn_provider; int /*<<< orphan*/ * sn_context; int /*<<< orphan*/ * sn_params; } ;
typedef  TYPE_3__ kcf_sreq_node_t ;
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_31__ {TYPE_2__* ks_taskq; } ;
struct TYPE_34__ {int pd_prov_type; int pd_flags; int /*<<< orphan*/  pd_state; TYPE_1__ pd_sched_info; } ;
typedef  TYPE_4__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_context_t ;
typedef  TYPE_3__ kcf_areq_node_t ;
struct TYPE_35__ {scalar_t__ cc_framework_private; } ;
typedef  TYPE_6__ crypto_ctx_t ;
struct TYPE_36__ {int cr_flag; void* cr_reqid; } ;
typedef  TYPE_7__ crypto_call_req_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_ALWAYS_QUEUE ; 
 int CRYPTO_BUSY ; 
 void* CRYPTO_FAILED ; 
 int CRYPTO_HOST_MEMORY ; 
#define  CRYPTO_HW_PROVIDER 129 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SKIP_REQID ; 
 int CRYPTO_SUCCESS ; 
#define  CRYPTO_SW_PROVIDER 128 
 int CRYPTO_SYNCHRONOUS ; 
 int /*<<< orphan*/  EMPTY_TASKQ (TYPE_2__*) ; 
 int /*<<< orphan*/  KCF_AREQ_REFRELE (TYPE_3__*) ; 
 int /*<<< orphan*/  KCF_PROV_IREFHOLD (TYPE_4__*) ; 
 int /*<<< orphan*/  KCF_PROV_IREFRELE (TYPE_4__*) ; 
 int /*<<< orphan*/  KCF_PROV_READY ; 
 int KCF_PROV_REFHELD (TYPE_4__*) ; 
 int /*<<< orphan*/  KCF_RHNDL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  REQ_ALLOCATED ; 
 int /*<<< orphan*/  REQ_DONE ; 
 int /*<<< orphan*/  TASKQID_INVALID ; 
 int /*<<< orphan*/  TQ_NOSLEEP ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int common_submit_request (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_taskq_maxalloc ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* kcf_areqnode_alloc (TYPE_4__*,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kcf_disp_sw_request (TYPE_3__*) ; 
 int /*<<< orphan*/  kcf_reqid_delete (TYPE_3__*) ; 
 void* kcf_reqid_insert (TYPE_3__*) ; 
 int /*<<< orphan*/  kcf_sreq_cache ; 
 TYPE_3__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_req_hwp (TYPE_3__*) ; 
 int /*<<< orphan*/  taskq_dispatch (TYPE_2__*,int /*<<< orphan*/  (*) (TYPE_3__*),TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait (TYPE_2__*) ; 

int
kcf_submit_request(kcf_provider_desc_t *pd, crypto_ctx_t *ctx,
    crypto_call_req_t *crq, kcf_req_params_t *params, boolean_t cont)
{
	int error = CRYPTO_SUCCESS;
	kcf_areq_node_t *areq;
	kcf_sreq_node_t *sreq;
	kcf_context_t *kcf_ctx;
	taskq_t *taskq = pd->pd_sched_info.ks_taskq;

	kcf_ctx = ctx ? (kcf_context_t *)ctx->cc_framework_private : NULL;

	/* Synchronous cases */
	if (crq == NULL) {
		switch (pd->pd_prov_type) {
		case CRYPTO_SW_PROVIDER:
			error = common_submit_request(pd, ctx, params,
			    KCF_RHNDL(KM_SLEEP));
			break;

		case CRYPTO_HW_PROVIDER:
			/*
			 * Special case for CRYPTO_SYNCHRONOUS providers that
			 * never return a CRYPTO_QUEUED error. We skip any
			 * request allocation and call the SPI directly.
			 */
			if ((pd->pd_flags & CRYPTO_SYNCHRONOUS) &&
			    EMPTY_TASKQ(taskq)) {
				KCF_PROV_IREFHOLD(pd);
				if (pd->pd_state == KCF_PROV_READY) {
					error = common_submit_request(pd, ctx,
					    params, KCF_RHNDL(KM_SLEEP));
					KCF_PROV_IREFRELE(pd);
					ASSERT(error != CRYPTO_QUEUED);
					break;
				}
				KCF_PROV_IREFRELE(pd);
			}

			sreq = kmem_cache_alloc(kcf_sreq_cache, KM_SLEEP);
			sreq->sn_state = REQ_ALLOCATED;
			sreq->sn_rv = CRYPTO_FAILED;
			sreq->sn_params = params;

			/*
			 * Note that we do not need to hold the context
			 * for synchronous case as the context will never
			 * become invalid underneath us. We do not need to hold
			 * the provider here either as the caller has a hold.
			 */
			sreq->sn_context = kcf_ctx;
			ASSERT(KCF_PROV_REFHELD(pd));
			sreq->sn_provider = pd;

			ASSERT(taskq != NULL);
			/*
			 * Call the SPI directly if the taskq is empty and the
			 * provider is not busy, else dispatch to the taskq.
			 * Calling directly is fine as this is the synchronous
			 * case. This is unlike the asynchronous case where we
			 * must always dispatch to the taskq.
			 */
			if (EMPTY_TASKQ(taskq) &&
			    pd->pd_state == KCF_PROV_READY) {
				process_req_hwp(sreq);
			} else {
				/*
				 * We can not tell from taskq_dispatch() return
				 * value if we exceeded maxalloc. Hence the
				 * check here. Since we are allowed to wait in
				 * the synchronous case, we wait for the taskq
				 * to become empty.
				 */
				if (taskq->tq_nalloc >= crypto_taskq_maxalloc) {
					taskq_wait(taskq);
				}

				(void) taskq_dispatch(taskq, process_req_hwp,
				    sreq, TQ_SLEEP);
			}

			/*
			 * Wait for the notification to arrive,
			 * if the operation is not done yet.
			 * Bug# 4722589 will make the wait a cv_wait_sig().
			 */
			mutex_enter(&sreq->sn_lock);
			while (sreq->sn_state < REQ_DONE)
				cv_wait(&sreq->sn_cv, &sreq->sn_lock);
			mutex_exit(&sreq->sn_lock);

			error = sreq->sn_rv;
			kmem_cache_free(kcf_sreq_cache, sreq);

			break;

		default:
			error = CRYPTO_FAILED;
			break;
		}

	} else {	/* Asynchronous cases */
		switch (pd->pd_prov_type) {
		case CRYPTO_SW_PROVIDER:
			if (!(crq->cr_flag & CRYPTO_ALWAYS_QUEUE)) {
				/*
				 * This case has less overhead since there is
				 * no switching of context.
				 */
				error = common_submit_request(pd, ctx, params,
				    KCF_RHNDL(KM_NOSLEEP));
			} else {
				/*
				 * CRYPTO_ALWAYS_QUEUE is set. We need to
				 * queue the request and return.
				 */
				areq = kcf_areqnode_alloc(pd, kcf_ctx, crq,
				    params, cont);
				if (areq == NULL)
					error = CRYPTO_HOST_MEMORY;
				else {
					if (!(crq->cr_flag
					    & CRYPTO_SKIP_REQID)) {
					/*
					 * Set the request handle. This handle
					 * is used for any crypto_cancel_req(9f)
					 * calls from the consumer. We have to
					 * do this before dispatching the
					 * request.
					 */
					crq->cr_reqid = kcf_reqid_insert(areq);
					}

					error = kcf_disp_sw_request(areq);
					/*
					 * There is an error processing this
					 * request. Remove the handle and
					 * release the request structure.
					 */
					if (error != CRYPTO_QUEUED) {
						if (!(crq->cr_flag
						    & CRYPTO_SKIP_REQID))
							kcf_reqid_delete(areq);
						KCF_AREQ_REFRELE(areq);
					}
				}
			}
			break;

		case CRYPTO_HW_PROVIDER:
			/*
			 * We need to queue the request and return.
			 */
			areq = kcf_areqnode_alloc(pd, kcf_ctx, crq, params,
			    cont);
			if (areq == NULL) {
				error = CRYPTO_HOST_MEMORY;
				goto done;
			}

			ASSERT(taskq != NULL);
			/*
			 * We can not tell from taskq_dispatch() return
			 * value if we exceeded maxalloc. Hence the check
			 * here.
			 */
			if (taskq->tq_nalloc >= crypto_taskq_maxalloc) {
				error = CRYPTO_BUSY;
				KCF_AREQ_REFRELE(areq);
				goto done;
			}

			if (!(crq->cr_flag & CRYPTO_SKIP_REQID)) {
			/*
			 * Set the request handle. This handle is used
			 * for any crypto_cancel_req(9f) calls from the
			 * consumer. We have to do this before dispatching
			 * the request.
			 */
			crq->cr_reqid = kcf_reqid_insert(areq);
			}

			if (taskq_dispatch(taskq,
			    process_req_hwp, areq, TQ_NOSLEEP) ==
			    TASKQID_INVALID) {
				error = CRYPTO_HOST_MEMORY;
				if (!(crq->cr_flag & CRYPTO_SKIP_REQID))
					kcf_reqid_delete(areq);
				KCF_AREQ_REFRELE(areq);
			} else {
				error = CRYPTO_QUEUED;
			}
			break;

		default:
			error = CRYPTO_FAILED;
			break;
		}
	}

done:
	return (error);
}