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
 int /*<<< orphan*/  KCF_PROV_REFHOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** prov_tab ; 
 int /*<<< orphan*/  prov_tab_mutex ; 

kcf_provider_desc_t *
kcf_prov_tab_lookup(crypto_provider_id_t prov_id)
{
	kcf_provider_desc_t *prov_desc;

	mutex_enter(&prov_tab_mutex);

	prov_desc = prov_tab[prov_id];

	if (prov_desc == NULL) {
		mutex_exit(&prov_tab_mutex);
		return (NULL);
	}

	KCF_PROV_REFHOLD(prov_desc);

	mutex_exit(&prov_tab_mutex);

	return (prov_desc);
}