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
struct TYPE_4__ {int ml_num_sublists; TYPE_2__* ml_sublists; } ;
typedef  TYPE_1__ multilist_t ;
struct TYPE_5__ {int /*<<< orphan*/  mls_lock; int /*<<< orphan*/  mls_list; } ;
typedef  TYPE_2__ multilist_sublist_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

int
multilist_is_empty(multilist_t *ml)
{
	for (int i = 0; i < ml->ml_num_sublists; i++) {
		multilist_sublist_t *mls = &ml->ml_sublists[i];
		/* See comment in multilist_insert(). */
		boolean_t need_lock = !MUTEX_HELD(&mls->mls_lock);

		if (need_lock)
			mutex_enter(&mls->mls_lock);

		if (!list_is_empty(&mls->mls_list)) {
			if (need_lock)
				mutex_exit(&mls->mls_lock);

			return (FALSE);
		}

		if (need_lock)
			mutex_exit(&mls->mls_lock);
	}

	return (TRUE);
}