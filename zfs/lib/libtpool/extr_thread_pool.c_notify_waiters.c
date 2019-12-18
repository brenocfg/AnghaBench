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
struct TYPE_3__ {int /*<<< orphan*/  tp_waitcv; int /*<<< orphan*/  tp_flags; int /*<<< orphan*/ * tp_active; int /*<<< orphan*/ * tp_head; } ;
typedef  TYPE_1__ tpool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TP_WAIT ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
notify_waiters(tpool_t *tpool)
{
	if (tpool->tp_head == NULL && tpool->tp_active == NULL) {
		tpool->tp_flags &= ~TP_WAIT;
		(void) pthread_cond_broadcast(&tpool->tp_waitcv);
	}
}