#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ulp_name; scalar_t__ ulp_debug; } ;
typedef  TYPE_1__ uu_list_pool_t ;
typedef  int /*<<< orphan*/  uu_list_node_t ;
struct TYPE_6__ {int /*<<< orphan*/ * uln_prev; int /*<<< orphan*/ * uln_next; } ;
typedef  TYPE_2__ uu_list_node_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/ * POOL_TO_MARKER (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*,void*,int /*<<< orphan*/ ) ; 

void
uu_list_node_fini(void *base, uu_list_node_t *np_arg, uu_list_pool_t *pp)
{
	uu_list_node_impl_t *np = (uu_list_node_impl_t *)np_arg;

	if (pp->ulp_debug) {
		if (np->uln_next == NULL &&
		    np->uln_prev == NULL) {
			uu_panic("uu_list_node_fini(%p, %p, %p (\"%s\")): "
			    "node already finied\n",
			    base, (void *)np_arg, (void *)pp, pp->ulp_name);
		}
		if (np->uln_next != POOL_TO_MARKER(pp) ||
		    np->uln_prev != NULL) {
			uu_panic("uu_list_node_fini(%p, %p, %p (\"%s\")): "
			    "node corrupt or on list\n",
			    base, (void *)np_arg, (void *)pp, pp->ulp_name);
		}
	}
	np->uln_next = NULL;
	np->uln_prev = NULL;
}