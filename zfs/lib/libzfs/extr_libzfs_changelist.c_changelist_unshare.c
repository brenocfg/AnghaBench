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
typedef  int /*<<< orphan*/  zfs_share_proto_t ;
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
struct TYPE_5__ {int /*<<< orphan*/  cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_6__ {scalar_t__ cl_prop; int /*<<< orphan*/  cl_tree; } ;
typedef  TYPE_2__ prop_changelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 scalar_t__ ZFS_PROP_SHARENFS ; 
 scalar_t__ ZFS_PROP_SHARESMB ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_unshare_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
changelist_unshare(prop_changelist_t *clp, zfs_share_proto_t *proto)
{
	prop_changenode_t *cn;
	uu_avl_walk_t *walk;
	int ret = 0;

	if (clp->cl_prop != ZFS_PROP_SHARENFS &&
	    clp->cl_prop != ZFS_PROP_SHARESMB)
		return (0);

	if ((walk = uu_avl_walk_start(clp->cl_tree, UU_WALK_ROBUST)) == NULL)
		return (-1);

	while ((cn = uu_avl_walk_next(walk)) != NULL) {
		if (zfs_unshare_proto(cn->cn_handle, NULL, proto) != 0)
			ret = -1;
	}

	uu_avl_walk_end(walk);

	return (ret);
}