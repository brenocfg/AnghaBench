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
struct session {int /*<<< orphan*/  options; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct client {TYPE_1__ status; struct session* session; } ;

/* Variables and functions */
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int,int /*<<< orphan*/ ,struct client*),struct client*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  status_timer_callback (int,int /*<<< orphan*/ ,struct client*) ; 

void
status_timer_start(struct client *c)
{
	struct session	*s = c->session;

	if (event_initialized(&c->status.timer))
		evtimer_del(&c->status.timer);
	else
		evtimer_set(&c->status.timer, status_timer_callback, c);

	if (s != NULL && options_get_number(s->options, "status"))
		status_timer_callback(-1, 0, c);
}