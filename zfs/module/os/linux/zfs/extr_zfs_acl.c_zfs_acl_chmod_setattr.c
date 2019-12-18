#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int z_pflags; int /*<<< orphan*/  z_acl_lock; int /*<<< orphan*/  z_lock; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_11__ {int z_hints; } ;
typedef  TYPE_2__ zfs_acl_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int V4_ACL_WIDE_FLAGS ; 
 int /*<<< orphan*/  ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_2__* zfs_acl_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_acl_chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_acl_version_zp (TYPE_1__*) ; 

int
zfs_acl_chmod_setattr(znode_t *zp, zfs_acl_t **aclp, uint64_t mode)
{
	mutex_enter(&zp->z_acl_lock);
	mutex_enter(&zp->z_lock);
	*aclp = zfs_acl_alloc(zfs_acl_version_zp(zp));
	(*aclp)->z_hints = zp->z_pflags & V4_ACL_WIDE_FLAGS;
	zfs_acl_chmod(ZTOZSB(zp), mode, *aclp);
	mutex_exit(&zp->z_lock);
	mutex_exit(&zp->z_acl_lock);
	ASSERT(*aclp);

	return (0);
}