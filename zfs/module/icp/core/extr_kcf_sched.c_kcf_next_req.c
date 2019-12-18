#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  taskqid_t ;
typedef  int /*<<< orphan*/  taskq_t ;
struct TYPE_34__ {int /*<<< orphan*/  dop_framework_mechtype; scalar_t__ dop_ciphertext; } ;
struct TYPE_32__ {int /*<<< orphan*/  mo_templ; int /*<<< orphan*/  mo_framework_mechtype; scalar_t__ mo_data; } ;
struct TYPE_26__ {TYPE_9__ decrypt_params; TYPE_7__ mac_params; } ;
struct TYPE_29__ {int rp_opgrp; TYPE_1__ rp_u; } ;
typedef  TYPE_4__ kcf_req_params_t ;
struct TYPE_27__ {int /*<<< orphan*/ * ks_taskq; } ;
struct TYPE_30__ {int pd_prov_type; TYPE_2__ pd_sched_info; } ;
typedef  TYPE_5__ kcf_provider_desc_t ;
struct TYPE_31__ {int /*<<< orphan*/  me_gen_swprov; } ;
typedef  TYPE_6__ kcf_mech_entry_t ;
typedef  TYPE_7__ kcf_mac_ops_params_t ;
struct TYPE_28__ {int cr_flag; TYPE_8__* cr_callback_arg; int /*<<< orphan*/  cr_callback_func; } ;
struct TYPE_33__ {TYPE_3__ kr_callreq; int /*<<< orphan*/  kr_savelen; int /*<<< orphan*/  kr_saveoffset; TYPE_11__* kr_areq; TYPE_4__ kr_params; } ;
typedef  TYPE_8__ kcf_dual_req_t ;
typedef  TYPE_9__ kcf_decrypt_ops_params_t ;
struct TYPE_23__ {int /*<<< orphan*/  ct_prov_tmpl; int /*<<< orphan*/  ct_generation; } ;
typedef  TYPE_10__ kcf_ctx_template_t ;
struct TYPE_24__ {void* an_isdual; TYPE_3__ an_reqarg; TYPE_5__* an_provider; TYPE_4__ an_params; } ;
typedef  TYPE_11__ kcf_areq_node_t ;
struct TYPE_25__ {int /*<<< orphan*/  dd_len1; int /*<<< orphan*/  dd_offset1; int /*<<< orphan*/  dd_len2; int /*<<< orphan*/  dd_offset2; } ;
typedef  TYPE_12__ crypto_dual_data_t ;
typedef  int /*<<< orphan*/ * crypto_ctx_template_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  CRYPTO_FG_DECRYPT_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC_ATOMIC ; 
 int CRYPTO_HOST_MEMORY ; 
#define  CRYPTO_HW_PROVIDER 131 
 int CRYPTO_MECH_NOT_SUPPORTED ; 
 int CRYPTO_OLD_CTX_TEMPLATE ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_RESTRICTED ; 
 int CRYPTO_SUCCESS ; 
#define  CRYPTO_SW_PROVIDER 130 
 int /*<<< orphan*/  KCF_AREQ_REFRELE (TYPE_11__*) ; 
