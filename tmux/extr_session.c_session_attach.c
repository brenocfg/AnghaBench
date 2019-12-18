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
struct winlink {struct session* session; } ;
struct window {int dummy; } ;
struct session {int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  notify_session_window (char*,struct session*,struct window*) ; 
 int /*<<< orphan*/  session_group_synchronize_from (struct session*) ; 
 struct winlink* winlink_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  winlink_set_window (struct winlink*,struct window*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 

struct winlink *
session_attach(struct session *s, struct window *w, int idx, char **cause)
{
	struct winlink	*wl;

	if ((wl = winlink_add(&s->windows, idx)) == NULL) {
		xasprintf(cause, "index in use: %d", idx);
		return (NULL);
	}
	wl->session = s;
	winlink_set_window(wl, w);
	notify_session_window("window-linked", s, w);

	session_group_synchronize_from(s);
	return (wl);
}