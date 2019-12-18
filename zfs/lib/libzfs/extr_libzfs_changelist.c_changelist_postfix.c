#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
typedef  int /*<<< orphan*/  shareopts ;
struct TYPE_17__ {TYPE_3__* cn_handle; scalar_t__ cn_shared; scalar_t__ cn_mounted; scalar_t__ cn_needpost; scalar_t__ cn_zoned; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_18__ {scalar_t__ cl_prop; scalar_t__ cl_waslegacy; int /*<<< orphan*/  cl_tree; } ;
typedef  TYPE_2__ prop_changelist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int boolean_t ;
struct TYPE_19__ {int /*<<< orphan*/ * zfs_hdl; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int TRUE ; 
 int UU_WALK_REVERSE ; 
 int UU_WALK_ROBUST ; 
 scalar_t__ ZFS_CANMOUNT_ON ; 
 scalar_t__ ZFS_IS_VOLUME (TYPE_3__*) ; 
 scalar_t__ ZFS_KEYSTATUS_UNAVAILABLE ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_CANMOUNT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 scalar_t__ ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  ZFS_PROP_SHARESMB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/  remove_mountpoint (TYPE_3__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__* uu_avl_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ ,int) ; 
 int zfs_is_mounted (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_mount (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zfs_prop_get_int (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refresh_properties (TYPE_3__*) ; 
 scalar_t__ zfs_share_nfs (TYPE_3__*) ; 
 scalar_t__ zfs_share_smb (TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_uninit_libshare (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_unshare_nfs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_unshare_smb (TYPE_3__*,int /*<<< orphan*/ *) ; 

int
changelist_postfix(prop_changelist_t *clp)
{
	prop_changenode_t *cn;
	uu_avl_walk_t *walk;
	char shareopts[ZFS_MAXPROPLEN];
	int errors = 0;
	libzfs_handle_t *hdl;

	/*
	 * If we're changing the mountpoint, attempt to destroy the underlying
	 * mountpoint.  All other datasets will have inherited from this dataset
	 * (in which case their mountpoints exist in the filesystem in the new
	 * location), or have explicit mountpoints set (in which case they won't
	 * be in the changelist).
	 */
	if ((cn = uu_avl_last(clp->cl_tree)) == NULL)
		return (0);

	if (clp->cl_prop == ZFS_PROP_MOUNTPOINT)
		remove_mountpoint(cn->cn_handle);

	/*
	 * It is possible that the changelist_prefix() used libshare
	 * to unshare some entries. Since libshare caches data, an
	 * attempt to reshare during postfix can fail unless libshare
	 * is uninitialized here so that it will reinitialize later.
	 */
	if (cn->cn_handle != NULL) {
		hdl = cn->cn_handle->zfs_hdl;
		assert(hdl != NULL);
		zfs_uninit_libshare(hdl);
	}

	/*
	 * We walk the datasets in reverse, because we want to mount any parent
	 * datasets before mounting the children.  We walk all datasets even if
	 * there are errors.
	 */
	if ((walk = uu_avl_walk_start(clp->cl_tree,
	    UU_WALK_REVERSE | UU_WALK_ROBUST)) == NULL)
		return (-1);

	while ((cn = uu_avl_walk_next(walk)) != NULL) {

		boolean_t sharenfs;
		boolean_t sharesmb;
		boolean_t mounted;
		boolean_t needs_key;

		/*
		 * If we are in the global zone, but this dataset is exported
		 * to a local zone, do nothing.
		 */
		if (getzoneid() == GLOBAL_ZONEID && cn->cn_zoned)
			continue;

		/* Only do post-processing if it's required */
		if (!cn->cn_needpost)
			continue;
		cn->cn_needpost = B_FALSE;

		zfs_refresh_properties(cn->cn_handle);

		if (ZFS_IS_VOLUME(cn->cn_handle))
			continue;

		/*
		 * Remount if previously mounted or mountpoint was legacy,
		 * or sharenfs or sharesmb  property is set.
		 */
		sharenfs = ((zfs_prop_get(cn->cn_handle, ZFS_PROP_SHARENFS,
		    shareopts, sizeof (shareopts), NULL, NULL, 0,
		    B_FALSE) == 0) && (strcmp(shareopts, "off") != 0));

		sharesmb = ((zfs_prop_get(cn->cn_handle, ZFS_PROP_SHARESMB,
		    shareopts, sizeof (shareopts), NULL, NULL, 0,
		    B_FALSE) == 0) && (strcmp(shareopts, "off") != 0));

		needs_key = (zfs_prop_get_int(cn->cn_handle,
		    ZFS_PROP_KEYSTATUS) == ZFS_KEYSTATUS_UNAVAILABLE);

		mounted = zfs_is_mounted(cn->cn_handle, NULL);

		if (!mounted && !needs_key && (cn->cn_mounted ||
		    ((sharenfs || sharesmb || clp->cl_waslegacy) &&
		    (zfs_prop_get_int(cn->cn_handle,
		    ZFS_PROP_CANMOUNT) == ZFS_CANMOUNT_ON)))) {

			if (zfs_mount(cn->cn_handle, NULL, 0) != 0)
				errors++;
			else
				mounted = TRUE;
		}

		/*
		 * If the file system is mounted we always re-share even
		 * if the filesystem is currently shared, so that we can
		 * adopt any new options.
		 */
		if (sharenfs && mounted)
			errors += zfs_share_nfs(cn->cn_handle);
		else if (cn->cn_shared || clp->cl_waslegacy)
			errors += zfs_unshare_nfs(cn->cn_handle, NULL);
		if (sharesmb && mounted)
			errors += zfs_share_smb(cn->cn_handle);
		else if (cn->cn_shared || clp->cl_waslegacy)
			errors += zfs_unshare_smb(cn->cn_handle, NULL);
	}

	uu_avl_walk_end(walk);

	return (errors ? -1 : 0);
}