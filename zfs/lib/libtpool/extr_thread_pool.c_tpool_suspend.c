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
struct TYPE_3__ {int tp_flags; int /*<<< orphan*/  tp_mutex; } ;
typedef  TYPE_1__ tpool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int TP_SUSPEND ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
tpool_suspend(tpool_t *tpool)
{
	ASSERT(!(tpool->tp_flags & (TP_DESTROY | TP_ABANDON)));

	pthread_mutex_lock(&tpool->tp_mutex);
	tpool->tp_flags |= TP_SUSPEND;
	pthread_mutex_unlock(&tpool->tp_mutex);
}