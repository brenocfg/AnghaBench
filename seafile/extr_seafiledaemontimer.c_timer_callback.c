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
struct SeafTimer {int in_callback; int (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  tv; int /*<<< orphan*/  event; int /*<<< orphan*/  user_data; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_timer_free (struct SeafTimer**) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
timer_callback (evutil_socket_t fd, short event, void *vtimer)
{
    int more;
    struct SeafTimer *timer = vtimer;

    timer->in_callback = 1;
    more = (*timer->func) (timer->user_data);
    timer->in_callback = 0;

    if (more)
        evtimer_add (timer->event, &timer->tv);
    else
        seaf_timer_free (&timer);
}