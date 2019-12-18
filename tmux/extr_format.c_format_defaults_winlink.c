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
typedef  int u_int ;
struct winlink {int idx; int flags; struct window* window; struct session* session; } ;
struct window {int dummy; } ;
struct session {int /*<<< orphan*/  lastw; int /*<<< orphan*/  windows; struct winlink* curw; } ;
struct format_tree {struct winlink* wl; struct window* w; struct client* c; } ;
struct client {int /*<<< orphan*/  tty; } ;
struct TYPE_2__ {struct winlink* wl; } ;

/* Variables and functions */
 struct winlink* RB_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct winlink* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct winlink* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int WINLINK_ACTIVITY ; 
 int WINLINK_BELL ; 
 int WINLINK_SILENCE ; 
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,...) ; 
 int /*<<< orphan*/  format_add_cb (struct format_tree*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_cb_window_stack_index ; 
 int /*<<< orphan*/  format_defaults_window (struct format_tree*,struct window*) ; 
 TYPE_1__ marked_pane ; 
 scalar_t__ server_check_marked () ; 
 int session_is_linked (struct session*,struct window*) ; 
 int tty_window_offset (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int window_printable_flags (struct winlink*) ; 
 int /*<<< orphan*/  winlinks ; 

__attribute__((used)) static void
format_defaults_winlink(struct format_tree *ft, struct winlink *wl)
{
	struct client	*c = ft->c;
	struct session	*s = wl->session;
	struct window	*w = wl->window;
	int		 flag;
	u_int		 ox, oy, sx, sy;

	if (ft->w == NULL)
		ft->w = wl->window;
	ft->wl = wl;

	format_defaults_window(ft, w);

	if (c != NULL) {
		flag = tty_window_offset(&c->tty, &ox, &oy, &sx, &sy);
		format_add(ft, "window_bigger", "%d", flag);
		if (flag) {
			format_add(ft, "window_offset_x", "%u", ox);
			format_add(ft, "window_offset_y", "%u", oy);
		}
	}

	format_add(ft, "window_index", "%d", wl->idx);
	format_add_cb(ft, "window_stack_index", format_cb_window_stack_index);
	format_add(ft, "window_flags", "%s", window_printable_flags(wl));
	format_add(ft, "window_active", "%d", wl == s->curw);

	format_add(ft, "window_start_flag", "%d",
	    !!(wl == RB_MIN(winlinks, &s->windows)));
	format_add(ft, "window_end_flag", "%d",
	    !!(wl == RB_MAX(winlinks, &s->windows)));

	if (server_check_marked() && marked_pane.wl == wl)
	    format_add(ft, "window_marked_flag", "1");
	else
	    format_add(ft, "window_marked_flag", "0");

	format_add(ft, "window_bell_flag", "%d",
	    !!(wl->flags & WINLINK_BELL));
	format_add(ft, "window_activity_flag", "%d",
	    !!(wl->flags & WINLINK_ACTIVITY));
	format_add(ft, "window_silence_flag", "%d",
	    !!(wl->flags & WINLINK_SILENCE));
	format_add(ft, "window_last_flag", "%d",
	    !!(wl == TAILQ_FIRST(&s->lastw)));
	format_add(ft, "window_linked", "%d", session_is_linked(s, wl->window));
}