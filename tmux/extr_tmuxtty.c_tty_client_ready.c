#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct window_pane {scalar_t__ window; int /*<<< orphan*/ * layout_cell; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/ * term; } ;
struct client {int flags; TYPE_2__* session; TYPE_1__ tty; } ;
struct TYPE_6__ {scalar_t__ window; } ;
struct TYPE_5__ {TYPE_3__* curw; } ;

/* Variables and functions */
 int CLIENT_REDRAWWINDOW ; 
 int CLIENT_SUSPENDED ; 
 int TTY_FREEZE ; 

__attribute__((used)) static int
tty_client_ready(struct client *c, struct window_pane *wp)
{
	if (c->session == NULL || c->tty.term == NULL)
		return (0);
	if (c->flags & (CLIENT_REDRAWWINDOW|CLIENT_SUSPENDED))
		return (0);
	if (c->tty.flags & TTY_FREEZE)
		return (0);
	if (c->session->curw->window != wp->window)
		return (0);
	if (wp->layout_cell == NULL)
		return (0);
	return (1);
}