#define  KCF_OG_DECRYPT 129 
#define  KCF_OG_MAC 128 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (TYPE_5__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_5__*) ; 
 int /*<<< orphan*/  KCF_RHNDL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int /*<<< orphan*/  TQ_NOSLEEP ; 
 int common_submit_request (TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcf_aop_done (TYPE_11__*,int) ; 
 TYPE_5__* kcf_get_mech_provider (int /*<<< orphan*/ ,TYPE_6__**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcf_last_req ; 
 int /*<<< orphan*/  kmem_free (TYPE_8__*,int) ; 
 int /*<<< orphan*/  process_req_hwp ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 

void
kcf_next_req(void *next_req_arg, int status)
{
	kcf_dual_req_t *next_req = (kcf_dual_req_t *)next_req_arg;
	kcf_req_params_t *params = &(next_req->kr_params);
	kcf_areq_node_t *areq = next_req->kr_areq;
	int error = status;
	kcf_provider_desc_t *pd = NULL;
	crypto_dual_data_t *ct = NULL;

	/* Stop the processing if an error occurred at this step */
	if (error != CRYPTO_SUCCESS) {
out:
		areq->an_reqarg = next_req->kr_callreq;
		KCF_AREQ_REFRELE(areq);
		kmem_free(next_req, sizeof (kcf_dual_req_t));
		areq->an_isdual = B_FALSE;
		kcf_aop_done(areq, error);
		return;
	}

	switch (params->rp_opgrp) {
	case KCF_OG_MAC: {

		/*
		 * The next req is submitted with the same reqid as the
		 * first part. The consumer only got back that reqid, and
		 * should still be able to cancel the operation during its
		 * second step.
		 */
		kcf_mac_ops_params_t *mops = &(params->rp_u.mac_params);
		crypto_ctx_template_t mac_tmpl;
		kcf_mech_entry_t *me;

		ct = (crypto_dual_data_t *)mops->mo_data;
		mac_tmpl = (crypto_ctx_template_t)mops->mo_templ;

		/* No expected recoverable failures, so no retry list */
		pd = kcf_get_mech_provider(mops->mo_framework_mechtype,
		    &me, &error, NULL, CRYPTO_FG_MAC_ATOMIC,
		    (areq->an_reqarg.cr_flag & CRYPTO_RESTRICTED), ct->dd_len2);

		if (pd == NULL) {
			error = CRYPTO_MECH_NOT_SUPPORTED;
			goto out;
		}
		/* Validate the MAC context template here */
		if ((pd->pd_prov_type == CRYPTO_SW_PROVIDER) &&
		    (mac_tmpl != NULL)) {
			kcf_ctx_template_t *ctx_mac_tmpl;

			ctx_mac_tmpl = (kcf_ctx_template_t *)mac_tmpl;

			if (ctx_mac_tmpl->ct_generation != me->me_gen_swprov) {
				KCF_PROV_REFRELE(pd);
				error = CRYPTO_OLD_CTX_TEMPLATE;
				goto out;
			}
			mops->mo_templ = ctx_mac_tmpl->ct_prov_tmpl;
		}

		break;
	}
	case KCF_OG_DECRYPT: {
		kcf_decrypt_ops_params_t *dcrops =
		    &(params->rp_u.decrypt_params);

		ct = (crypto_dual_data_t *)dcrops->dop_ciphertext;
		/* No expected recoverable failures, so no retry list */
		pd = kcf_get_mech_provider(dcrops->dop_framework_mechtype,
		    NULL, &error, NULL, CRYPTO_FG_DECRYPT_ATOMIC,
		    (areq->an_reqarg.cr_flag & CRYPTO_RESTRICTED), ct->dd_len1);

		if (pd == NULL) {
			error = CRYPTO_MECH_NOT_SUPPORTED;
			goto out;
		}
		break;
	}
	default:
		break;
	}

	/* The second step uses len2 and offset2 of the dual_data */
	next_req->kr_saveoffset = ct->dd_offset1;
	next_req->kr_savelen = ct->dd_len1;
	ct->dd_offset1 = ct->dd_offset2;
	ct->dd_len1 = ct->dd_len2;

	/* preserve if the caller is restricted */
	if (areq->an_reqarg.cr_flag & CRYPTO_RESTRICTED) {
		areq->an_reqarg.cr_flag = CRYPTO_RESTRICTED;
	} else {
		areq->an_reqarg.cr_flag = 0;
	}

	areq->an_reqarg.cr_callback_func = kcf_last_req;
	areq->an_reqarg.cr_callback_arg = next_req;
	areq->an_isdual = B_TRUE;

	/*
	 * We would like to call kcf_submit_request() here. But,
	 * that is not possible as that routine allocates a new
	 * kcf_areq_node_t request structure, while we need to
	 * reuse the existing request structure.
	 */
	switch (pd->pd_prov_type) {
	case CRYPTO_SW_PROVIDER:
		error = common_submit_request(pd, NULL, params,
		    KCF_RHNDL(KM_NOSLEEP));
		break;

	case CRYPTO_HW_PROVIDER: {
		kcf_provider_desc_t *old_pd;
		taskq_t *taskq = pd->pd_sched_info.ks_taskq;

		/*
		 * Set the params for the second step in the
		 * dual-ops.
		 */
		areq->an_params = *params;
		old_pd = areq->an_provider;
		KCF_PROV_REFRELE(old_pd);
		KCF_PROV_REFHOLD(pd);
		areq->an_provider = pd;

		/*
		 * Note that we have to do a taskq_dispatch()
		 * here as we may be in interrupt context.
		 */
		if (taskq_dispatch(taskq, process_req_hwp, areq,
		    TQ_NOSLEEP) == (taskqid_t)0) {
			error = CRYPTO_HOST_MEMORY;
		} else {
			error = CRYPTO_QUEUED;
		}
		break;
	}
	default:
		break;
	}

	/*
	 * We have to release the holds on the request and the provider
	 * in all cases.
	 */
	KCF_AREQ_REFRELE(areq);
	KCF_PROV_REFRELE(pd);

	if (error != CRYPTO_QUEUED) {
		/* restore, clean up, and invoke the client's callback */

		ct->dd_offset1 = next_req->kr_saveoffset;
		ct->dd_len1 = next_req->kr_savelen;
		areq->an_reqarg = next_req->kr_callreq;
		kmem_free(next_req, sizeof (kcf_dual_req_t));
		areq->an_isdual = B_FALSE;
		kcf_aop_done(areq, error);
	}
}