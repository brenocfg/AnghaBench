#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
struct TYPE_7__ {scalar_t__ cl_pool; scalar_t__ cl_tree; int /*<<< orphan*/  cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
typedef  TYPE_1__ prop_changelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_destroy (scalar_t__) ; 
 int /*<<< orphan*/  uu_avl_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  uu_avl_remove (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ ) ; 

void
changelist_free(prop_changelist_t *clp)
{
	prop_changenode_t *cn;

	if (clp->cl_tree) {
		uu_avl_walk_t *walk;

		if ((walk = uu_avl_walk_start(clp->cl_tree,
		    UU_WALK_ROBUST)) == NULL)
			return;

		while ((cn = uu_avl_walk_next(walk)) != NULL) {
			uu_avl_remove(clp->cl_tree, cn);
			zfs_close(cn->cn_handle);
			free(cn);
		}

		uu_avl_walk_end(walk);
		uu_avl_destroy(clp->cl_tree);
	}
	if (clp->cl_pool)
		uu_avl_pool_destroy(clp->cl_pool);

	free(clp);
}