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
struct timer_queue {scalar_t__ event; int /*<<< orphan*/  timers; scalar_t__ quit; } ;
struct queue_timer {scalar_t__ runcount; int destroy; scalar_t__ event; int /*<<< orphan*/  entry; struct timer_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  NtSetEvent (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct queue_timer*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_remove_timer(struct queue_timer *t)
{
    /* We MUST hold the queue cs while calling this function.  This ensures
       that we cannot queue another callback for this timer.  The runcount
       being zero makes sure we don't have any already queued.  */
    struct timer_queue *q = t->q;

    assert(t->runcount == 0);
    assert(t->destroy);

    list_remove(&t->entry);
    if (t->event)
        NtSetEvent(t->event, NULL);
    RtlFreeHeap(RtlGetProcessHeap(), 0, t);

    if (q->quit && list_empty(&q->timers))
        NtSetEvent(q->event, NULL);
}