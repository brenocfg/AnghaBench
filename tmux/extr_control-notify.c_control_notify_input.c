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
typedef  size_t u_int ;
typedef  char u_char ;
struct window_pane {char const id; int /*<<< orphan*/  window; } ;
struct evbuffer {int dummy; } ;
struct client {int flags; TYPE_1__* session; } ;
struct TYPE_2__ {int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int CLIENT_CONTROL_NOOUTPUT ; 
 int /*<<< orphan*/  control_write_buffer (struct client*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,char const) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/ * winlink_find_by_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
control_notify_input(struct client *c, struct window_pane *wp,
    const u_char *buf, size_t len)
{
	struct evbuffer *message;
	u_int		 i;

	if (c->session == NULL)
	    return;

	if (c->flags & CLIENT_CONTROL_NOOUTPUT)
		return;

	/*
	 * Only write input if the window pane is linked to a window belonging
	 * to the client's session.
	 */
	if (winlink_find_by_window(&c->session->windows, wp->window) != NULL) {
		message = evbuffer_new();
		if (message == NULL)
			fatalx("out of memory");
		evbuffer_add_printf(message, "%%output %%%u ", wp->id);
		for (i = 0; i < len; i++) {
			if (buf[i] < ' ' || buf[i] == '\\')
			    evbuffer_add_printf(message, "\\%03o", buf[i]);
			else
			    evbuffer_add_printf(message, "%c", buf[i]);
		}
		control_write_buffer(c, message);
		evbuffer_free(message);
	}
}