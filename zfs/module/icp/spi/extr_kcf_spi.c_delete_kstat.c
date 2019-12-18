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
struct TYPE_6__ {TYPE_2__* pd_kstat; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_7__ {TYPE_1__* ks_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KCF_PROV_IREFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (TYPE_1__*) ; 
 int /*<<< orphan*/  kstat_delete (TYPE_2__*) ; 

__attribute__((used)) static void
delete_kstat(kcf_provider_desc_t *desc)
{
	/* destroy the kstat created for this provider */
	if (desc->pd_kstat != NULL) {
		kcf_provider_desc_t *kspd = desc->pd_kstat->ks_private;

		/* release reference held by desc->pd_kstat->ks_private */
		ASSERT(desc == kspd);
		kstat_delete(kspd->pd_kstat);
		desc->pd_kstat = NULL;
		KCF_PROV_REFRELE(kspd);
		KCF_PROV_IREFRELE(kspd);
	}
}