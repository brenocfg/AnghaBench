#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_23__ {scalar_t__ pd_prov_type; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_context_t ;
typedef  int /*<<< orphan*/  crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  TYPE_1__* crypto_provider_t ;
struct TYPE_24__ {int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_3__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
struct TYPE_25__ {scalar_t__ cc_framework_private; } ;
typedef  TYPE_4__ crypto_ctx_t ;
typedef  scalar_t__ crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CHECK_FASTPATH (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_RESTRICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC ; 
 int CRYPTO_HOST_MEMORY ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int /*<<< orphan*/  CRYPTO_MECH_INVALID ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  KCF_CONTEXT_REFRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_OP_INIT ; 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_1__*,int) ; 
 int KCF_PROV_MAC_INIT (TYPE_1__*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCF_PROV_REFHELD (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_SET_PROVIDER_MECHNUM (int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  KCF_SWFP_RHNDL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_WRAP_MAC_OPS_PARAMS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kcf_get_hardware_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 TYPE_4__* kcf_new_ctx (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int kcf_submit_request (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_mac_init_prov(crypto_provider_t provider, crypto_session_id_t sid,
    crypto_mechanism_t *mech, crypto_key_t *key, crypto_spi_ctx_template_t tmpl,
    crypto_context_t *ctxp, crypto_call_req_t *crq)
{
	int rv;
	crypto_ctx_t *ctx;
	kcf_req_params_t params;
	kcf_provider_desc_t *pd = provider;
	kcf_provider_desc_t *real_provider = pd;

	ASSERT(KCF_PROV_REFHELD(pd));

	if (pd->pd_prov_type == CRYPTO_LOGICAL_PROVIDER) {
		rv = kcf_get_hardware_provider(mech->cm_type,
		    CRYPTO_MECH_INVALID, CHECK_RESTRICT(crq), pd,
		    &real_provider, CRYPTO_FG_MAC);

		if (rv != CRYPTO_SUCCESS)
			return (rv);
	}

	/* Allocate and initialize the canonical context */
	if ((ctx = kcf_new_ctx(crq, real_provider, sid)) == NULL) {
		if (pd->pd_prov_type == CRYPTO_LOGICAL_PROVIDER)
			KCF_PROV_REFRELE(real_provider);
		return (CRYPTO_HOST_MEMORY);
	}

	/* The fast path for SW providers. */
	if (CHECK_FASTPATH(crq, pd)) {
		crypto_mechanism_t lmech;

		lmech = *mech;
		KCF_SET_PROVIDER_MECHNUM(mech->cm_type, real_provider, &lmech);
		rv = KCF_PROV_MAC_INIT(real_provider, ctx, &lmech, key, tmpl,
		    KCF_SWFP_RHNDL(crq));
		KCF_PROV_INCRSTATS(pd, rv);
	} else {
		KCF_WRAP_MAC_OPS_PARAMS(&params, KCF_OP_INIT, sid, mech, key,
		    NULL, NULL, tmpl);
		rv = kcf_submit_request(real_provider, ctx, crq, &params,
		    B_FALSE);
	}

	if (pd->pd_prov_type == CRYPTO_LOGICAL_PROVIDER)
		KCF_PROV_REFRELE(real_provider);

	if ((rv == CRYPTO_SUCCESS) || (rv == CRYPTO_QUEUED))
		*ctxp = (crypto_context_t)ctx;
	else {
		/* Release the hold done in kcf_new_ctx(). */
		KCF_CONTEXT_REFRELE((kcf_context_t *)ctx->cc_framework_private);
	}

	return (rv);
}