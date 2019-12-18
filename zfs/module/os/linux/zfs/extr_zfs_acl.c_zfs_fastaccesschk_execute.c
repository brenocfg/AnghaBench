#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int z_pflags; int z_mode; int /*<<< orphan*/  z_acl_lock; } ;
typedef  TYPE_1__ znode_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_EXECUTE ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int /*<<< orphan*/  DTRACE_PROBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EACCES ; 
 scalar_t__ KGID_TO_SGID (int /*<<< orphan*/ ) ; 
 scalar_t__ KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ ) ; 
 int ZFS_NO_EXECS_DENIED ; 
 int ZFS_XATTR ; 
 TYPE_5__* ZTOI (TYPE_1__*) ; 
 int /*<<< orphan*/  ZTOZSB (TYPE_1__*) ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 scalar_t__ groupmember (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs__fastpath__execute__access__miss ; 
 int zfs_zaccess (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
zfs_fastaccesschk_execute(znode_t *zdp, cred_t *cr)
{
	boolean_t owner = B_FALSE;
	boolean_t groupmbr = B_FALSE;
	boolean_t is_attr;
	uid_t uid = crgetuid(cr);
	int error;

	if (zdp->z_pflags & ZFS_AV_QUARANTINED)
		return (SET_ERROR(EACCES));

	is_attr = ((zdp->z_pflags & ZFS_XATTR) &&
	    (S_ISDIR(ZTOI(zdp)->i_mode)));
	if (is_attr)
		goto slow;


	mutex_enter(&zdp->z_acl_lock);

	if (zdp->z_pflags & ZFS_NO_EXECS_DENIED) {
		mutex_exit(&zdp->z_acl_lock);
		return (0);
	}

	if (KUID_TO_SUID(ZTOI(zdp)->i_uid) != 0 ||
	    KGID_TO_SGID(ZTOI(zdp)->i_gid) != 0) {
		mutex_exit(&zdp->z_acl_lock);
		goto slow;
	}

	if (uid == KUID_TO_SUID(ZTOI(zdp)->i_uid)) {
		owner = B_TRUE;
		if (zdp->z_mode & S_IXUSR) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		} else {
			mutex_exit(&zdp->z_acl_lock);
			goto slow;
		}
	}
	if (groupmember(KGID_TO_SGID(ZTOI(zdp)->i_gid), cr)) {
		groupmbr = B_TRUE;
		if (zdp->z_mode & S_IXGRP) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		} else {
			mutex_exit(&zdp->z_acl_lock);
			goto slow;
		}
	}
	if (!owner && !groupmbr) {
		if (zdp->z_mode & S_IXOTH) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		}
	}

	mutex_exit(&zdp->z_acl_lock);

slow:
	DTRACE_PROBE(zfs__fastpath__execute__access__miss);
	ZFS_ENTER(ZTOZSB(zdp));
	error = zfs_zaccess(zdp, ACE_EXECUTE, 0, B_FALSE, cr);
	ZFS_EXIT(ZTOZSB(zdp));
	return (error);
}