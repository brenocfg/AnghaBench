#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pd_state; scalar_t__ pd_prov_type; scalar_t__ ec_provider_type; int pd_mech_list_count; int pd_flags; TYPE_1__* pd_mechanisms; int /*<<< orphan*/  ec_mech_name; int /*<<< orphan*/  ec_change; } ;
typedef  TYPE_2__ kcf_provider_desc_t ;
typedef  TYPE_2__ crypto_notify_event_change_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  cm_mech_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CRYPTO_EVENT_MECHS_CHANGED ; 
 int /*<<< orphan*/  CRYPTO_EVENT_PROVIDER_REGISTERED ; 
 int /*<<< orphan*/  CRYPTO_EVENT_PROVIDER_UNREGISTERED ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int /*<<< orphan*/  CRYPTO_MAX_MECH_NAME ; 
 int /*<<< orphan*/  CRYPTO_MECH_ADDED ; 
 int /*<<< orphan*/  CRYPTO_MECH_REMOVED ; 
 int KCF_LPROV_MEMBER ; 
 scalar_t__ KCF_PROV_VERIFICATION_FAILED ; 
 int /*<<< orphan*/  kcf_walk_ntfylist (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kcf_do_notify(kcf_provider_desc_t *prov_desc, boolean_t is_added)
{
	int i;
	crypto_notify_event_change_t ec;

	ASSERT(prov_desc->pd_state > KCF_PROV_VERIFICATION_FAILED);

	/*
	 * Inform interested clients of the mechanisms becoming
	 * available/unavailable. We skip this for logical providers
	 * as they do not affect mechanisms.
	 */
	if (prov_desc->pd_prov_type != CRYPTO_LOGICAL_PROVIDER) {
		ec.ec_provider_type = prov_desc->pd_prov_type;
		ec.ec_change = is_added ? CRYPTO_MECH_ADDED :
		    CRYPTO_MECH_REMOVED;
		for (i = 0; i < prov_desc->pd_mech_list_count; i++) {
			(void) strlcpy(ec.ec_mech_name,
			    prov_desc->pd_mechanisms[i].cm_mech_name,
			    CRYPTO_MAX_MECH_NAME);
			kcf_walk_ntfylist(CRYPTO_EVENT_MECHS_CHANGED, &ec);
		}

	}

	/*
	 * Inform interested clients about the new or departing provider.
	 * In case of a logical provider, we need to notify the event only
	 * for the logical provider and not for the underlying
	 * providers which are known by the KCF_LPROV_MEMBER bit.
	 */
	if (prov_desc->pd_prov_type == CRYPTO_LOGICAL_PROVIDER ||
	    (prov_desc->pd_flags & KCF_LPROV_MEMBER) == 0) {
		kcf_walk_ntfylist(is_added ? CRYPTO_EVENT_PROVIDER_REGISTERED :
		    CRYPTO_EVENT_PROVIDER_UNREGISTERED, prov_desc);
	}
}