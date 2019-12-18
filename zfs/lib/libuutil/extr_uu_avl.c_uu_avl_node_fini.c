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
struct TYPE_4__ {int /*<<< orphan*/  uap_name; scalar_t__ uap_debug; } ;
typedef  TYPE_1__ uu_avl_pool_t ;
typedef  int /*<<< orphan*/  uu_avl_node_t ;

/* Variables and functions */
 uintptr_t DEAD_MARKER ; 
 uintptr_t POOL_TO_MARKER (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*,void*,int /*<<< orphan*/ ) ; 

void
uu_avl_node_fini(void *base, uu_avl_node_t *np, uu_avl_pool_t *pp)
{
	uintptr_t *na = (uintptr_t *)np;

	if (pp->uap_debug) {
		if (na[0] == DEAD_MARKER && na[1] == DEAD_MARKER) {
			uu_panic("uu_avl_node_fini(%p, %p, %p (\"%s\")): "
			    "node already finied\n",
			    base, (void *)np, (void *)pp, pp->uap_name);
		}
		if (na[0] != POOL_TO_MARKER(pp) || na[1] != 0) {
			uu_panic("uu_avl_node_fini(%p, %p, %p (\"%s\")): "
			    "node corrupt, in tree, or in different pool\n",
			    base, (void *)np, (void *)pp, pp->uap_name);
		}
	}

	na[0] = DEAD_MARKER;
	na[1] = DEAD_MARKER;
	na[2] = DEAD_MARKER;
}