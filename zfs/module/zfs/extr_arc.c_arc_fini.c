#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_refcnt; } ;
typedef  TYPE_1__ arc_prune_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  arc_adjust_lock ; 
 int /*<<< orphan*/  arc_adjust_waiters_cv ; 
 int /*<<< orphan*/  arc_adjust_zthr ; 
 int /*<<< orphan*/  arc_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_initialized ; 
 int /*<<< orphan*/ * arc_ksp ; 
 int /*<<< orphan*/  arc_loaned_bytes ; 
 int /*<<< orphan*/  arc_lowmem_fini () ; 
 int /*<<< orphan*/  arc_prune_list ; 
 int /*<<< orphan*/  arc_prune_mtx ; 
 int /*<<< orphan*/  arc_prune_taskq ; 
 int /*<<< orphan*/  arc_reap_zthr ; 
 int /*<<< orphan*/  arc_state_fini () ; 
 int /*<<< orphan*/  buf_fini () ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kstat_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zthr_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zthr_destroy (int /*<<< orphan*/ ) ; 

void
arc_fini(void)
{
	arc_prune_t *p;

#ifdef _KERNEL
	arc_lowmem_fini();
#endif /* _KERNEL */

	/* Use B_TRUE to ensure *all* buffers are evicted */
	arc_flush(NULL, B_TRUE);

	arc_initialized = B_FALSE;

	if (arc_ksp != NULL) {
		kstat_delete(arc_ksp);
		arc_ksp = NULL;
	}

	taskq_wait(arc_prune_taskq);
	taskq_destroy(arc_prune_taskq);

	mutex_enter(&arc_prune_mtx);
	while ((p = list_head(&arc_prune_list)) != NULL) {
		list_remove(&arc_prune_list, p);
		zfs_refcount_remove(&p->p_refcnt, &arc_prune_list);
		zfs_refcount_destroy(&p->p_refcnt);
		kmem_free(p, sizeof (*p));
	}
	mutex_exit(&arc_prune_mtx);

	list_destroy(&arc_prune_list);
	mutex_destroy(&arc_prune_mtx);

	(void) zthr_cancel(arc_adjust_zthr);
	(void) zthr_cancel(arc_reap_zthr);

	mutex_destroy(&arc_adjust_lock);
	cv_destroy(&arc_adjust_waiters_cv);

	/*
	 * buf_fini() must proceed arc_state_fini() because buf_fin() may
	 * trigger the release of kmem magazines, which can callback to
	 * arc_space_return() which accesses aggsums freed in act_state_fini().
	 */
	buf_fini();
	arc_state_fini();

	/*
	 * We destroy the zthrs after all the ARC state has been
	 * torn down to avoid the case of them receiving any
	 * wakeup() signals after they are destroyed.
	 */
	zthr_destroy(arc_adjust_zthr);
	zthr_destroy(arc_reap_zthr);

	ASSERT0(arc_loaned_bytes);
}