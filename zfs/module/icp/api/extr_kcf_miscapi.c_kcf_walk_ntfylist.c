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
typedef  int uint32_t ;
struct TYPE_3__ {int kn_event_mask; int /*<<< orphan*/  kn_lock; int /*<<< orphan*/  kn_cv; int /*<<< orphan*/  kn_state; int /*<<< orphan*/  (* kn_func ) (int,void*) ;struct TYPE_3__* kn_next; } ;
typedef  TYPE_1__ kcf_ntfy_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  NTFY_RUNNING ; 
 int /*<<< orphan*/  NTFY_WAITING ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ntfy_list_head ; 
 int /*<<< orphan*/  ntfy_list_lock ; 
 int /*<<< orphan*/  stub1 (int,void*) ; 

void
kcf_walk_ntfylist(uint32_t event, void *event_arg)
{
	kcf_ntfy_elem_t *nep;
	int nelem = 0;

	mutex_enter(&ntfy_list_lock);

	/*
	 * Count how many clients are on the notification list. We need
	 * this count to ensure that clients which joined the list after we
	 * have started this walk, are not wrongly notified.
	 */
	for (nep = ntfy_list_head; nep != NULL; nep = nep->kn_next)
		nelem++;

	for (nep = ntfy_list_head; (nep != NULL && nelem); nep = nep->kn_next) {
		nelem--;

		/*
		 * Check if this client is interested in the
		 * event.
		 */
		if (!(nep->kn_event_mask & event))
			continue;

		mutex_enter(&nep->kn_lock);
		nep->kn_state = NTFY_RUNNING;
		mutex_exit(&nep->kn_lock);
		mutex_exit(&ntfy_list_lock);

		/*
		 * We invoke the callback routine with no locks held. Another
		 * client could have joined the list meanwhile. This is fine
		 * as we maintain nelem as stated above. The NULL check in the
		 * for loop guards against shrinkage. Also, any callers of
		 * crypto_unnotify_events() at this point cv_wait till kn_state
		 * changes to NTFY_WAITING. Hence, nep is assured to be valid.
		 */
		(*nep->kn_func)(event, event_arg);

		mutex_enter(&nep->kn_lock);
		nep->kn_state = NTFY_WAITING;
		cv_broadcast(&nep->kn_cv);
		mutex_exit(&nep->kn_lock);

		mutex_enter(&ntfy_list_lock);
	}

	mutex_exit(&ntfy_list_lock);
}