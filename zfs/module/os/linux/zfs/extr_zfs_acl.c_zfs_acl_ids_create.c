#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_25__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int z_mode; int z_pflags; int /*<<< orphan*/  z_acl_lock; int /*<<< orphan*/  z_lock; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_29__ {int /*<<< orphan*/  z_fuid_idx; scalar_t__ z_use_fuids; scalar_t__ z_replay; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_acl_t ;
struct TYPE_30__ {int z_mode; TYPE_6__* z_aclp; void* z_fgid; void* z_fuid; int /*<<< orphan*/  z_fuidp; } ;
typedef  TYPE_3__ zfs_acl_ids_t ;
typedef  int /*<<< orphan*/  vsecattr_t ;
struct TYPE_31__ {int va_mode; int va_mask; void* va_gid; void* va_uid; } ;
typedef  TYPE_4__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* gid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_32__ {int /*<<< orphan*/  z_hints; } ;
struct TYPE_28__ {int i_mode; int /*<<< orphan*/  i_gid; } ;

/* Variables and functions */
 int AT_GID ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  FUID_INDEX (void*) ; 
 int /*<<< orphan*/  FUID_RID (void*) ; 
 scalar_t__ IS_EPHEMERAL (void*) ; 
 int IS_ROOT_NODE ; 
 int IS_XATTR ; 
 void* KGID_TO_SGID (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_ACL_AUTO_INHERIT ; 
 int /*<<< orphan*/  ZFS_ACL_TRIVIAL ; 
 int /*<<< orphan*/  ZFS_GROUP ; 
 int ZFS_INHERIT_ACE ; 
 int /*<<< orphan*/  ZFS_OWNER ; 
 int ZFS_XATTR ; 
 TYPE_25__* ZTOI (TYPE_1__*) ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 scalar_t__ ace_trivial_common (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 void* crgetgid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  groupmember (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ secpolicy_vnode_create_gid (int /*<<< orphan*/ *) ; 
 scalar_t__ secpolicy_vnode_setids_setgids (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zfs_ace_walk ; 
 TYPE_6__* zfs_acl_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_acl_chmod (TYPE_2__*,int,TYPE_6__*) ; 
 TYPE_6__* zfs_acl_inherit (TYPE_2__*,int,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 scalar_t__ zfs_acl_node_read (TYPE_1__*,scalar_t__,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  zfs_acl_version_zp (TYPE_1__*) ; 
 void* zfs_fuid_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* zfs_fuid_create_cred (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zfs_fuid_idx_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* zfs_fuid_map_id (TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fuid_node_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int zfs_mode_compute (int,TYPE_6__*,int /*<<< orphan*/ *,void*,void*) ; 
 int zfs_vsec_2_aclp (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__**) ; 

int
zfs_acl_ids_create(znode_t *dzp, int flag, vattr_t *vap, cred_t *cr,
    vsecattr_t *vsecp, zfs_acl_ids_t *acl_ids)
{
	int		error;
	zfsvfs_t	*zfsvfs = ZTOZSB(dzp);
	zfs_acl_t	*paclp;
	gid_t		gid = vap->va_gid;
	boolean_t	need_chmod = B_TRUE;
	boolean_t	inherited = B_FALSE;

	bzero(acl_ids, sizeof (zfs_acl_ids_t));
	acl_ids->z_mode = vap->va_mode;

	if (vsecp)
		if ((error = zfs_vsec_2_aclp(zfsvfs, vap->va_mode, vsecp,
		    cr, &acl_ids->z_fuidp, &acl_ids->z_aclp)) != 0)
			return (error);

	acl_ids->z_fuid = vap->va_uid;
	acl_ids->z_fgid = vap->va_gid;
#ifdef HAVE_KSID
	/*
	 * Determine uid and gid.
	 */
	if ((flag & IS_ROOT_NODE) || zfsvfs->z_replay ||
	    ((flag & IS_XATTR) && (S_ISDIR(vap->va_mode)))) {
		acl_ids->z_fuid = zfs_fuid_create(zfsvfs, (uint64_t)vap->va_uid,
		    cr, ZFS_OWNER, &acl_ids->z_fuidp);
		acl_ids->z_fgid = zfs_fuid_create(zfsvfs, (uint64_t)vap->va_gid,
		    cr, ZFS_GROUP, &acl_ids->z_fuidp);
		gid = vap->va_gid;
	} else {
		acl_ids->z_fuid = zfs_fuid_create_cred(zfsvfs, ZFS_OWNER,
		    cr, &acl_ids->z_fuidp);
		acl_ids->z_fgid = 0;
		if (vap->va_mask & AT_GID)  {
			acl_ids->z_fgid = zfs_fuid_create(zfsvfs,
			    (uint64_t)vap->va_gid,
			    cr, ZFS_GROUP, &acl_ids->z_fuidp);
			gid = vap->va_gid;
			if (acl_ids->z_fgid != KGID_TO_SGID(ZTOI(dzp)->i_gid) &&
			    !groupmember(vap->va_gid, cr) &&
			    secpolicy_vnode_create_gid(cr) != 0)
				acl_ids->z_fgid = 0;
		}
		if (acl_ids->z_fgid == 0) {
			if (dzp->z_mode & S_ISGID) {
				char		*domain;
				uint32_t	rid;

				acl_ids->z_fgid = KGID_TO_SGID(
				    ZTOI(dzp)->i_gid);
				gid = zfs_fuid_map_id(zfsvfs, acl_ids->z_fgid,
				    cr, ZFS_GROUP);

				if (zfsvfs->z_use_fuids &&
				    IS_EPHEMERAL(acl_ids->z_fgid)) {
					domain = zfs_fuid_idx_domain(
					    &zfsvfs->z_fuid_idx,
					    FUID_INDEX(acl_ids->z_fgid));
					rid = FUID_RID(acl_ids->z_fgid);
					zfs_fuid_node_add(&acl_ids->z_fuidp,
					    domain, rid,
					    FUID_INDEX(acl_ids->z_fgid),
					    acl_ids->z_fgid, ZFS_GROUP);
				}
			} else {
				acl_ids->z_fgid = zfs_fuid_create_cred(zfsvfs,
				    ZFS_GROUP, cr, &acl_ids->z_fuidp);
				gid = crgetgid(cr);
			}
		}
	}
#endif /* HAVE_KSID */

	/*
	 * If we're creating a directory, and the parent directory has the
	 * set-GID bit set, set in on the new directory.
	 * Otherwise, if the user is neither privileged nor a member of the
	 * file's new group, clear the file's set-GID bit.
	 */

	if (!(flag & IS_ROOT_NODE) && (dzp->z_mode & S_ISGID) &&
	    (S_ISDIR(vap->va_mode))) {
		acl_ids->z_mode |= S_ISGID;
	} else {
		if ((acl_ids->z_mode & S_ISGID) &&
		    secpolicy_vnode_setids_setgids(cr, gid) != 0)
			acl_ids->z_mode &= ~S_ISGID;
	}

	if (acl_ids->z_aclp == NULL) {
		mutex_enter(&dzp->z_acl_lock);
		mutex_enter(&dzp->z_lock);
		if (!(flag & IS_ROOT_NODE) && (S_ISDIR(ZTOI(dzp)->i_mode) &&
		    (dzp->z_pflags & ZFS_INHERIT_ACE)) &&
		    !(dzp->z_pflags & ZFS_XATTR)) {
			VERIFY(0 == zfs_acl_node_read(dzp, B_TRUE,
			    &paclp, B_FALSE));
			acl_ids->z_aclp = zfs_acl_inherit(zfsvfs,
			    vap->va_mode, paclp, acl_ids->z_mode, &need_chmod);
			inherited = B_TRUE;
		} else {
			acl_ids->z_aclp =
			    zfs_acl_alloc(zfs_acl_version_zp(dzp));
			acl_ids->z_aclp->z_hints |= ZFS_ACL_TRIVIAL;
		}
		mutex_exit(&dzp->z_lock);
		mutex_exit(&dzp->z_acl_lock);
		if (need_chmod) {
			acl_ids->z_aclp->z_hints |= S_ISDIR(vap->va_mode) ?
			    ZFS_ACL_AUTO_INHERIT : 0;
			zfs_acl_chmod(zfsvfs, acl_ids->z_mode, acl_ids->z_aclp);
		}
	}

	if (inherited || vsecp) {
		acl_ids->z_mode = zfs_mode_compute(acl_ids->z_mode,
		    acl_ids->z_aclp, &acl_ids->z_aclp->z_hints,
		    acl_ids->z_fuid, acl_ids->z_fgid);
		if (ace_trivial_common(acl_ids->z_aclp, 0, zfs_ace_walk) == 0)
			acl_ids->z_aclp->z_hints |= ZFS_ACL_TRIVIAL;
	}

	return (0);
}