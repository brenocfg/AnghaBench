#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  event; int /*<<< orphan*/  in_callback; } ;
typedef  TYPE_1__ SeafTimer ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_return_if_fail (TYPE_1__**) ; 

void
seaf_timer_free (SeafTimer **ptimer)
{
    SeafTimer *timer;

    /* zero out the argument passed in */
    g_return_if_fail (ptimer);

    timer = *ptimer;
    *ptimer = NULL;

    /* destroy the timer directly or via the command queue */
    if (timer && !timer->in_callback)
    {
        event_del (timer->event);
        event_free (timer->event);
        g_free (timer);
    }
}