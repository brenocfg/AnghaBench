#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int pd_flags; } ;
typedef  TYPE_3__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_tried_t ;
struct TYPE_19__ {scalar_t__ cm_mech_number; } ;
struct TYPE_21__ {TYPE_2__ pm_mech_info; TYPE_7__* pm_mi_list; TYPE_3__* pm_prov_desc; struct TYPE_21__* pm_next; } ;
typedef  TYPE_4__ kcf_prov_mech_desc_t ;
struct TYPE_22__ {size_t me_threshold; scalar_t__ me_num_hwprov; int /*<<< orphan*/  me_mutex; TYPE_4__* me_sw_prov; TYPE_4__* me_hw_prov_chain; } ;
typedef  TYPE_5__ kcf_mech_entry_t ;
struct TYPE_23__ {scalar_t__ cm_type; } ;
typedef  TYPE_6__ crypto_mechanism_t ;
typedef  scalar_t__ crypto_mech_type_t ;
struct TYPE_18__ {int cm_func_group_mask; scalar_t__ cm_mech_number; } ;
struct TYPE_24__ {scalar_t__ ml_kcf_mechid; TYPE_1__ ml_mech_info; struct TYPE_24__* ml_next; } ;
typedef  TYPE_7__ crypto_mech_info_list_t ;
typedef  int crypto_func_group_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_MECHANISM_INVALID ; 
 scalar_t__ CRYPTO_MECH_INVALID ; 
 int CRYPTO_MECH_NOT_SUPPORTED ; 
 int INT_MAX ; 
 int /*<<< orphan*/  IS_FG_SUPPORTED (TYPE_4__*,int) ; 
 scalar_t__ IS_PROVIDER_TRIED (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_IS_PROV_USABLE (TYPE_3__*) ; 
 int KCF_PROV_LOAD (TYPE_3__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (TYPE_3__*) ; 
 int KCF_PROV_RESTRICTED ; 
 scalar_t__ KCF_SUCCESS ; 
 scalar_t__ kcf_get_mech_entry (scalar_t__,TYPE_5__**) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

kcf_provider_desc_t *
kcf_get_dual_provider(crypto_mechanism_t *mech1, crypto_mechanism_t *mech2,
    kcf_mech_entry_t **mepp, crypto_mech_type_t *prov_mt1,
    crypto_mech_type_t *prov_mt2, int *error, kcf_prov_tried_t *triedl,
    crypto_func_group_t fg1, crypto_func_group_t fg2, boolean_t call_restrict,
    size_t data_size)
{
	kcf_provider_desc_t *pd = NULL, *pdm1 = NULL, *pdm1m2 = NULL;
	kcf_prov_mech_desc_t *prov_chain, *mdesc;
	int len, gqlen = INT_MAX, dgqlen = INT_MAX;
	crypto_mech_info_list_t *mil;
	crypto_mech_type_t m2id =  mech2->cm_type;
	kcf_mech_entry_t *me;

	/* when mech is a valid mechanism, me will be its mech_entry */
	if (kcf_get_mech_entry(mech1->cm_type, &me) != KCF_SUCCESS) {
		*error = CRYPTO_MECHANISM_INVALID;
		return (NULL);
	}

	*prov_mt2 = CRYPTO_MECH_INVALID;

	if (mepp != NULL)
		*mepp = me;
	mutex_enter(&me->me_mutex);

	prov_chain = me->me_hw_prov_chain;
	/*
	 * We check the threshold for using a hardware provider for
	 * this amount of data. If there is no software provider available
	 * for the first mechanism, then the threshold is ignored.
	 */
	if ((prov_chain != NULL) &&
	    ((data_size == 0) || (me->me_threshold == 0) ||
	    (data_size >= me->me_threshold) ||
	    ((mdesc = me->me_sw_prov) == NULL) ||
	    (!IS_FG_SUPPORTED(mdesc, fg1)) ||
	    (!KCF_IS_PROV_USABLE(mdesc->pm_prov_desc)))) {
		/* there is at least one provider */
		ASSERT(me->me_num_hwprov > 0);

		/*
		 * Find the least loaded provider capable of the combo
		 * me1 + me2, and save a pointer to the least loaded
		 * provider capable of me1 only.
		 */
		while (prov_chain != NULL) {
			pd = prov_chain->pm_prov_desc;
			len = KCF_PROV_LOAD(pd);

			if (!IS_FG_SUPPORTED(prov_chain, fg1) ||
			    !KCF_IS_PROV_USABLE(pd) ||
			    IS_PROVIDER_TRIED(pd, triedl) ||
			    (call_restrict &&
			    (pd->pd_flags & KCF_PROV_RESTRICTED))) {
				prov_chain = prov_chain->pm_next;
				continue;
			}

			/* Save the best provider capable of m1 */
			if (len < gqlen) {
				*prov_mt1 =
				    prov_chain->pm_mech_info.cm_mech_number;
				gqlen = len;
				pdm1 = pd;
			}

			/* See if pd can do me2 too */
			for (mil = prov_chain->pm_mi_list;
			    mil != NULL; mil = mil->ml_next) {
				if ((mil->ml_mech_info.cm_func_group_mask &
				    fg2) == 0)
					continue;

				if ((mil->ml_kcf_mechid == m2id) &&
				    (len < dgqlen)) {
					/* Bingo! */
					dgqlen = len;
					pdm1m2 = pd;
					*prov_mt2 =
					    mil->ml_mech_info.cm_mech_number;
					*prov_mt1 = prov_chain->
					    pm_mech_info.cm_mech_number;
					break;
				}
			}

			prov_chain = prov_chain->pm_next;
		}

		pd =  (pdm1m2 != NULL) ? pdm1m2 : pdm1;
	}

	/* no HW provider for this mech, is there a SW provider? */
	if (pd == NULL && (mdesc = me->me_sw_prov) != NULL) {
		pd = mdesc->pm_prov_desc;
		if (!IS_FG_SUPPORTED(mdesc, fg1) ||
		    !KCF_IS_PROV_USABLE(pd) ||
		    IS_PROVIDER_TRIED(pd, triedl) ||
		    (call_restrict && (pd->pd_flags & KCF_PROV_RESTRICTED)))
			pd = NULL;
		else {
			/* See if pd can do me2 too */
			for (mil = me->me_sw_prov->pm_mi_list;
			    mil != NULL; mil = mil->ml_next) {
				if ((mil->ml_mech_info.cm_func_group_mask &
				    fg2) == 0)
					continue;

				if (mil->ml_kcf_mechid == m2id) {
					/* Bingo! */
					*prov_mt2 =
					    mil->ml_mech_info.cm_mech_number;
					break;
				}
			}
			*prov_mt1 = me->me_sw_prov->pm_mech_info.cm_mech_number;
		}
	}

	if (pd == NULL)
		*error = CRYPTO_MECH_NOT_SUPPORTED;
	else
		KCF_PROV_REFHOLD(pd);

	mutex_exit(&me->me_mutex);
	return (pd);
}