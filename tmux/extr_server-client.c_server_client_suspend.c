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
struct session {int dummy; } ;
struct client {int flags; int /*<<< orphan*/  peer; int /*<<< orphan*/  tty; struct session* session; } ;

/* Variables and functions */
 int CLIENT_DETACHING ; 
 int CLIENT_SUSPENDED ; 
 int /*<<< orphan*/  MSG_SUSPEND ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_stop_tty (int /*<<< orphan*/ *) ; 

void
server_client_suspend(struct client *c)
{
	struct session	*s = c->session;

	if (s == NULL || (c->flags & CLIENT_DETACHING))
		return;

	tty_stop_tty(&c->tty);
	c->flags |= CLIENT_SUSPENDED;
	proc_send(c->peer, MSG_SUSPEND, -1, NULL, 0);
}