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
struct TYPE_3__ {int /*<<< orphan*/  cv_event; int /*<<< orphan*/ * cv_mutex; int /*<<< orphan*/  cv_refs; int /*<<< orphan*/  cv_waiters; } ;
typedef  TYPE_1__ kcondvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cv_destroy_wakeup(kcondvar_t *cvp)
{
	if (!atomic_read(&cvp->cv_waiters) && !atomic_read(&cvp->cv_refs)) {
		ASSERT(cvp->cv_mutex == NULL);
		ASSERT(!waitqueue_active(&cvp->cv_event));
		return (1);
	}

	return (0);
}