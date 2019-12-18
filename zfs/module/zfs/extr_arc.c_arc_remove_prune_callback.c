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
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_refcnt; } ;
typedef  TYPE_1__ arc_prune_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  arc_prune_list ; 
 int /*<<< orphan*/  arc_prune_mtx ; 
 int /*<<< orphan*/  arc_prune_taskq ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_wait_outstanding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arc_remove_prune_callback(arc_prune_t *p)
{
	boolean_t wait = B_FALSE;
	mutex_enter(&arc_prune_mtx);
	list_remove(&arc_prune_list, p);
	if (zfs_refcount_remove(&p->p_refcnt, &arc_prune_list) > 0)
		wait = B_TRUE;
	mutex_exit(&arc_prune_mtx);

	/* wait for arc_prune_task to finish */
	if (wait)
		taskq_wait_outstanding(arc_prune_taskq, 0);
	ASSERT0(zfs_refcount_count(&p->p_refcnt));
	zfs_refcount_destroy(&p->p_refcnt);
	kmem_free(p, sizeof (*p));
}