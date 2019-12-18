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
struct TYPE_3__ {int /*<<< orphan*/  rr_linked_rcount; int /*<<< orphan*/  rr_anon_rcount; int /*<<< orphan*/ * rr_writer; int /*<<< orphan*/  rr_cv; int /*<<< orphan*/  rr_lock; } ;
typedef  TYPE_1__ rrwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

void
rrw_destroy(rrwlock_t *rrl)
{
	mutex_destroy(&rrl->rr_lock);
	cv_destroy(&rrl->rr_cv);
	ASSERT(rrl->rr_writer == NULL);
	zfs_refcount_destroy(&rrl->rr_anon_rcount);
	zfs_refcount_destroy(&rrl->rr_linked_rcount);
}