#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct TYPE_6__ {int /*<<< orphan*/  z_root; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 struct inode* ZTOI (int /*<<< orphan*/ *) ; 
 int zfs_zget (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
zfs_root(zfsvfs_t *zfsvfs, struct inode **ipp)
{
	znode_t *rootzp;
	int error;

	ZFS_ENTER(zfsvfs);

	error = zfs_zget(zfsvfs, zfsvfs->z_root, &rootzp);
	if (error == 0)
		*ipp = ZTOI(rootzp);

	ZFS_EXIT(zfsvfs);
	return (error);
}