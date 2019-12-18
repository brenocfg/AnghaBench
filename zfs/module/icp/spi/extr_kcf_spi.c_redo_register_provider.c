#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_PROV_IREFHOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_prov_mechs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
redo_register_provider(kcf_provider_desc_t *pd)
{
	/* process the mechanisms supported by the provider */
	(void) init_prov_mechs(NULL, pd);

	/*
	 * Hold provider in providers table. We should not call
	 * kcf_prov_tab_add_provider() here as the provider descriptor
	 * is still valid which means it has an entry in the provider
	 * table.
	 */
	KCF_PROV_REFHOLD(pd);
	KCF_PROV_IREFHOLD(pd);
}