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
struct TYPE_2__ {scalar_t__ band_start; int /*<<< orphan*/  stop; int /*<<< orphan*/  status; int /*<<< orphan*/  num; int /*<<< orphan*/  bit; int /*<<< orphan*/  pix; int /*<<< orphan*/  cookie; int /*<<< orphan*/  tbounds; int /*<<< orphan*/  ctm; int /*<<< orphan*/  list; int /*<<< orphan*/  ctx; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ worker_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_THREADS (char*) ; 
 int /*<<< orphan*/  RENDER_OK ; 
 int /*<<< orphan*/  drawband (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mu_wait_semaphore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void worker_thread(void *arg)
{
	worker_t *me = (worker_t *)arg;

	do
	{
		DEBUG_THREADS(("Worker %d waiting\n", me->num));
		mu_wait_semaphore(&me->start);
		DEBUG_THREADS(("Worker %d woken for band_start %d\n", me->num, me->band_start));
		me->status = RENDER_OK;
		if (me->band_start >= 0)
			me->status = drawband(me->ctx, NULL, me->list, me->ctm, me->tbounds, &me->cookie, me->band_start, me->pix, &me->bit);
		DEBUG_THREADS(("Worker %d completed band_start %d (status=%d)\n", me->num, me->band_start, me->status));
		mu_trigger_semaphore(&me->stop);
	}
	while (me->band_start >= 0);
}