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
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pm_prov_desc; struct TYPE_5__* pm_next; } ;
typedef  TYPE_1__ kcf_prov_mech_desc_t ;
struct TYPE_6__ {scalar_t__ me_num_hwprov; TYPE_1__* me_hw_prov_chain; } ;
typedef  TYPE_2__ kcf_mech_entry_t ;
typedef  int /*<<< orphan*/  crypto_func_group_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ IS_FG_SUPPORTED (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
is_valid_provider_for_mech(kcf_provider_desc_t *pd, kcf_mech_entry_t *me,
    crypto_func_group_t fg)
{
	kcf_prov_mech_desc_t *prov_chain;

	prov_chain = me->me_hw_prov_chain;
	if (prov_chain != NULL) {
		ASSERT(me->me_num_hwprov > 0);
		for (; prov_chain != NULL; prov_chain = prov_chain->pm_next) {
			if (prov_chain->pm_prov_desc == pd &&
			    IS_FG_SUPPORTED(prov_chain, fg)) {
				return (B_TRUE);
			}
		}
	}
	return (B_FALSE);
}