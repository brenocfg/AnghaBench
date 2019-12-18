#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_11__ {scalar_t__ pd_prov_type; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_12__ {TYPE_1__* kc_prov_desc; } ;
typedef  TYPE_2__ kcf_context_t ;
typedef  int /*<<< orphan*/  crypto_data_t ;
struct TYPE_13__ {int /*<<< orphan*/  cc_session; scalar_t__ cc_framework_private; } ;
typedef  TYPE_3__ crypto_ctx_t ;
typedef  scalar_t__ crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CHECK_FASTPATH (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CRYPTO_INVALID_CONTEXT ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int /*<<< orphan*/  KCF_CONTEXT_COND_RELEASE (int,TYPE_2__*) ; 
 int /*<<< orphan*/  KCF_OP_FINAL ; 
 int KCF_PROV_DIGEST_FINAL (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KCF_WRAP_DIGEST_OPS_PARAMS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kcf_submit_request (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_digest_final(crypto_context_t context, crypto_data_t *digest,
    crypto_call_req_t *cr)
{
	crypto_ctx_t *ctx = (crypto_ctx_t *)context;
	kcf_context_t *kcf_ctx;
	kcf_provider_desc_t *pd;
	int error;
	kcf_req_params_t params;

	if ((ctx == NULL) ||
	    ((kcf_ctx = (kcf_context_t *)ctx->cc_framework_private) == NULL) ||
	    ((pd = kcf_ctx->kc_prov_desc) == NULL)) {
		return (CRYPTO_INVALID_CONTEXT);
	}

	ASSERT(pd->pd_prov_type != CRYPTO_LOGICAL_PROVIDER);

	/* The fast path for SW providers. */
	if (CHECK_FASTPATH(cr, pd)) {
		error = KCF_PROV_DIGEST_FINAL(pd, ctx, digest, NULL);
		KCF_PROV_INCRSTATS(pd, error);
	} else {
		KCF_WRAP_DIGEST_OPS_PARAMS(&params, KCF_OP_FINAL,
		    ctx->cc_session, NULL, NULL, NULL, digest);
		error = kcf_submit_request(pd, ctx, cr, &params, B_FALSE);
	}

	/* Release the hold done in kcf_new_ctx() during init step. */
	KCF_CONTEXT_COND_RELEASE(error, kcf_ctx);
	return (error);
}