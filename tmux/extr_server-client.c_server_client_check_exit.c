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
struct client {int flags; int /*<<< orphan*/  retval; int /*<<< orphan*/  peer; int /*<<< orphan*/  stderr_data; int /*<<< orphan*/  stdout_data; int /*<<< orphan*/  stdin_data; } ;

/* Variables and functions */
 int CLIENT_ATTACHED ; 
 int CLIENT_EXIT ; 
 int CLIENT_EXITED ; 
 scalar_t__ EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_EXIT ; 
 int /*<<< orphan*/  notify_client (char*,struct client*) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
server_client_check_exit(struct client *c)
{
	if (~c->flags & CLIENT_EXIT)
		return;
	if (c->flags & CLIENT_EXITED)
		return;

	if (EVBUFFER_LENGTH(c->stdin_data) != 0)
		return;
	if (EVBUFFER_LENGTH(c->stdout_data) != 0)
		return;
	if (EVBUFFER_LENGTH(c->stderr_data) != 0)
		return;

	if (c->flags & CLIENT_ATTACHED)
		notify_client("client-detached", c);
	proc_send(c->peer, MSG_EXIT, -1, &c->retval, sizeof c->retval);
	c->flags |= CLIENT_EXITED;
}