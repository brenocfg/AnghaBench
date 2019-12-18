#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_6__ {size_t pd_mech_list_count; int /*<<< orphan*/  pd_prov_id; TYPE_1__* pd_mechanisms; } ;
typedef  TYPE_2__ kcf_provider_desc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  cm_mech_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kcf_prov_tab_rem_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcf_remove_mech_provider (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
undo_register_provider(kcf_provider_desc_t *desc, boolean_t remove_prov)
{
	uint_t mech_idx;

	/* remove the provider from the mechanisms tables */
	for (mech_idx = 0; mech_idx < desc->pd_mech_list_count;
	    mech_idx++) {
		kcf_remove_mech_provider(
		    desc->pd_mechanisms[mech_idx].cm_mech_name, desc);
	}

	/* remove provider from providers table */
	if (remove_prov)
		(void) kcf_prov_tab_rem_provider(desc->pd_prov_id);
}