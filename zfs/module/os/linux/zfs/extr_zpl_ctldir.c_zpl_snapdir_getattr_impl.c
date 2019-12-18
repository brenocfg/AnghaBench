#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  u32 ;
struct path {TYPE_1__* dentry; } ;
struct kstat {int nlink; int size; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  ctime; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_2__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dmu_objset_snap_cmtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 

__attribute__((used)) static int
zpl_snapdir_getattr_impl(const struct path *path, struct kstat *stat,
    u32 request_mask, unsigned int query_flags)
{
	struct inode *ip = path->dentry->d_inode;
	zfsvfs_t *zfsvfs = ITOZSB(ip);

	ZFS_ENTER(zfsvfs);
	generic_fillattr(ip, stat);

	stat->nlink = stat->size = 2;
	stat->ctime = stat->mtime = dmu_objset_snap_cmtime(zfsvfs->z_os);
	stat->atime = current_time(ip);
	ZFS_EXIT(zfsvfs);

	return (0);
}