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
struct TYPE_4__ {int tp_flags; int /*<<< orphan*/  tp_mutex; TYPE_2__* tp_active; } ;
typedef  TYPE_1__ tpool_t ;
struct TYPE_5__ {scalar_t__ tpa_tid; struct TYPE_5__* tpa_next; } ;
typedef  TYPE_2__ tpool_active_t ;
typedef  scalar_t__ pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 

int
tpool_member(tpool_t *tpool)
{
	pthread_t my_tid = pthread_self();
	tpool_active_t *activep;

	ASSERT(!(tpool->tp_flags & (TP_DESTROY | TP_ABANDON)));

	pthread_mutex_lock(&tpool->tp_mutex);
	for (activep = tpool->tp_active; activep; activep = activep->tpa_next) {
		if (activep->tpa_tid == my_tid) {
			pthread_mutex_unlock(&tpool->tp_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&tpool->tp_mutex);
	return (0);
}