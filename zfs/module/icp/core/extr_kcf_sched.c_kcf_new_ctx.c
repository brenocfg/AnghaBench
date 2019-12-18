#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pd_prov_handle; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_10__ {int /*<<< orphan*/ * cc_opstate; scalar_t__ cc_flags; void* cc_framework_private; int /*<<< orphan*/ * cc_provider_private; int /*<<< orphan*/  cc_session; int /*<<< orphan*/  cc_provider; } ;
struct TYPE_9__ {int kc_refcnt; TYPE_3__ kc_glbl_ctx; int /*<<< orphan*/ * kc_mech; int /*<<< orphan*/ * kc_sw_prov_desc; TYPE_1__* kc_prov_desc; int /*<<< orphan*/ * kc_secondctx; int /*<<< orphan*/ * kc_req_chain_last; int /*<<< orphan*/ * kc_req_chain_first; } ;
typedef  TYPE_2__ kcf_context_t ;
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  TYPE_3__ crypto_ctx_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_PROV_REFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kcf_context_cache ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

crypto_ctx_t *
kcf_new_ctx(crypto_call_req_t *crq, kcf_provider_desc_t *pd,
    crypto_session_id_t sid)
{
	crypto_ctx_t *ctx;
	kcf_context_t *kcf_ctx;

	kcf_ctx = kmem_cache_alloc(kcf_context_cache,
	    (crq == NULL) ? KM_SLEEP : KM_NOSLEEP);
	if (kcf_ctx == NULL)
		return (NULL);

	/* initialize the context for the consumer */
	kcf_ctx->kc_refcnt = 1;
	kcf_ctx->kc_req_chain_first = NULL;
	kcf_ctx->kc_req_chain_last = NULL;
	kcf_ctx->kc_secondctx = NULL;
	KCF_PROV_REFHOLD(pd);
	kcf_ctx->kc_prov_desc = pd;
	kcf_ctx->kc_sw_prov_desc = NULL;
	kcf_ctx->kc_mech = NULL;

	ctx = &kcf_ctx->kc_glbl_ctx;
	ctx->cc_provider = pd->pd_prov_handle;
	ctx->cc_session = sid;
	ctx->cc_provider_private = NULL;
	ctx->cc_framework_private = (void *)kcf_ctx;
	ctx->cc_flags = 0;
	ctx->cc_opstate = NULL;

	return (ctx);
}