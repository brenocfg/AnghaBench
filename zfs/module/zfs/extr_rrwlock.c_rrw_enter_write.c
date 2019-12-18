#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rr_lock; int /*<<< orphan*/ * rr_writer; int /*<<< orphan*/  rr_writer_wanted; int /*<<< orphan*/  rr_cv; int /*<<< orphan*/  rr_linked_rcount; int /*<<< orphan*/  rr_anon_rcount; } ;
typedef  TYPE_1__ rrwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

void
rrw_enter_write(rrwlock_t *rrl)
{
	mutex_enter(&rrl->rr_lock);
	ASSERT(rrl->rr_writer != curthread);

	while (zfs_refcount_count(&rrl->rr_anon_rcount) > 0 ||
	    zfs_refcount_count(&rrl->rr_linked_rcount) > 0 ||
	    rrl->rr_writer != NULL) {
		rrl->rr_writer_wanted = B_TRUE;
		cv_wait(&rrl->rr_cv, &rrl->rr_lock);
	}
	rrl->rr_writer_wanted = B_FALSE;
	rrl->rr_writer = curthread;
	mutex_exit(&rrl->rr_lock);
}