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
typedef  int u_int ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_2__ {int flags; } ;
struct client {TYPE_1__ tty; int /*<<< orphan*/  flags; int /*<<< orphan*/  identify_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_IDENTIFY ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct client*) ; 
 int /*<<< orphan*/  server_client_callback_identify ; 
 int /*<<< orphan*/  server_redraw_client (struct client*) ; 

void
server_client_set_identify(struct client *c, u_int delay)
{
	struct timeval	tv;

	tv.tv_sec = delay / 1000;
	tv.tv_usec = (delay % 1000) * 1000L;

	if (event_initialized(&c->identify_timer))
		evtimer_del(&c->identify_timer);
	evtimer_set(&c->identify_timer, server_client_callback_identify, c);
	if (delay != 0)
		evtimer_add(&c->identify_timer, &tv);

	c->flags |= CLIENT_IDENTIFY;
	c->tty.flags |= (TTY_FREEZE|TTY_NOCURSOR);
	server_redraw_client(c);
}