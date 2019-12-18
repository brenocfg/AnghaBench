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
struct TYPE_5__ {scalar_t__ ul_debug; } ;
typedef  TYPE_1__ uu_list_t ;

/* Variables and functions */
 void* uu_list_first (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_list_remove (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*) ; 

void *
uu_list_teardown(uu_list_t *lp, void **cookie)
{
	void *ep;

	/*
	 * XXX: disable list modification until list is empty
	 */
	if (lp->ul_debug && *cookie != NULL)
		uu_panic("uu_list_teardown(%p, %p): unexpected cookie\n",
		    (void *)lp, (void *)cookie);

	ep = uu_list_first(lp);
	if (ep)
		uu_list_remove(lp, ep);
	return (ep);
}