#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pt_pd; struct TYPE_4__* pt_next; } ;
typedef  TYPE_1__ kcf_prov_tried_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_PROV_REFRELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

void
kcf_free_triedlist(kcf_prov_tried_t *list)
{
	kcf_prov_tried_t *l;

	while ((l = list) != NULL) {
		list = list->pt_next;
		KCF_PROV_REFRELE(l->pt_pd);
		kmem_free(l, sizeof (kcf_prov_tried_t));
	}
}