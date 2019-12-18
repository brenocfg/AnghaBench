#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  void* off_t ;
struct TYPE_29__ {int /*<<< orphan*/ * md_mac; int /*<<< orphan*/ * md_plaintext; TYPE_7__* md_ciphertext; int /*<<< orphan*/  md_decr_templ; int /*<<< orphan*/  md_decr_key; int /*<<< orphan*/  md_decr_mech; int /*<<< orphan*/  md_mac_templ; int /*<<< orphan*/  md_mac_key; int /*<<< orphan*/  md_mac_mech; } ;
struct TYPE_30__ {int /*<<< orphan*/ * em_mac; TYPE_7__* em_ciphertext; int /*<<< orphan*/ * em_plaintext; int /*<<< orphan*/  em_mac_templ; int /*<<< orphan*/  em_mac_key; int /*<<< orphan*/  em_mac_mech; int /*<<< orphan*/ * em_encr_templ; int /*<<< orphan*/ * em_encr_key; int /*<<< orphan*/  em_encr_mech; } ;
struct TYPE_26__ {TYPE_4__ mac_decrypt_params; TYPE_5__ encrypt_mac_params; } ;
struct TYPE_27__ {int rp_opgrp; TYPE_1__ rp_u; int /*<<< orphan*/  rp_optype; } ;
typedef  TYPE_2__ kcf_req_params_t ;
struct TYPE_28__ {int /*<<< orphan*/  pd_sid; } ;
typedef  TYPE_3__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_op_type_t ;
typedef  TYPE_4__ kcf_mac_decrypt_ops_params_t ;
typedef  TYPE_5__ kcf_encrypt_mac_ops_params_t ;
struct TYPE_33__ {scalar_t__ cc_framework_private; } ;
struct TYPE_31__ {TYPE_8__ kc_glbl_ctx; struct TYPE_31__* kc_secondctx; } ;
typedef  TYPE_6__ kcf_context_t ;
struct TYPE_32__ {size_t dd_len1; size_t dd_len2; void* dd_offset1; void* dd_offset2; } ;
typedef  TYPE_7__ crypto_dual_data_t ;
typedef  int /*<<< orphan*/  crypto_data_t ;
typedef  TYPE_8__ crypto_ctx_t ;
typedef  TYPE_8__* crypto_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  KCF_CONTEXT_REFHOLD (TYPE_6__*) ; 
#define  KCF_OG_ENCRYPT_MAC 132 
#define  KCF_OG_MAC_DECRYPT 131 
#define  KCF_OP_FINAL 130 
#define  KCF_OP_INIT 129 
#define  KCF_OP_UPDATE 128 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_3__*,int) ; 
 int /*<<< orphan*/  KCF_WRAP_DECRYPT_OPS_PARAMS (TYPE_2__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCF_WRAP_ENCRYPT_OPS_PARAMS (TYPE_2__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_cancel_ctx (TYPE_8__*) ; 
 int crypto_decrypt_final (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_decrypt_update (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_mac_final (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_mac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__**,int /*<<< orphan*/ *) ; 
 int crypto_mac_update (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kcf_submit_request (TYPE_3__*,TYPE_8__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kcf_emulate_dual(kcf_provider_desc_t *pd, crypto_ctx_t *ctx,
    kcf_req_params_t *params)
{
	int err = CRYPTO_ARGUMENTS_BAD;
	kcf_op_type_t optype;
	size_t save_len;
	off_t save_offset;

	optype = params->rp_optype;

	switch (params->rp_opgrp) {
	case KCF_OG_ENCRYPT_MAC: {
		kcf_encrypt_mac_ops_params_t *cmops =
		    &params->rp_u.encrypt_mac_params;
		kcf_context_t *encr_kcf_ctx;
		crypto_ctx_t *mac_ctx;
		kcf_req_params_t encr_params;

		encr_kcf_ctx = (kcf_context_t *)(ctx->cc_framework_private);

		switch (optype) {
		case KCF_OP_INIT: {
			encr_kcf_ctx->kc_secondctx = NULL;

			KCF_WRAP_ENCRYPT_OPS_PARAMS(&encr_params, KCF_OP_INIT,
			    pd->pd_sid, &cmops->em_encr_mech,
			    cmops->em_encr_key, NULL, NULL,
			    cmops->em_encr_templ);

			err = kcf_submit_request(pd, ctx, NULL, &encr_params,
			    B_FALSE);

			/* It can't be CRYPTO_QUEUED */
			if (err != CRYPTO_SUCCESS) {
				break;
			}

			err = crypto_mac_init(&cmops->em_mac_mech,
			    cmops->em_mac_key, cmops->em_mac_templ,
			    (crypto_context_t *)&mac_ctx, NULL);

			if (err == CRYPTO_SUCCESS) {
				encr_kcf_ctx->kc_secondctx = (kcf_context_t *)
				    mac_ctx->cc_framework_private;
				KCF_CONTEXT_REFHOLD((kcf_context_t *)
				    mac_ctx->cc_framework_private);
			}

			break;

		}
		case KCF_OP_UPDATE: {
			crypto_dual_data_t *ct = cmops->em_ciphertext;
			crypto_data_t *pt = cmops->em_plaintext;
			kcf_context_t *mac_kcf_ctx = encr_kcf_ctx->kc_secondctx;
			crypto_ctx_t *mac_ctx = &mac_kcf_ctx->kc_glbl_ctx;

			KCF_WRAP_ENCRYPT_OPS_PARAMS(&encr_params, KCF_OP_UPDATE,
			    pd->pd_sid, NULL, NULL, pt, (crypto_data_t *)ct,
			    NULL);

			err = kcf_submit_request(pd, ctx, NULL, &encr_params,
			    B_FALSE);

			/* It can't be CRYPTO_QUEUED */
			if (err != CRYPTO_SUCCESS) {
				break;
			}

			save_offset = ct->dd_offset1;
			save_len = ct->dd_len1;
			if (ct->dd_len2 == 0) {
				/*
				 * The previous encrypt step was an
				 * accumulation only and didn't produce any
				 * partial output
				 */
				if (ct->dd_len1 == 0)
					break;

			} else {
				ct->dd_offset1 = ct->dd_offset2;
				ct->dd_len1 = ct->dd_len2;
			}
			err = crypto_mac_update((crypto_context_t)mac_ctx,
			    (crypto_data_t *)ct, NULL);

			ct->dd_offset1 = save_offset;
			ct->dd_len1 = save_len;

			break;
		}
		case KCF_OP_FINAL: {
			crypto_dual_data_t *ct = cmops->em_ciphertext;
			crypto_data_t *mac = cmops->em_mac;
			kcf_context_t *mac_kcf_ctx = encr_kcf_ctx->kc_secondctx;
			crypto_ctx_t *mac_ctx = &mac_kcf_ctx->kc_glbl_ctx;
			crypto_context_t mac_context = mac_ctx;

			KCF_WRAP_ENCRYPT_OPS_PARAMS(&encr_params, KCF_OP_FINAL,
			    pd->pd_sid, NULL, NULL, NULL, (crypto_data_t *)ct,
			    NULL);

			err = kcf_submit_request(pd, ctx, NULL, &encr_params,
			    B_FALSE);

			/* It can't be CRYPTO_QUEUED */
			if (err != CRYPTO_SUCCESS) {
				crypto_cancel_ctx(mac_context);
				break;
			}

			if (ct->dd_len2 > 0) {
				save_offset = ct->dd_offset1;
				save_len = ct->dd_len1;
				ct->dd_offset1 = ct->dd_offset2;
				ct->dd_len1 = ct->dd_len2;

				err = crypto_mac_update(mac_context,
				    (crypto_data_t *)ct, NULL);

				ct->dd_offset1 = save_offset;
				ct->dd_len1 = save_len;

				if (err != CRYPTO_SUCCESS)  {
					crypto_cancel_ctx(mac_context);
					return (err);
				}
			}

			/* and finally, collect the MAC */
			err = crypto_mac_final(mac_context, mac, NULL);
			break;
		}

		default:
			break;
		}
		KCF_PROV_INCRSTATS(pd, err);
		break;
	}
	case KCF_OG_MAC_DECRYPT: {
		kcf_mac_decrypt_ops_params_t *mdops =
		    &params->rp_u.mac_decrypt_params;
		kcf_context_t *decr_kcf_ctx;
		crypto_ctx_t *mac_ctx;
		kcf_req_params_t decr_params;

		decr_kcf_ctx = (kcf_context_t *)(ctx->cc_framework_private);

		switch (optype) {
		case KCF_OP_INIT: {
			decr_kcf_ctx->kc_secondctx = NULL;

			err = crypto_mac_init(&mdops->md_mac_mech,
			    mdops->md_mac_key, mdops->md_mac_templ,
			    (crypto_context_t *)&mac_ctx, NULL);

			/* It can't be CRYPTO_QUEUED */
			if (err != CRYPTO_SUCCESS) {
				break;
			}

			KCF_WRAP_DECRYPT_OPS_PARAMS(&decr_params, KCF_OP_INIT,
			    pd->pd_sid, &mdops->md_decr_mech,
			    mdops->md_decr_key, NULL, NULL,
			    mdops->md_decr_templ);

			err = kcf_submit_request(pd, ctx, NULL, &decr_params,
			    B_FALSE);

			/* It can't be CRYPTO_QUEUED */
			if (err != CRYPTO_SUCCESS) {
				crypto_cancel_ctx((crypto_context_t)mac_ctx);
				break;
			}

			decr_kcf_ctx->kc_secondctx = (kcf_context_t *)
			    mac_ctx->cc_framework_private;
			KCF_CONTEXT_REFHOLD((kcf_context_t *)
			    mac_ctx->cc_framework_private);

			break;
		default:
			break;

		}
		case KCF_OP_UPDATE: {
			crypto_dual_data_t *ct = mdops->md_ciphertext;
			crypto_data_t *pt = mdops->md_plaintext;
			kcf_context_t *mac_kcf_ctx = decr_kcf_ctx->kc_secondctx;
			crypto_ctx_t *mac_ctx = &mac_kcf_ctx->kc_glbl_ctx;

			err = crypto_mac_update((crypto_context_t)mac_ctx,
			    (crypto_data_t *)ct, NULL);

			if (err != CRYPTO_SUCCESS)
				break;

			save_offset = ct->dd_offset1;
			save_len = ct->dd_len1;

			/* zero ct->dd_len2 means decrypt everything */
			if (ct->dd_len2 > 0) {
				ct->dd_offset1 = ct->dd_offset2;
				ct->dd_len1 = ct->dd_len2;
			}

			err = crypto_decrypt_update((crypto_context_t)ctx,
			    (crypto_data_t *)ct, pt, NULL);

			ct->dd_offset1 = save_offset;
			ct->dd_len1 = save_len;

			break;
		}
		case KCF_OP_FINAL: {
			crypto_data_t *pt = mdops->md_plaintext;
			crypto_data_t *mac = mdops->md_mac;
			kcf_context_t *mac_kcf_ctx = decr_kcf_ctx->kc_secondctx;
			crypto_ctx_t *mac_ctx = &mac_kcf_ctx->kc_glbl_ctx;

			err = crypto_mac_final((crypto_context_t)mac_ctx,
			    mac, NULL);

			if (err != CRYPTO_SUCCESS) {
				crypto_cancel_ctx(ctx);
				break;
			}

			/* Get the last chunk of plaintext */
			KCF_CONTEXT_REFHOLD(decr_kcf_ctx);
			err = crypto_decrypt_final((crypto_context_t)ctx, pt,
			    NULL);

			break;
		}
		}
		break;
	}
	default:

		break;
	}		/* end of switch(params->rp_opgrp) */

	return (err);
}