#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_is_mapped; } ;
typedef  TYPE_2__ znode_t ;
struct vm_area_struct {int /*<<< orphan*/  vm_flags; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_2__* ITOZ (struct inode*) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int zfs_map (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zpl_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct inode *ip = filp->f_mapping->host;
	znode_t *zp = ITOZ(ip);
	int error;
	fstrans_cookie_t cookie;

	cookie = spl_fstrans_mark();
	error = -zfs_map(ip, vma->vm_pgoff, (caddr_t *)vma->vm_start,
	    (size_t)(vma->vm_end - vma->vm_start), vma->vm_flags);
	spl_fstrans_unmark(cookie);
	if (error)
		return (error);

	error = generic_file_mmap(filp, vma);
	if (error)
		return (error);

	mutex_enter(&zp->z_lock);
	zp->z_is_mapped = B_TRUE;
	mutex_exit(&zp->z_lock);

	return (error);
}