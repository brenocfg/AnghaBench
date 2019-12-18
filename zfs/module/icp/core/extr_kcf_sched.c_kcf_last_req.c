#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ dop_ciphertext; } ;
struct TYPE_14__ {scalar_t__ mo_data; } ;
struct TYPE_12__ {TYPE_5__ decrypt_params; TYPE_3__ mac_params; } ;
struct TYPE_13__ {int rp_opgrp; TYPE_1__ rp_u; } ;
typedef  TYPE_2__ kcf_req_params_t ;
typedef  TYPE_3__ kcf_mac_ops_params_t ;
struct TYPE_19__ {int /*<<< orphan*/  cr_callback_arg; int /*<<< orphan*/  (* cr_callback_func ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_15__ {TYPE_8__ kr_callreq; int /*<<< orphan*/  kr_savelen; int /*<<< orphan*/  kr_saveoffset; TYPE_6__* kr_areq; TYPE_2__ kr_params; } ;
typedef  TYPE_4__ kcf_dual_req_t ;
typedef  TYPE_5__ kcf_decrypt_ops_params_t ;
struct TYPE_17__ {int /*<<< orphan*/  an_isdual; TYPE_8__ an_reqarg; } ;
typedef  TYPE_6__ kcf_areq_node_t ;
struct TYPE_18__ {int /*<<< orphan*/  dd_len1; int /*<<< orphan*/  dd_offset1; } ;
typedef  TYPE_7__ crypto_dual_data_t ;
typedef  TYPE_8__ crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KCF_AREQ_REFRELE (TYPE_6__*) ; 
#define  KCF_OG_DECRYPT 129 
#define  KCF_OG_MAC 128 
 int /*<<< orphan*/  kcf_aop_done (TYPE_6__*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void
kcf_last_req(void *last_req_arg, int status)
{
	kcf_dual_req_t *last_req = (kcf_dual_req_t *)last_req_arg;

	kcf_req_params_t *params = &(last_req->kr_params);
	kcf_areq_node_t *areq = last_req->kr_areq;
	crypto_dual_data_t *ct = NULL;

	switch (params->rp_opgrp) {
	case KCF_OG_MAC: {
		kcf_mac_ops_params_t *mops = &(params->rp_u.mac_params);

		ct = (crypto_dual_data_t *)mops->mo_data;
		break;
	}
	case KCF_OG_DECRYPT: {
		kcf_decrypt_ops_params_t *dcrops =
		    &(params->rp_u.decrypt_params);

		ct = (crypto_dual_data_t *)dcrops->dop_ciphertext;
		break;
	}
	default: {
		panic("invalid kcf_op_group_t %d", (int)params->rp_opgrp);
		return;
	}
	}
	ct->dd_offset1 = last_req->kr_saveoffset;
	ct->dd_len1 = last_req->kr_savelen;

	/* The submitter used kcf_last_req as its callback */

	if (areq == NULL) {
		crypto_call_req_t *cr = &last_req->kr_callreq;

		(*(cr->cr_callback_func))(cr->cr_callback_arg, status);
		kmem_free(last_req, sizeof (kcf_dual_req_t));
		return;
	}
	areq->an_reqarg = last_req->kr_callreq;
	KCF_AREQ_REFRELE(areq);
	kmem_free(last_req, sizeof (kcf_dual_req_t));
	areq->an_isdual = B_FALSE;
	kcf_aop_done(areq, status);
}