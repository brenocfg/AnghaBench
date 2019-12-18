#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_12__ {int pd_mech_list_count; scalar_t__ pd_prov_type; int pd_flags; scalar_t__ pd_hash_limit; TYPE_4__* pd_mechanisms; } ;
typedef  TYPE_2__ kcf_provider_desc_t ;
typedef  int /*<<< orphan*/  kcf_prov_mech_desc_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pi_mechanisms; TYPE_1__* pi_ops_vector; } ;
typedef  TYPE_3__ crypto_provider_info_t ;
struct TYPE_14__ {int cm_func_group_mask; int cm_mech_flags; scalar_t__ cm_max_input_length; int /*<<< orphan*/  cm_mech_name; } ;
typedef  TYPE_4__ crypto_mech_info_t ;
struct TYPE_11__ {int /*<<< orphan*/ * co_random_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_FG_DIGEST ; 
 int CRYPTO_FG_RANDOM ; 
 int CRYPTO_HASH_NO_UPDATE ; 
 int CRYPTO_HOST_MEMORY ; 
 int CRYPTO_KEYSIZE_UNIT_IN_BITS ; 
 int CRYPTO_KEYSIZE_UNIT_IN_BYTES ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int /*<<< orphan*/  CRYPTO_MAX_MECH_NAME ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ CRYPTO_SW_PROVIDER ; 
 int KCF_MECH_TAB_FULL ; 
 int KCF_SUCCESS ; 
 int /*<<< orphan*/  SUN_RANDOM ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int kcf_add_mech_provider (size_t,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kcf_remove_mech_provider (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_prov_mechs(crypto_provider_info_t *info, kcf_provider_desc_t *desc)
{
	uint_t mech_idx;
	uint_t cleanup_idx;
	int err = CRYPTO_SUCCESS;
	kcf_prov_mech_desc_t *pmd;
	int desc_use_count = 0;
	int mcount = desc->pd_mech_list_count;

	if (desc->pd_prov_type == CRYPTO_LOGICAL_PROVIDER) {
		if (info != NULL) {
			ASSERT(info->pi_mechanisms != NULL);
			bcopy(info->pi_mechanisms, desc->pd_mechanisms,
			    sizeof (crypto_mech_info_t) * mcount);
		}
		return (CRYPTO_SUCCESS);
	}

	/*
	 * Copy the mechanism list from the provider info to the provider
	 * descriptor. desc->pd_mechanisms has an extra crypto_mech_info_t
	 * element if the provider has random_ops since we keep an internal
	 * mechanism, SUN_RANDOM, in this case.
	 */
	if (info != NULL) {
		if (info->pi_ops_vector->co_random_ops != NULL) {
			crypto_mech_info_t *rand_mi;

			/*
			 * Need the following check as it is possible to have
			 * a provider that implements just random_ops and has
			 * pi_mechanisms == NULL.
			 */
			if (info->pi_mechanisms != NULL) {
				bcopy(info->pi_mechanisms, desc->pd_mechanisms,
				    sizeof (crypto_mech_info_t) * (mcount - 1));
			}
			rand_mi = &desc->pd_mechanisms[mcount - 1];

			bzero(rand_mi, sizeof (crypto_mech_info_t));
			(void) strncpy(rand_mi->cm_mech_name, SUN_RANDOM,
			    CRYPTO_MAX_MECH_NAME);
			rand_mi->cm_func_group_mask = CRYPTO_FG_RANDOM;
		} else {
			ASSERT(info->pi_mechanisms != NULL);
			bcopy(info->pi_mechanisms, desc->pd_mechanisms,
			    sizeof (crypto_mech_info_t) * mcount);
		}
	}

	/*
	 * For each mechanism support by the provider, add the provider
	 * to the corresponding KCF mechanism mech_entry chain.
	 */
	for (mech_idx = 0; mech_idx < desc->pd_mech_list_count; mech_idx++) {
		crypto_mech_info_t *mi = &desc->pd_mechanisms[mech_idx];

		if ((mi->cm_mech_flags & CRYPTO_KEYSIZE_UNIT_IN_BITS) &&
		    (mi->cm_mech_flags & CRYPTO_KEYSIZE_UNIT_IN_BYTES)) {
			err = CRYPTO_ARGUMENTS_BAD;
			break;
		}

		if (desc->pd_flags & CRYPTO_HASH_NO_UPDATE &&
		    mi->cm_func_group_mask & CRYPTO_FG_DIGEST) {
			/*
			 * We ask the provider to specify the limit
			 * per hash mechanism. But, in practice, a
			 * hardware limitation means all hash mechanisms
			 * will have the same maximum size allowed for
			 * input data. So, we make it a per provider
			 * limit to keep it simple.
			 */
			if (mi->cm_max_input_length == 0) {
				err = CRYPTO_ARGUMENTS_BAD;
				break;
			} else {
				desc->pd_hash_limit = mi->cm_max_input_length;
			}
		}

		if ((err = kcf_add_mech_provider(mech_idx, desc, &pmd)) !=
		    KCF_SUCCESS)
			break;

		if (pmd == NULL)
			continue;

		/* The provider will be used for this mechanism */
		desc_use_count++;
	}

	/*
	 * Don't allow multiple software providers with disabled mechanisms
	 * to register. Subsequent enabling of mechanisms will result in
	 * an unsupported configuration, i.e. multiple software providers
	 * per mechanism.
	 */
	if (desc_use_count == 0 && desc->pd_prov_type == CRYPTO_SW_PROVIDER)
		return (CRYPTO_ARGUMENTS_BAD);

	if (err == KCF_SUCCESS)
		return (CRYPTO_SUCCESS);

	/*
	 * An error occurred while adding the mechanism, cleanup
	 * and bail.
	 */
	for (cleanup_idx = 0; cleanup_idx < mech_idx; cleanup_idx++) {
		kcf_remove_mech_provider(
		    desc->pd_mechanisms[cleanup_idx].cm_mech_name, desc);
	}

	if (err == KCF_MECH_TAB_FULL)
		return (CRYPTO_HOST_MEMORY);

	return (CRYPTO_ARGUMENTS_BAD);
}