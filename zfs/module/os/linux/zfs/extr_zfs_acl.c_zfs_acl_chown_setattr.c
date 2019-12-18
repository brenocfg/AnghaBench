#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  z_pflags; int /*<<< orphan*/  z_mode; int /*<<< orphan*/  z_acl_lock; int /*<<< orphan*/  z_lock; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_12__ {scalar_t__ z_acl_count; } ;
typedef  TYPE_2__ zfs_acl_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_13__ {scalar_t__ z_acl_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 int /*<<< orphan*/  KGID_TO_SGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ ZFS_ACLTYPE_POSIXACL ; 
 TYPE_9__* ZTOI (TYPE_1__*) ; 
 TYPE_7__* ZTOZSB (TYPE_1__*) ; 
 int zfs_acl_node_read (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_mode_compute (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_acl_chown_setattr(znode_t *zp)
{
	int error;
	zfs_acl_t *aclp;

	if (ZTOZSB(zp)->z_acl_type == ZFS_ACLTYPE_POSIXACL)
		return (0);

	ASSERT(MUTEX_HELD(&zp->z_lock));
	ASSERT(MUTEX_HELD(&zp->z_acl_lock));

	error = zfs_acl_node_read(zp, B_TRUE, &aclp, B_FALSE);
	if (error == 0 && aclp->z_acl_count > 0)
		zp->z_mode = ZTOI(zp)->i_mode =
		    zfs_mode_compute(zp->z_mode, aclp,
		    &zp->z_pflags, KUID_TO_SUID(ZTOI(zp)->i_uid),
		    KGID_TO_SGID(ZTOI(zp)->i_gid));

	/*
	 * Some ZFS implementations (ZEVO) create neither a ZNODE_ACL
	 * nor a DACL_ACES SA in which case ENOENT is returned from
	 * zfs_acl_node_read() when the SA can't be located.
	 * Allow chown/chgrp to succeed in these cases rather than
	 * returning an error that makes no sense in the context of
	 * the caller.
	 */
	if (error == ENOENT)
		return (0);

	return (error);
}