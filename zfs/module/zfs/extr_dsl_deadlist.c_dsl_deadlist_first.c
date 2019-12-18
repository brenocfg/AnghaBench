#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_tree; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
typedef  int /*<<< orphan*/  dsl_deadlist_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

dsl_deadlist_entry_t *
dsl_deadlist_first(dsl_deadlist_t *dl)
{
	dsl_deadlist_entry_t *dle;

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_tree(dl);
	dle = avl_first(&dl->dl_tree);
	mutex_exit(&dl->dl_lock);

	return (dle);
}