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
struct TYPE_5__ {int /*<<< orphan*/  dl_tree; int /*<<< orphan*/  dl_lock; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
typedef  int /*<<< orphan*/  dsl_deadlist_entry_t ;
typedef  scalar_t__ (* deadlist_iter_t ) (void*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AVL_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_iterate(dsl_deadlist_t *dl, deadlist_iter_t func, void *args)
{
	dsl_deadlist_entry_t *dle;

	ASSERT(dsl_deadlist_is_open(dl));

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_tree(dl);
	mutex_exit(&dl->dl_lock);
	for (dle = avl_first(&dl->dl_tree); dle != NULL;
	    dle = AVL_NEXT(&dl->dl_tree, dle)) {
		if (func(args, dle) != 0)
			break;
	}
}