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
struct TYPE_2__ {int flags; } ;
struct client {TYPE_1__ tty; int /*<<< orphan*/ * overlay_key; int /*<<< orphan*/ * overlay_draw; int /*<<< orphan*/  (* overlay_free ) (struct client*) ;int /*<<< orphan*/  overlay_timer; } ;

/* Variables and functions */
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_redraw_client (struct client*) ; 
 int /*<<< orphan*/  stub1 (struct client*) ; 

__attribute__((used)) static void
server_client_clear_overlay(struct client *c)
{
	if (c->overlay_draw == NULL)
		return;

	if (event_initialized(&c->overlay_timer))
		evtimer_del(&c->overlay_timer);

	if (c->overlay_free != NULL)
		c->overlay_free(c);

	c->overlay_draw = NULL;
	c->overlay_key = NULL;

	c->tty.flags &= ~(TTY_FREEZE|TTY_NOCURSOR);
	server_redraw_client(c);
}