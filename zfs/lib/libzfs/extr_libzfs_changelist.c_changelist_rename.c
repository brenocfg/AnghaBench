#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
struct TYPE_6__ {TYPE_4__* cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_7__ {int /*<<< orphan*/  cl_tree; } ;
typedef  TYPE_2__ prop_changelist_t ;
typedef  int /*<<< orphan*/  newname ;
struct TYPE_8__ {char* zfs_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  isa_child_of (char*,char const*) ; 
 int /*<<< orphan*/  remove_mountpoint (TYPE_4__*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
changelist_rename(prop_changelist_t *clp, const char *src, const char *dst)
{
	prop_changenode_t *cn;
	uu_avl_walk_t *walk;
	char newname[ZFS_MAX_DATASET_NAME_LEN];

	if ((walk = uu_avl_walk_start(clp->cl_tree, UU_WALK_ROBUST)) == NULL)
		return;

	while ((cn = uu_avl_walk_next(walk)) != NULL) {
		/*
		 * Do not rename a clone that's not in the source hierarchy.
		 */
		if (!isa_child_of(cn->cn_handle->zfs_name, src))
			continue;

		/*
		 * Destroy the previous mountpoint if needed.
		 */
		remove_mountpoint(cn->cn_handle);

		(void) strlcpy(newname, dst, sizeof (newname));
		(void) strlcat(newname, cn->cn_handle->zfs_name + strlen(src),
		    sizeof (newname));

		(void) strlcpy(cn->cn_handle->zfs_name, newname,
		    sizeof (cn->cn_handle->zfs_name));
	}

	uu_avl_walk_end(walk);
}