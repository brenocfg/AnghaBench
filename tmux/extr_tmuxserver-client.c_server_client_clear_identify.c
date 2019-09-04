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
struct window_pane {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct client {int flags; TYPE_1__ tty; int /*<<< orphan*/  (* identify_callback ) (struct client*,struct window_pane*) ;} ;

/* Variables and functions */
 int CLIENT_IDENTIFY ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 int /*<<< orphan*/  server_redraw_client (struct client*) ; 
 int /*<<< orphan*/  stub1 (struct client*,struct window_pane*) ; 

__attribute__((used)) static void
server_client_clear_identify(struct client *c, struct window_pane *wp)
{
	if (~c->flags & CLIENT_IDENTIFY)
		return;
	c->flags &= ~CLIENT_IDENTIFY;

	if (c->identify_callback != NULL)
		c->identify_callback(c, wp);

	c->tty.flags &= ~(TTY_FREEZE|TTY_NOCURSOR);
	server_redraw_client(c);
}