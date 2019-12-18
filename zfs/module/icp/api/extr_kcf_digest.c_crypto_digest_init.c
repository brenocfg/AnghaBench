#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pd_prov_type; int pd_flags; int /*<<< orphan*/  pd_sid; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_tried_t ;
struct TYPE_10__ {int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RESTRICT (int /*<<< orphan*/ *) ; 
 int CRYPTO_BUFFER_TOO_BIG ; 
 int /*<<< orphan*/  CRYPTO_FG_DIGEST ; 
 int CRYPTO_HASH_NO_UPDATE ; 
 scalar_t__ CRYPTO_HW_PROVIDER ; 
 int CRYPTO_QUEUED ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ IS_RECOVERABLE (int) ; 
 int /*<<< orphan*/  KCF_KMFLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int crypto_digest_init_prov (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcf_free_triedlist (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcf_get_mech_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcf_insert_triedlist (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
crypto_digest_init(crypto_mechanism_t *mech, crypto_context_t *ctxp,
    crypto_call_req_t  *crq)
{
	int error;
	kcf_provider_desc_t *pd;
	kcf_prov_tried_t *list = NULL;

retry:
	/* The pd is returned held */
	if ((pd = kcf_get_mech_provider(mech->cm_type, NULL, &error,
	    list, CRYPTO_FG_DIGEST, CHECK_RESTRICT(crq), 0)) == NULL) {
		if (list != NULL)
			kcf_free_triedlist(list);
		return (error);
	}

	if (pd->pd_prov_type == CRYPTO_HW_PROVIDER &&
	    (pd->pd_flags & CRYPTO_HASH_NO_UPDATE)) {
		/*
		 * The hardware provider has limited digest support.
		 * So, we fallback early here to using a software provider.
		 *
		 * XXX - need to enhance to do the fallback later in
		 * crypto_digest_update() if the size of accumulated input data
		 * exceeds the maximum size digestable by hardware provider.
		 */
		error = CRYPTO_BUFFER_TOO_BIG;
	} else {
		error = crypto_digest_init_prov(pd, pd->pd_sid,
		    mech, ctxp, crq);
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