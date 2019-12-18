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
typedef  scalar_t__ uint64_t ;
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct path {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int LOOKUP_DIRECTORY ; 
 int LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFSCTL_INO_SNAPDIRS ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 struct inode* ilookup (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int kern_path (char*,int,struct path*) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int zfsctl_snapshot_path_objset (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 

int
zfsctl_snapdir_vget(struct super_block *sb, uint64_t objsetid, int gen,
    struct inode **ipp)
{
	int error;
	struct path path;
	char *mnt;
	struct dentry *dentry;

	mnt = kmem_alloc(MAXPATHLEN, KM_SLEEP);

	error = zfsctl_snapshot_path_objset(sb->s_fs_info, objsetid,
	    MAXPATHLEN, mnt);
	if (error)
		goto out;

	/* Trigger automount */
	error = -kern_path(mnt, LOOKUP_FOLLOW|LOOKUP_DIRECTORY, &path);
	if (error)
		goto out;

	path_put(&path);
	/*
	 * Get the snapdir inode. Note, we don't want to use the above
	 * path because it contains the root of the snapshot rather
	 * than the snapdir.
	 */
	*ipp = ilookup(sb, ZFSCTL_INO_SNAPDIRS - objsetid);
	if (*ipp == NULL) {
		error = SET_ERROR(ENOENT);
		goto out;
	}

	/* check gen, see zfsctl_snapdir_fid */
	dentry = d_obtain_alias(igrab(*ipp));
	if (gen != (!IS_ERR(dentry) && d_mountpoint(dentry))) {
		iput(*ipp);
		*ipp = NULL;
		error = SET_ERROR(ENOENT);
	}
	if (!IS_ERR(dentry))
		dput(dentry);
out:
	kmem_free(mnt, MAXPATHLEN);
	return (error);
}