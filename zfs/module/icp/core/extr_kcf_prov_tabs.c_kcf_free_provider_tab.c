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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_PROV_REFRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,int) ; 

void
kcf_free_provider_tab(uint_t count, kcf_provider_desc_t **array)
{
	kcf_provider_desc_t *prov_desc;
	int i;

	for (i = 0; i < count; i++) {
		if ((prov_desc = array[i]) != NULL) {
			KCF_PROV_REFRELE(prov_desc);
		}
	}
	kmem_free(array, count * sizeof (kcf_provider_desc_t *));
}