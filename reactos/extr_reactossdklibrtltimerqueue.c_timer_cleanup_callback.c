#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_queue {int /*<<< orphan*/  cs; } ;
struct queue_timer {scalar_t__ runcount; scalar_t__ destroy; struct timer_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  RtlEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlLeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  queue_remove_timer (struct queue_timer*) ; 

__attribute__((used)) static void timer_cleanup_callback(struct queue_timer *t)
{
    struct timer_queue *q = t->q;
    RtlEnterCriticalSection(&q->cs);

    assert(0 < t->runcount);
    --t->runcount;

    if (t->destroy && t->runcount == 0)
        queue_remove_timer(t);

    RtlLeaveCriticalSection(&q->cs);
}