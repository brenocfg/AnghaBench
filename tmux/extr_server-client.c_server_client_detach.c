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
struct session {int /*<<< orphan*/  name; } ;
struct client {int flags; int /*<<< orphan*/  peer; struct session* session; } ;
typedef  enum msgtype { ____Placeholder_msgtype } msgtype ;

/* Variables and functions */
 int CLIENT_DETACHING ; 
 int /*<<< orphan*/  notify_client (char*,struct client*) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void
server_client_detach(struct client *c, enum msgtype msgtype)
{
	struct session	*s = c->session;

	if (s == NULL || (c->flags & CLIENT_DETACHING))
		return;

	c->flags |= CLIENT_DETACHING;
	notify_client("client-detached", c);
	proc_send(c->peer, msgtype, -1, s->name, strlen(s->name) + 1);
}