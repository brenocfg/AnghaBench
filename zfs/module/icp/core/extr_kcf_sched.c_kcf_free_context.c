#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pd_lock; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_15__ {int cc_flags; int /*<<< orphan*/ * cc_provider_private; } ;
struct TYPE_14__ {TYPE_1__* kc_sw_prov_desc; TYPE_1__* kc_prov_desc; struct TYPE_14__* kc_secondctx; TYPE_3__ kc_glbl_ctx; } ;
typedef  TYPE_2__ kcf_context_t ;
typedef  TYPE_3__ crypto_ctx_t ;

/* Variables and functions */
 int CRYPTO_INIT_OPSTATE ; 
 int /*<<< orphan*/  KCF_CONTEXT_REFRELE (TYPE_2__*) ; 
 int /*<<< orphan*/  KCF_IS_PROV_REMOVED (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_FREE_CONTEXT (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  KCF_PROV_IREFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_IREFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  kcf_context_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
kcf_free_context(kcf_context_t *kcf_ctx)
{
	kcf_provider_desc_t *pd = kcf_ctx->kc_prov_desc;
	crypto_ctx_t *gctx = &kcf_ctx->kc_glbl_ctx;
	kcf_context_t *kcf_secondctx = kcf_ctx->kc_secondctx;

	/* Release the second context, if any */

	if (kcf_secondctx != NULL)
		KCF_CONTEXT_REFRELE(kcf_secondctx);

	if (gctx->cc_provider_private != NULL) {
		mutex_enter(&pd->pd_lock);
		if (!KCF_IS_PROV_REMOVED(pd)) {
			/*
			 * Increment the provider's internal refcnt so it
			 * doesn't unregister from the framework while
			 * we're calling the entry point.
			 */
			KCF_PROV_IREFHOLD(pd);
			mutex_exit(&pd->pd_lock);
			(void) KCF_PROV_FREE_CONTEXT(pd, gctx);
			KCF_PROV_IREFRELE(pd);
		} else {
			mutex_exit(&pd->pd_lock);
		}
	}

	/* kcf_ctx->kc_prov_desc has a hold on pd */
	KCF_PROV_REFRELE(kcf_ctx->kc_prov_desc);

	/* check if this context is shared with a software provider */
	if ((gctx->cc_flags & CRYPTO_INIT_OPSTATE) &&
	    kcf_ctx->kc_sw_prov_desc != NULL) {
		KCF_PROV_REFRELE(kcf_ctx->kc_sw_prov_desc);
	}

	kmem_cache_free(kcf_context_cache, kcf_ctx);
}