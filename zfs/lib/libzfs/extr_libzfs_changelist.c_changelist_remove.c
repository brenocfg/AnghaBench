#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
struct TYPE_8__ {TYPE_3__* cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_9__ {int /*<<< orphan*/  cl_tree; } ;
typedef  TYPE_2__ prop_changelist_t ;
struct TYPE_10__ {int /*<<< orphan*/  zfs_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  uu_avl_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_3__*) ; 

void
changelist_remove(prop_changelist_t *clp, const char *name)
{
	prop_changenode_t *cn;
	uu_avl_walk_t *walk;

	if ((walk = uu_avl_walk_start(clp->cl_tree, UU_WALK_ROBUST)) == NULL)
		return;

	while ((cn = uu_avl_walk_next(walk)) != NULL) {
		if (strcmp(cn->cn_handle->zfs_name, name) == 0) {
			uu_avl_remove(clp->cl_tree, cn);
			zfs_close(cn->cn_handle);
			free(cn);
			uu_avl_walk_end(walk);
			return;
		}
	}

	uu_avl_walk_end(walk);
}