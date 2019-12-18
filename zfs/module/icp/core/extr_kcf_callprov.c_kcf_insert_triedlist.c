#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;
struct TYPE_5__ {struct TYPE_5__* pt_next; int /*<<< orphan*/ * pt_pd; } ;
typedef  TYPE_1__ kcf_prov_tried_t ;

/* Variables and functions */
 TYPE_1__* kmem_alloc (int,int) ; 

kcf_prov_tried_t *
kcf_insert_triedlist(kcf_prov_tried_t **list, kcf_provider_desc_t *pd,
    int kmflag)
{
	kcf_prov_tried_t *l;

	l = kmem_alloc(sizeof (kcf_prov_tried_t), kmflag);
	if (l == NULL)
		return (NULL);

	l->pt_pd = pd;
	l->pt_next = *list;
	*list = l;

	return (l);
}