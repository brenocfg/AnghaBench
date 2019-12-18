#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  v_lock; struct file* v_file; int /*<<< orphan*/  v_type; } ;
typedef  TYPE_1__ vnode_t ;
struct kstat {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  mnt; } ;
struct file {int /*<<< orphan*/  f_dentry; TYPE_6__ f_path; } ;
struct TYPE_11__ {int f_fd; int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_list; struct file* f_file; TYPE_1__* f_vnode; int /*<<< orphan*/  f_ref; scalar_t__ f_offset; int /*<<< orphan*/  f_task; } ;
typedef  TYPE_2__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  STATX_TYPE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct file* fget (int) ; 
 TYPE_2__* file_find (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vfs_getattr (TYPE_6__*,struct kstat*,...) ; 
 TYPE_1__* vn_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_file_cache ; 
 int /*<<< orphan*/  vn_file_list ; 
 int /*<<< orphan*/  vn_file_lock ; 
 int /*<<< orphan*/  vn_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vn_mode_to_vtype (int /*<<< orphan*/ ) ; 

file_t *
vn_getf(int fd)
{
	struct kstat stat;
	struct file *lfp;
	file_t *fp;
	vnode_t *vp;
	int rc = 0;

	if (fd < 0)
		return (NULL);

	/* Already open just take an extra reference */
	spin_lock(&vn_file_lock);

	fp = file_find(fd, current);
	if (fp) {
		lfp = fget(fd);
		fput(fp->f_file);
		/*
		 * areleasef() can cause us to see a stale reference when
		 * userspace has reused a file descriptor before areleasef()
		 * has run. fput() the stale reference and replace it. We
		 * retain the original reference count such that the concurrent
		 * areleasef() will decrement its reference and terminate.
		 */
		if (lfp != fp->f_file) {
			fp->f_file = lfp;
			fp->f_vnode->v_file = lfp;
		}
		atomic_inc(&fp->f_ref);
		spin_unlock(&vn_file_lock);
		return (fp);
	}

	spin_unlock(&vn_file_lock);

	/* File was not yet opened create the object and setup */
	fp = kmem_cache_alloc(vn_file_cache, KM_SLEEP);
	if (fp == NULL)
		goto out;

	mutex_enter(&fp->f_lock);

	fp->f_fd = fd;
	fp->f_task = current;
	fp->f_offset = 0;
	atomic_inc(&fp->f_ref);

	lfp = fget(fd);
	if (lfp == NULL)
		goto out_mutex;

	vp = vn_alloc(KM_SLEEP);
	if (vp == NULL)
		goto out_fget;

#if defined(HAVE_4ARGS_VFS_GETATTR)
	rc = vfs_getattr(&lfp->f_path, &stat, STATX_TYPE,
	    AT_STATX_SYNC_AS_STAT);
#elif defined(HAVE_2ARGS_VFS_GETATTR)
	rc = vfs_getattr(&lfp->f_path, &stat);
#else
	rc = vfs_getattr(lfp->f_path.mnt, lfp->f_dentry, &stat);
#endif
	if (rc)
		goto out_vnode;

	mutex_enter(&vp->v_lock);
	vp->v_type = vn_mode_to_vtype(stat.mode);
	vp->v_file = lfp;
	mutex_exit(&vp->v_lock);

	fp->f_vnode = vp;
	fp->f_file = lfp;

	/* Put it on the tracking list */
	spin_lock(&vn_file_lock);
	list_add(&fp->f_list, &vn_file_list);
	spin_unlock(&vn_file_lock);

	mutex_exit(&fp->f_lock);
	return (fp);

out_vnode:
	vn_free(vp);
out_fget:
	fput(lfp);
out_mutex:
	mutex_exit(&fp->f_lock);
	kmem_cache_free(vn_file_cache, fp);
out:
	return (NULL);
}