#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_10__ {scalar_t__ pd_prov_type; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_11__ {TYPE_1__* kc_prov_desc; } ;
typedef  TYPE_2__ kcf_context_t ;
typedef  int /*<<< orphan*/  crypto_data_t ;
struct TYPE_12__ {int /*<<< orphan*/  cc_session; scalar_t__ cc_framework_private; } ;
typedef  TYPE_3__ crypto_ctx_t ;
typedef  scalar_t__ crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CHECK_FASTPATH (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CRYPTO_INVALID_CONTEXT ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int /*<<< orphan*/  KCF_OP_UPDATE ; 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_1__*,int) ; 
 int KCF_PROV_MAC_UPDATE (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_WRAP_MAC_OPS_PARAMS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kcf_submit_request (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_mac_update(crypto_context_t context, crypto_data_t *data,
    crypto_call_req_t *cr)
{
	crypto_ctx_t *ctx = (crypto_ctx_t *)context;
	kcf_context_t *kcf_ctx;
	kcf_provider_desc_t *pd;
	kcf_req_params_t params;
	int rv;

	if ((ctx == NULL) ||
	    ((kcf_ctx = (kcf_context_t *)ctx->cc_framework_private) == NULL) ||
	    ((pd = kcf_ctx->kc_prov_desc) == NULL)) {
		return (CRYPTO_INVALID_CONTEXT);
	}

	ASSERT(pd->pd_prov_type != CRYPTO_LOGICAL_PROVIDER);

	/* The fast path for SW providers. */
	if (CHECK_FASTPATH(cr, pd)) {
		rv = KCF_PROV_MAC_UPDATE(pd, ctx, data, NULL);
		KCF_PROV_INCRSTATS(pd, rv);
	} else {
		KCF_WRAP_MAC_OPS_PARAMS(&params, KCF_OP_UPDATE,
		    ctx->cc_session, NULL, NULL, data, NULL, NULL);
		rv = kcf_submit_request(pd, ctx, cr, &params, B_FALSE);
	}

	return (rv);
}