#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_6__ {size_t pd_prov_id; scalar_t__ pd_kcf_prov_handle; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  scalar_t__ crypto_kcf_provider_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CE_WARN ; 
 int CRYPTO_HOST_MEMORY ; 
 int CRYPTO_SUCCESS ; 
 size_t KCF_MAX_PROVIDERS ; 
 int /*<<< orphan*/  KCF_PROV_IREFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__** prov_tab ; 
 int /*<<< orphan*/  prov_tab_mutex ; 
 int /*<<< orphan*/  prov_tab_num ; 

int
kcf_prov_tab_add_provider(kcf_provider_desc_t *prov_desc)
{
	uint_t i;

	ASSERT(prov_tab != NULL);

	mutex_enter(&prov_tab_mutex);

	/* find free slot in providers table */
	for (i = 1; i < KCF_MAX_PROVIDERS && prov_tab[i] != NULL; i++)
		;
	if (i == KCF_MAX_PROVIDERS) {
		/* ran out of providers entries */
		mutex_exit(&prov_tab_mutex);
		cmn_err(CE_WARN, "out of providers entries");
		return (CRYPTO_HOST_MEMORY);
	}

	/* initialize entry */
	prov_tab[i] = prov_desc;
	KCF_PROV_REFHOLD(prov_desc);
	KCF_PROV_IREFHOLD(prov_desc);
	prov_tab_num++;

	mutex_exit(&prov_tab_mutex);

	/* update provider descriptor */
	prov_desc->pd_prov_id = i;

	/*
	 * The KCF-private provider handle is defined as the internal
	 * provider id.
	 */
	prov_desc->pd_kcf_prov_handle =
	    (crypto_kcf_provider_handle_t)prov_desc->pd_prov_id;

	return (CRYPTO_SUCCESS);
}