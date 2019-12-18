#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct session {int dummy; } ;
struct msg_stdin_data {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int len; int type; } ;
struct imsg {char* data; TYPE_1__ hdr; } ;
struct TYPE_6__ {int fd; } ;
struct client {int flags; int stdin_closed; int /*<<< orphan*/  activity_time; TYPE_2__ tty; struct session* session; int /*<<< orphan*/  peer; int /*<<< orphan*/  stdin_callback_data; int /*<<< orphan*/  (* stdin_callback ) (struct client*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  stdin_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int CLIENT_CONTROL ; 
 int CLIENT_DEAD ; 
 int CLIENT_SUSPENDED ; 
 int IMSG_HEADER_SIZE ; 
#define  MSG_COMMAND 142 
 int /*<<< orphan*/  MSG_EXITED ; 
#define  MSG_EXITING 141 
#define  MSG_IDENTIFY_CLIENTPID 140 
#define  MSG_IDENTIFY_CWD 139 
#define  MSG_IDENTIFY_DONE 138 
#define  MSG_IDENTIFY_ENVIRON 137 
#define  MSG_IDENTIFY_FLAGS 136 
#define  MSG_IDENTIFY_STDIN 135 
#define  MSG_IDENTIFY_TERM 134 
#define  MSG_IDENTIFY_TTYNAME 133 
#define  MSG_RESIZE 132 
#define  MSG_SHELL 131 
#define  MSG_STDIN 130 
#define  MSG_UNLOCK 129 
#define  MSG_WAKEUP 128 
 int /*<<< orphan*/  evbuffer_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct msg_stdin_data*,char const*,int) ; 
 int /*<<< orphan*/  notify_client (char*,struct client*) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_client_clear_overlay (struct client*) ; 
 int /*<<< orphan*/  server_client_dispatch_command (struct client*,struct imsg*) ; 
 int /*<<< orphan*/  server_client_dispatch_identify (struct client*,struct imsg*) ; 
 int /*<<< orphan*/  server_client_dispatch_shell (struct client*) ; 
 int /*<<< orphan*/  server_client_lost (struct client*) ; 
 int /*<<< orphan*/  server_client_update_latest (struct client*) ; 
 int /*<<< orphan*/  server_redraw_client (struct client*) ; 
 int /*<<< orphan*/  session_update_activity (struct session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_close (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_resize (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_start_tty (TYPE_2__*) ; 

__attribute__((used)) static void
server_client_dispatch(struct imsg *imsg, void *arg)
{
	struct client		*c = arg;
	struct msg_stdin_data	 stdindata;
	const char		*data;
	ssize_t			 datalen;
	struct session		*s;

	if (c->flags & CLIENT_DEAD)
		return;

	if (imsg == NULL) {
		server_client_lost(c);
		return;
	}

	data = imsg->data;
	datalen = imsg->hdr.len - IMSG_HEADER_SIZE;

	switch (imsg->hdr.type) {
	case MSG_IDENTIFY_FLAGS:
	case MSG_IDENTIFY_TERM:
	case MSG_IDENTIFY_TTYNAME:
	case MSG_IDENTIFY_CWD:
	case MSG_IDENTIFY_STDIN:
	case MSG_IDENTIFY_ENVIRON:
	case MSG_IDENTIFY_CLIENTPID:
	case MSG_IDENTIFY_DONE:
		server_client_dispatch_identify(c, imsg);
		break;
	case MSG_COMMAND:
		server_client_dispatch_command(c, imsg);
		break;
	case MSG_STDIN:
		if (datalen != sizeof stdindata)
			fatalx("bad MSG_STDIN size");
		memcpy(&stdindata, data, sizeof stdindata);

		if (c->stdin_callback == NULL)
			break;
		if (stdindata.size <= 0)
			c->stdin_closed = 1;
		else {
			evbuffer_add(c->stdin_data, stdindata.data,
			    stdindata.size);
		}
		c->stdin_callback(c, c->stdin_closed, c->stdin_callback_data);
		break;
	case MSG_RESIZE:
		if (datalen != 0)
			fatalx("bad MSG_RESIZE size");

		if (c->flags & CLIENT_CONTROL)
			break;
		server_client_update_latest(c);
		server_client_clear_overlay(c);
		tty_resize(&c->tty);
		recalculate_sizes();
		server_redraw_client(c);
		if (c->session != NULL)
			notify_client("client-resized", c);
		break;
	case MSG_EXITING:
		if (datalen != 0)
			fatalx("bad MSG_EXITING size");

		c->session = NULL;
		tty_close(&c->tty);
		proc_send(c->peer, MSG_EXITED, -1, NULL, 0);
		break;
	case MSG_WAKEUP:
	case MSG_UNLOCK:
		if (datalen != 0)
			fatalx("bad MSG_WAKEUP size");

		if (!(c->flags & CLIENT_SUSPENDED))
			break;
		c->flags &= ~CLIENT_SUSPENDED;

		if (c->tty.fd == -1) /* exited in the meantime */
			break;
		s = c->session;

		if (gettimeofday(&c->activity_time, NULL) != 0)
			fatal("gettimeofday failed");

		tty_start_tty(&c->tty);
		server_redraw_client(c);
		recalculate_sizes();

		if (s != NULL)
			session_update_activity(s, &c->activity_time);
		break;
	case MSG_SHELL:
		if (datalen != 0)
			fatalx("bad MSG_SHELL size");

		server_client_dispatch_shell(c);
		break;
	}
}