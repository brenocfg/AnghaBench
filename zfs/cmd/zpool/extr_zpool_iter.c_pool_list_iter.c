#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zn_handle; } ;
typedef  TYPE_1__ zpool_node_t ;
struct TYPE_8__ {int /*<<< orphan*/  zl_avl; } ;
typedef  TYPE_2__ zpool_list_t ;
typedef  int (* zpool_iter_f ) (int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 scalar_t__ POOL_STATE_UNAVAIL ; 
 TYPE_1__* uu_avl_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_avl_next (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ ) ; 

int
pool_list_iter(zpool_list_t *zlp, int unavail, zpool_iter_f func,
    void *data)
{
	zpool_node_t *node, *next_node;
	int ret = 0;

	for (node = uu_avl_first(zlp->zl_avl); node != NULL; node = next_node) {
		next_node = uu_avl_next(zlp->zl_avl, node);
		if (zpool_get_state(node->zn_handle) != POOL_STATE_UNAVAIL ||
		    unavail)
			ret |= func(node->zn_handle, data);
	}

	return (ret);
}