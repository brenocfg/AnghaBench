#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ pd_prov_type; int /*<<< orphan*/  pd_sid; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_tried_t ;
struct TYPE_13__ {scalar_t__ me_gen_swprov; } ;
typedef  TYPE_2__ kcf_mech_entry_t ;
struct TYPE_14__ {scalar_t__ ct_generation; int /*<<< orphan*/ * ct_prov_tmpl; } ;
typedef  TYPE_3__ kcf_ctx_template_t ;
typedef  int /*<<< orphan*/ * crypto_spi_ctx_template_t ;
struct TYPE_15__ {int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_4__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
typedef  int /*<<< orphan*/  crypto_func_group_t ;
typedef  scalar_t__ crypto_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RESTRICT (int /*<<< orphan*/ *) ; 
 int CRYPTO_OLD_CTX_TEMPLATE ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ CRYPTO_SW_PROVIDER ; 
 scalar_t__ IS_RECOVERABLE (int) ; 
 int /*<<< orphan*/  KCF_KMFLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int crypto_cipher_init_prov (TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcf_free_triedlist (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcf_get_mech_provider (int /*<<< orphan*/ ,TYPE_2__**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcf_insert_triedlist (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
crypto_cipher_init(crypto_mechanism_t *mech, crypto_key_t *key,
    crypto_ctx_template_t tmpl, crypto_context_t *ctxp,
    crypto_call_req_t *crq, crypto_func_group_t func)
{
	int error;
	kcf_mech_entry_t *me;
	kcf_provider_desc_t *pd;
	kcf_ctx_template_t *ctx_tmpl;
	crypto_spi_ctx_template_t spi_ctx_tmpl = NULL;
	kcf_prov_tried_t *list = NULL;

retry:
	/* pd is returned held */
	if ((pd = kcf_get_mech_provider(mech->cm_type, &me, &error,
	    list, func, CHECK_RESTRICT(crq), 0)) == NULL) {
		if (list != NULL)
			kcf_free_triedlist(list);
		return (error);
	}

	/*
	 * For SW providers, check the validity of the context template
	 * It is very rare that the generation number mis-matches, so
	 * is acceptable to fail here, and let the consumer recover by
	 * freeing this tmpl and create a new one for the key and new SW
	 * provider
	 */
	if ((pd->pd_prov_type == CRYPTO_SW_PROVIDER) &&
	    ((ctx_tmpl = (kcf_ctx_template_t *)tmpl) != NULL)) {
		if (ctx_tmpl->ct_generation != me->me_gen_swprov) {
			if (list != NULL)
				kcf_free_triedlist(list);
			KCF_PROV_REFRELE(pd);
			return (CRYPTO_OLD_CTX_TEMPLATE);
		} else {
			spi_ctx_tmpl = ctx_tmpl->ct_prov_tmpl;
		}
	}

	error = crypto_cipher_init_prov(pd, pd->pd_sid, mech, key,
	    spi_ctx_tmpl, ctxp, crq, func);
	if (error != CRYPTO_SUCCESS && error != CRYPTO_QUEUED &&
	    IS_RECOVERABLE(error)) {
		/* Add pd to the linked list of providers tried. */
		if (kcf_insert_triedlist(&list, pd, KCF_KMFLAG(crq)) != NULL)
			goto retry;
	}

	if (list != NULL)
		kcf_free_triedlist(list);

	KCF_PROV_REFRELE(pd);
	return (error);
}