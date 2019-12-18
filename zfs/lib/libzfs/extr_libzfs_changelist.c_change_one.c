#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zprop_source_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  where ;
typedef  int /*<<< orphan*/  uu_avl_index_t ;
typedef  int /*<<< orphan*/  property ;
struct TYPE_8__ {int cn_mounted; int /*<<< orphan*/  cn_treenode; scalar_t__ cn_zoned; void* cn_needpost; int /*<<< orphan*/  cn_shared; int /*<<< orphan*/ * cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_9__ {scalar_t__ cl_realprop; scalar_t__ cl_prop; scalar_t__ cl_shareprop; int cl_gflags; scalar_t__ cl_alldependents; int /*<<< orphan*/  cl_tree; int /*<<< orphan*/  cl_pool; void* cl_haszonedchild; scalar_t__ cl_allchildren; } ;
typedef  TYPE_2__ prop_changelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 void* B_TRUE ; 
 int CL_GATHER_MOUNT_ALWAYS ; 
 scalar_t__ GLOBAL_ZONEID ; 
 scalar_t__ ZFS_IS_VOLUME (int /*<<< orphan*/ *) ; 
 int ZFS_MAXPROPLEN ; 
 scalar_t__ ZFS_PROP_NAME ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 scalar_t__ ZPROP_INVAL ; 
 scalar_t__ ZPROP_SRC_DEFAULT ; 
 scalar_t__ ZPROP_SRC_INHERITED ; 
 scalar_t__ ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/ * uu_avl_find (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_insert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_node_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_handle (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_is_mounted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_shared (int /*<<< orphan*/ *) ; 
 int zfs_iter_children (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,scalar_t__,char*,int,scalar_t__*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
change_one(zfs_handle_t *zhp, void *data)
{
	prop_changelist_t *clp = data;
	char property[ZFS_MAXPROPLEN];
	char where[64];
	prop_changenode_t *cn = NULL;
	zprop_source_t sourcetype = ZPROP_SRC_NONE;
	zprop_source_t share_sourcetype = ZPROP_SRC_NONE;
	int ret = 0;

	/*
	 * We only want to unmount/unshare those filesystems that may inherit
	 * from the target filesystem.  If we find any filesystem with a
	 * locally set mountpoint, we ignore any children since changing the
	 * property will not affect them.  If this is a rename, we iterate
	 * over all children regardless, since we need them unmounted in
	 * order to do the rename.  Also, if this is a volume and we're doing
	 * a rename, then always add it to the changelist.
	 */

	if (!(ZFS_IS_VOLUME(zhp) && clp->cl_realprop == ZFS_PROP_NAME) &&
	    zfs_prop_get(zhp, clp->cl_prop, property,
	    sizeof (property), &sourcetype, where, sizeof (where),
	    B_FALSE) != 0) {
		goto out;
	}

	/*
	 * If we are "watching" sharenfs or sharesmb
	 * then check out the companion property which is tracked
	 * in cl_shareprop
	 */
	if (clp->cl_shareprop != ZPROP_INVAL &&
	    zfs_prop_get(zhp, clp->cl_shareprop, property,
	    sizeof (property), &share_sourcetype, where, sizeof (where),
	    B_FALSE) != 0) {
		goto out;
	}

	if (clp->cl_alldependents || clp->cl_allchildren ||
	    sourcetype == ZPROP_SRC_DEFAULT ||
	    sourcetype == ZPROP_SRC_INHERITED ||
	    (clp->cl_shareprop != ZPROP_INVAL &&
	    (share_sourcetype == ZPROP_SRC_DEFAULT ||
	    share_sourcetype == ZPROP_SRC_INHERITED))) {
		if ((cn = zfs_alloc(zfs_get_handle(zhp),
		    sizeof (prop_changenode_t))) == NULL) {
			ret = -1;
			goto out;
		}

		cn->cn_handle = zhp;
		cn->cn_mounted = (clp->cl_gflags & CL_GATHER_MOUNT_ALWAYS) ||
		    zfs_is_mounted(zhp, NULL);
		cn->cn_shared = zfs_is_shared(zhp);
		cn->cn_zoned = zfs_prop_get_int(zhp, ZFS_PROP_ZONED);
		cn->cn_needpost = B_TRUE;

		/* Indicate if any child is exported to a local zone. */
		if (getzoneid() == GLOBAL_ZONEID && cn->cn_zoned)
			clp->cl_haszonedchild = B_TRUE;

		uu_avl_node_init(cn, &cn->cn_treenode, clp->cl_pool);

		uu_avl_index_t idx;

		if (uu_avl_find(clp->cl_tree, cn, NULL, &idx) == NULL) {
			uu_avl_insert(clp->cl_tree, cn, idx);
		} else {
			free(cn);
			cn = NULL;
		}

		if (!clp->cl_alldependents)
			ret = zfs_iter_children(zhp, change_one, data);

		/*
		 * If we added the handle to the changelist, we will re-use it
		 * later so return without closing it.
		 */
		if (cn != NULL)
			return (ret);
	}

out:
	zfs_close(zhp);
	return (ret);
}