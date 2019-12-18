#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rc_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  rr_lock; int /*<<< orphan*/ * rr_writer; TYPE_2__ rr_anon_rcount; TYPE_2__ rr_linked_rcount; scalar_t__ rr_track_all; scalar_t__ rr_writer_wanted; int /*<<< orphan*/  rr_cv; } ;
typedef  TYPE_1__ rrwlock_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_PROBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrn_add (TYPE_1__*,void*) ; 
 int /*<<< orphan*/ * rrn_find (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs__rrwfastpath__rdmiss ; 
 int /*<<< orphan*/  zfs_refcount_add (TYPE_2__*,void*) ; 
 scalar_t__ zfs_refcount_count (TYPE_2__*) ; 
 scalar_t__ zfs_refcount_is_zero (TYPE_2__*) ; 

__attribute__((used)) static void
rrw_enter_read_impl(rrwlock_t *rrl, boolean_t prio, void *tag)
{
	mutex_enter(&rrl->rr_lock);
#if !defined(DEBUG) && defined(_KERNEL)
	if (rrl->rr_writer == NULL && !rrl->rr_writer_wanted &&
	    !rrl->rr_track_all) {
		rrl->rr_anon_rcount.rc_count++;
		mutex_exit(&rrl->rr_lock);
		return;
	}
	DTRACE_PROBE(zfs__rrwfastpath__rdmiss);
#endif
	ASSERT(rrl->rr_writer != curthread);
	ASSERT(zfs_refcount_count(&rrl->rr_anon_rcount) >= 0);

	while (rrl->rr_writer != NULL || (rrl->rr_writer_wanted &&
	    zfs_refcount_is_zero(&rrl->rr_anon_rcount) && !prio &&
	    rrn_find(rrl) == NULL))
		cv_wait(&rrl->rr_cv, &rrl->rr_lock);

	if (rrl->rr_writer_wanted || rrl->rr_track_all) {
		/* may or may not be a re-entrant enter */
		rrn_add(rrl, tag);
		(void) zfs_refcount_add(&rrl->rr_linked_rcount, tag);
	} else {
		(void) zfs_refcount_add(&rrl->rr_anon_rcount, tag);
	}
	ASSERT(rrl->rr_writer == NULL);
	mutex_exit(&rrl->rr_lock);
}