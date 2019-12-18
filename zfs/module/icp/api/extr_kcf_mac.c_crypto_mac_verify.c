#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_25__ {scalar_t__ pd_prov_type; int pd_flags; scalar_t__ pd_hash_limit; int /*<<< orphan*/  pd_sid; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_tried_t ;
struct TYPE_26__ {scalar_t__ me_gen_swprov; } ;
typedef  TYPE_2__ kcf_mech_entry_t ;
struct TYPE_27__ {scalar_t__ ct_generation; int /*<<< orphan*/ * ct_prov_tmpl; } ;
typedef  TYPE_3__ kcf_ctx_template_t ;
typedef  int /*<<< orphan*/ * crypto_spi_ctx_template_t ;
struct TYPE_28__ {int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_4__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
struct TYPE_29__ {scalar_t__ cd_length; } ;
typedef  TYPE_5__ crypto_data_t ;
typedef  scalar_t__ crypto_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 scalar_t__ CHECK_FASTPATH (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_RESTRICT (int /*<<< orphan*/ *) ; 
 int CRYPTO_BUFFER_TOO_BIG ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC_ATOMIC ; 
 int CRYPTO_HASH_NO_UPDATE ; 
 scalar_t__ CRYPTO_HW_PROVIDER ; 
 int CRYPTO_OLD_CTX_TEMPLATE ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ CRYPTO_SW_PROVIDER ; 
 scalar_t__ IS_RECOVERABLE (int) ; 
 int /*<<< orphan*/  KCF_ISDUALREQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_KMFLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_OP_MAC_VERIFY_ATOMIC ; 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_1__*,int) ; 
 int KCF_PROV_MAC_VERIFY_ATOMIC (TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_SET_PROVIDER_MECHNUM (int /*<<< orphan*/ ,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  KCF_SWFP_RHNDL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_WRAP_MAC_OPS_PARAMS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcf_free_triedlist (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcf_get_mech_provider (int /*<<< orphan*/ ,TYPE_2__**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * kcf_insert_triedlist (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int kcf_submit_request (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_mac_verify(crypto_mechanism_t *mech, crypto_data_t *data,
    crypto_key_t *key, crypto_ctx_template_t tmpl, crypto_data_t *mac,
    crypto_call_req_t *crq)
{
	int error;
	kcf_mech_entry_t *me;
	kcf_req_params_t params;
	kcf_provider_desc_t *pd;
	kcf_ctx_template_t *ctx_tmpl;
	crypto_spi_ctx_template_t spi_ctx_tmpl = NULL;
	kcf_prov_tried_t *list = NULL;

retry:
	/* The pd is returned held */
	if ((pd = kcf_get_mech_provider(mech->cm_type, &me, &error,
	    list, CRYPTO_FG_MAC_ATOMIC, CHECK_RESTRICT(crq),
	    data->cd_length)) == NULL) {
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

	/* The fast path for SW providers. */
	if (CHECK_FASTPATH(crq, pd)) {
		crypto_mechanism_t lmech;

		lmech = *mech;
		KCF_SET_PROVIDER_MECHNUM(mech->cm_type, pd, &lmech);

		error = KCF_PROV_MAC_VERIFY_ATOMIC(pd, pd->pd_sid, &lmech, key,
		    data, mac, spi_ctx_tmpl, KCF_SWFP_RHNDL(crq));
		KCF_PROV_INCRSTATS(pd, error);
	} else {
		if (pd->pd_prov_type == CRYPTO_HW_PROVIDER &&
		    (pd->pd_flags & CRYPTO_HASH_NO_UPDATE) &&
		    (data->cd_length > pd->pd_hash_limit)) {
			/* see comments in crypto_mac() */
			error = CRYPTO_BUFFER_TOO_BIG;
		} else {
			KCF_WRAP_MAC_OPS_PARAMS(&params,
			    KCF_OP_MAC_VERIFY_ATOMIC, pd->pd_sid, mech,
			    key, data, mac, spi_ctx_tmpl);

			error = kcf_submit_request(pd, NULL, crq, &params,
			    KCF_ISDUALREQ(crq));
		}
	}

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