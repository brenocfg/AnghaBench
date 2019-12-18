#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* pl_next; TYPE_2__* pl_provider; } ;
typedef  TYPE_1__ kcf_provider_list_t ;
struct TYPE_9__ {scalar_t__ pd_prov_type; int /*<<< orphan*/  pd_lock; TYPE_1__* pd_provider_list; int /*<<< orphan*/  pd_flags; } ;
typedef  TYPE_2__ kcf_provider_desc_t ;

/* Variables and functions */
 scalar_t__ CRYPTO_HW_PROVIDER ; 
 int /*<<< orphan*/  KCF_LPROV_MEMBER ; 
 int /*<<< orphan*/  KCF_PROV_IREFRELE (TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_provider_from_array (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void
remove_provider(kcf_provider_desc_t *pp)
{
	kcf_provider_desc_t *p;
	kcf_provider_list_t *e, *next;

	mutex_enter(&pp->pd_lock);
	for (e = pp->pd_provider_list; e != NULL; e = next) {
		p = e->pl_provider;
		remove_provider_from_array(pp, p);
		if (p->pd_prov_type == CRYPTO_HW_PROVIDER &&
		    p->pd_provider_list == NULL)
			p->pd_flags &= ~KCF_LPROV_MEMBER;
		KCF_PROV_IREFRELE(p);
		next = e->pl_next;
		kmem_free(e, sizeof (*e));
	}
	pp->pd_provider_list = NULL;
	mutex_exit(&pp->pd_lock);
}