#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_req_params_t ;
struct TYPE_22__ {scalar_t__ pd_prov_type; int pd_flags; scalar_t__ pd_hash_limit; int /*<<< orphan*/  pd_sid; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_tried_t ;
struct TYPE_23__ {int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
struct TYPE_24__ {scalar_t__ cd_length; } ;
typedef  TYPE_3__ crypto_data_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CHECK_FASTPATH (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_RESTRICT (int /*<<< orphan*/ *) ; 
 int CRYPTO_BUFFER_TOO_BIG ; 
 int /*<<< orphan*/  CRYPTO_FG_DIGEST_ATOMIC ; 
 int CRYPTO_HASH_NO_UPDATE ; 
 scalar_t__ CRYPTO_HW_PROVIDER ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ IS_RECOVERABLE (int) ; 
 int /*<<< orphan*/  KCF_KMFLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_OP_ATOMIC ; 
 int KCF_PROV_DIGEST_ATOMIC (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCF_PROV_INCRSTATS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_SET_PROVIDER_MECHNUM (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  KCF_SWFP_RHNDL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_WRAP_DIGEST_OPS_PARAMS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  kcf_free_triedlist (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcf_get_mech_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * kcf_insert_triedlist (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int kcf_submit_request (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_digest(crypto_mechanism_t *mech, crypto_data_t *data,
    crypto_data_t *digest, crypto_call_req_t *crq)
{
	int error;
	kcf_provider_desc_t *pd;
	kcf_req_params_t params;
	kcf_prov_tried_t *list = NULL;

retry:
	/* The pd is returned held */
	if ((pd = kcf_get_mech_provider(mech->cm_type, NULL, &error, list,
	    CRYPTO_FG_DIGEST_ATOMIC, CHECK_RESTRICT(crq),
	    data->cd_length)) == NULL) {
		if (list != NULL)
			kcf_free_triedlist(list);
		return (error);
	}

	/* The fast path for SW providers. */
	if (CHECK_FASTPATH(crq, pd)) {
		crypto_mechanism_t lmech;

		lmech = *mech;
		KCF_SET_PROVIDER_MECHNUM(mech->cm_type, pd, &lmech);
		error = KCF_PROV_DIGEST_ATOMIC(pd, pd->pd_sid, &lmech, data,
		    digest, KCF_SWFP_RHNDL(crq));
		KCF_PROV_INCRSTATS(pd, error);
	} else {
		if (pd->pd_prov_type == CRYPTO_HW_PROVIDER &&
		    (pd->pd_flags & CRYPTO_HASH_NO_UPDATE) &&
		    (data->cd_length > pd->pd_hash_limit)) {
			error = CRYPTO_BUFFER_TOO_BIG;
		} else {
			KCF_WRAP_DIGEST_OPS_PARAMS(&params, KCF_OP_ATOMIC,
			    pd->pd_sid, mech, NULL, data, digest);

			/* no crypto context to carry between multiple parts. */
			error = kcf_submit_request(pd, NULL, crq, &params,
			    B_FALSE);
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