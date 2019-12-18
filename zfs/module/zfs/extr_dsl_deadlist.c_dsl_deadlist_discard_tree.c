#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dl_lock; scalar_t__ dl_havetree; int /*<<< orphan*/  dl_tree; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  dle_bpobj; } ;
typedef  TYPE_2__ dsl_deadlist_entry_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_discard_tree(dsl_deadlist_t *dl)
{
	mutex_enter(&dl->dl_lock);

	if (!dl->dl_havetree) {
		mutex_exit(&dl->dl_lock);
		return;
	}
	dsl_deadlist_entry_t *dle;
	void *cookie = NULL;
	while ((dle = avl_destroy_nodes(&dl->dl_tree, &cookie)) != NULL) {
		bpobj_close(&dle->dle_bpobj);
		kmem_free(dle, sizeof (*dle));
	}
	avl_destroy(&dl->dl_tree);

	dl->dl_havetree = B_FALSE;
	mutex_exit(&dl->dl_lock);
}