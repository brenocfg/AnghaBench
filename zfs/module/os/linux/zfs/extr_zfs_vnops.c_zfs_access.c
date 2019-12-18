#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/ * ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 int V_ACE_MASK ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (int /*<<< orphan*/ *) ; 
 int zfs_zaccess (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_rwx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

int
zfs_access(struct inode *ip, int mode, int flag, cred_t *cr)
{
	znode_t *zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);
	int error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if (flag & V_ACE_MASK)
		error = zfs_zaccess(zp, mode, flag, B_FALSE, cr);
	else
		error = zfs_zaccess_rwx(zp, mode, flag, cr);

	ZFS_EXIT(zfsvfs);
	return (error);
}