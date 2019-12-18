#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int band; int /*<<< orphan*/  stop; int /*<<< orphan*/  num; int /*<<< orphan*/  bit; int /*<<< orphan*/  pix; int /*<<< orphan*/  cookie; int /*<<< orphan*/  tbounds; int /*<<< orphan*/  ctm; int /*<<< orphan*/  list; int /*<<< orphan*/  ctx; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ worker_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_THREADS (char*) ; 
 int band_height ; 
 int /*<<< orphan*/  drawband (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_wait_semaphore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void worker_thread(void *arg)
{
	worker_t *me = (worker_t *)arg;

	do
	{
		DEBUG_THREADS(("Worker %d waiting\n", me->num));
		mu_wait_semaphore(&me->start);
		DEBUG_THREADS(("Worker %d woken for band %d\n", me->num, me->band));
		if (me->band >= 0)
			drawband(me->ctx, NULL, me->list, me->ctm, me->tbounds, &me->cookie, me->band * band_height, me->pix, &me->bit);
		DEBUG_THREADS(("Worker %d completed band %d\n", me->num, me->band));
		mu_trigger_semaphore(&me->stop);
	}
	while (me->band >= 0);
}