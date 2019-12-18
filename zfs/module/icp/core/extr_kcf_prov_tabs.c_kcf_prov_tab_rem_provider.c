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
typedef  size_t crypto_provider_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_INVALID_PROVIDER_ID ; 
 int CRYPTO_SUCCESS ; 
 size_t KCF_MAX_PROVIDERS ; 
 int /*<<< orphan*/  KCF_PROV_IREFRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** prov_tab ; 
 int /*<<< orphan*/  prov_tab_mutex ; 
 scalar_t__ prov_tab_num ; 

int
kcf_prov_tab_rem_provider(crypto_provider_id_t prov_id)
{
	kcf_provider_desc_t *prov_desc;

	ASSERT(prov_tab != NULL);
	ASSERT(prov_tab_num >= 0);

	/*
	 * Validate provider id, since it can be specified by a 3rd-party
	 * provider.
	 */

	mutex_enter(&prov_tab_mutex);
	if (prov_id >= KCF_MAX_PROVIDERS ||
	    ((prov_desc = prov_tab[prov_id]) == NULL)) {
		mutex_exit(&prov_tab_mutex);
		return (CRYPTO_INVALID_PROVIDER_ID);
	}
	mutex_exit(&prov_tab_mutex);

	/*
	 * The provider id must remain valid until the associated provider
	 * descriptor is freed. For this reason, we simply release our
	 * reference to the descriptor here. When the reference count
	 * reaches zero, kcf_free_provider_desc() will be invoked and
	 * the associated entry in the providers table will be released
	 * at that time.
	 */

	KCF_PROV_REFRELE(prov_desc);
	KCF_PROV_IREFRELE(prov_desc);

	return (CRYPTO_SUCCESS);
}