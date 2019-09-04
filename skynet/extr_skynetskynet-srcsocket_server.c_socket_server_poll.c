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
struct socket_server {int checkctrl; scalar_t__ event_index; scalar_t__ event_n; struct event* ev; int /*<<< orphan*/  event_fd; } ;
struct socket_message {char* data; } ;
struct socket_lock {int dummy; } ;
struct socket {int type; int /*<<< orphan*/  fd; int /*<<< orphan*/  protocol; } ;
struct event {int read; int /*<<< orphan*/  eof; int /*<<< orphan*/  error; int /*<<< orphan*/  write; struct socket* s; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MAX_EVENT ; 
 int /*<<< orphan*/  PROTOCOL_TCP ; 
 int SOCKET_ACCEPT ; 
 int SOCKET_CLOSE ; 
 int SOCKET_ERR ; 
#define  SOCKET_TYPE_CONNECTING 130 
#define  SOCKET_TYPE_INVALID 129 
#define  SOCKET_TYPE_LISTEN 128 
 int SOCKET_UDP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  clear_closed_event (struct socket_server*,struct socket_message*,int) ; 
 int ctrl_cmd (struct socket_server*,struct socket_message*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  force_close (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int forward_message_tcp (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int forward_message_udp (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ has_cmd (struct socket_server*) ; 
 int report_accept (struct socket_server*,struct socket*,struct socket_message*) ; 
 int report_connect (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int send_buffer (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  socket_lock_init (struct socket*,struct socket_lock*) ; 
 scalar_t__ sp_wait (int /*<<< orphan*/ ,struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int 
socket_server_poll(struct socket_server *ss, struct socket_message * result, int * more) {
	for (;;) {
		if (ss->checkctrl) {
			if (has_cmd(ss)) {
				int type = ctrl_cmd(ss, result);
				if (type != -1) {
					clear_closed_event(ss, result, type);
					return type;
				} else
					continue;
			} else {
				ss->checkctrl = 0;
			}
		}
		if (ss->event_index == ss->event_n) {
			ss->event_n = sp_wait(ss->event_fd, ss->ev, MAX_EVENT);
			ss->checkctrl = 1;
			if (more) {
				*more = 0;
			}
			ss->event_index = 0;
			if (ss->event_n <= 0) {
				ss->event_n = 0;
				if (errno == EINTR) {
					continue;
				}
				return -1;
			}
		}
		struct event *e = &ss->ev[ss->event_index++];
		struct socket *s = e->s;
		if (s == NULL) {
			// dispatch pipe message at beginning
			continue;
		}
		struct socket_lock l;
		socket_lock_init(s, &l);
		switch (s->type) {
		case SOCKET_TYPE_CONNECTING:
			return report_connect(ss, s, &l, result);
		case SOCKET_TYPE_LISTEN: {
			int ok = report_accept(ss, s, result);
			if (ok > 0) {
				return SOCKET_ACCEPT;
			} if (ok < 0 ) {
				return SOCKET_ERR;
			}
			// when ok == 0, retry
			break;
		}
		case SOCKET_TYPE_INVALID:
			fprintf(stderr, "socket-server: invalid socket\n");
			break;
		default:
			if (e->read) {
				int type;
				if (s->protocol == PROTOCOL_TCP) {
					type = forward_message_tcp(ss, s, &l, result);
				} else {
					type = forward_message_udp(ss, s, &l, result);
					if (type == SOCKET_UDP) {
						// try read again
						--ss->event_index;
						return SOCKET_UDP;
					}
				}
				if (e->write && type != SOCKET_CLOSE && type != SOCKET_ERR) {
					// Try to dispatch write message next step if write flag set.
					e->read = false;
					--ss->event_index;
				}
				if (type == -1)
					break;				
				return type;
			}
			if (e->write) {
				int type = send_buffer(ss, s, &l, result);
				if (type == -1)
					break;
				return type;
			}
			if (e->error) {
				// close when error
				int error;
				socklen_t len = sizeof(error);  
				int code = getsockopt(s->fd, SOL_SOCKET, SO_ERROR, &error, &len);  
				const char * err = NULL;
				if (code < 0) {
					err = strerror(errno);
				} else if (error != 0) {
					err = strerror(error);
				} else {
					err = "Unknown error";
				}
				force_close(ss, s, &l, result);
				result->data = (char *)err;
				return SOCKET_ERR;
			}
			if(e->eof) {
				force_close(ss, s, &l, result);
				return SOCKET_CLOSE;
			}
			break;
		}
	}
}