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
struct TYPE_4__ {int /*<<< orphan*/ * an_tried_plist; int /*<<< orphan*/ * an_context; int /*<<< orphan*/  an_provider; } ;
typedef  TYPE_1__ kcf_areq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_CONTEXT_REFRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCF_PROV_REFRELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcf_areq_cache ; 
 int /*<<< orphan*/  kcf_free_triedlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
kcf_free_req(kcf_areq_node_t *areq)
{
	KCF_PROV_REFRELE(areq->an_provider);
	if (areq->an_context != NULL)
		KCF_CONTEXT_REFRELE(areq->an_context);

	if (areq->an_tried_plist != NULL)
		kcf_free_triedlist(areq->an_tried_plist);
	kmem_cache_free(kcf_areq_cache, areq);
}