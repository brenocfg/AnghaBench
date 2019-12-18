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
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prov_tab ; 
 int prov_tab_max ; 
 int /*<<< orphan*/  prov_tab_mutex ; 

void
kcf_prov_tab_init(void)
{
	mutex_init(&prov_tab_mutex, NULL, MUTEX_DEFAULT, NULL);

	prov_tab = kmem_zalloc(prov_tab_max * sizeof (kcf_provider_desc_t *),
	    KM_SLEEP);
}