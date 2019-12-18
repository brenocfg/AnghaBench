#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct inode {TYPE_2__* i_sb; } ;
typedef  int /*<<< orphan*/  pathname_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_4__ {TYPE_1__* s_root; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFSCTL_INO_SHARES ; 
 int /*<<< orphan*/  ZFSCTL_INO_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 char* ZFS_SHAREDIR_NAME ; 
 char* ZFS_SNAPDIR_NAME ; 
 scalar_t__ strcmp (char*,char*) ; 
 struct inode* zfsctl_inode_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpl_fops_shares ; 
 int /*<<< orphan*/  zpl_fops_snapdir ; 
 int /*<<< orphan*/  zpl_ops_shares ; 
 int /*<<< orphan*/  zpl_ops_snapdir ; 

int
zfsctl_root_lookup(struct inode *dip, char *name, struct inode **ipp,
    int flags, cred_t *cr, int *direntflags, pathname_t *realpnp)
{
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	int error = 0;

	ZFS_ENTER(zfsvfs);

	if (strcmp(name, "..") == 0) {
		*ipp = dip->i_sb->s_root->d_inode;
	} else if (strcmp(name, ZFS_SNAPDIR_NAME) == 0) {
		*ipp = zfsctl_inode_lookup(zfsvfs, ZFSCTL_INO_SNAPDIR,
		    &zpl_fops_snapdir, &zpl_ops_snapdir);
	} else if (strcmp(name, ZFS_SHAREDIR_NAME) == 0) {
		*ipp = zfsctl_inode_lookup(zfsvfs, ZFSCTL_INO_SHARES,
		    &zpl_fops_shares, &zpl_ops_shares);
	} else {
		*ipp = NULL;
	}

	if (*ipp == NULL)
		error = SET_ERROR(ENOENT);

	ZFS_EXIT(zfsvfs);

	return (error);
}