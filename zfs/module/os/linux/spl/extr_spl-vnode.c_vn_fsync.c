#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* v_file; } ;
typedef  TYPE_1__ vnode_t ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int FDSYNC ; 
 int /*<<< orphan*/  __SPL_PF_FSTRANS ; 
 int __spl_pf_fstrans_check () ; 
 TYPE_4__* current ; 
 int spl_filp_fsync (TYPE_1__*,int) ; 

int
vn_fsync(vnode_t *vp, int flags, void *x3, void *x4)
{
	int datasync = 0;
	int error;
	int fstrans;

	ASSERT(vp);
	ASSERT(vp->v_file);

	if (flags & FDSYNC)
		datasync = 1;

	/*
	 * May enter XFS which generates a warning when PF_FSTRANS is set.
	 * To avoid this the flag is cleared over vfs_sync() and then reset.
	 */
	fstrans = __spl_pf_fstrans_check();
	if (fstrans)
		current->flags &= ~(__SPL_PF_FSTRANS);

	error = -spl_filp_fsync(vp->v_file, datasync);
	if (fstrans)
		current->flags |= __SPL_PF_FSTRANS;

	return (error);
}