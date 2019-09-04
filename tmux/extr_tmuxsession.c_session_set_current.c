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
struct winlink {int /*<<< orphan*/  window; } ;
struct session {struct winlink* curw; int /*<<< orphan*/  lastw; } ;

/* Variables and functions */
 int /*<<< orphan*/  notify_session (char*,struct session*) ; 
 int /*<<< orphan*/  tty_update_window_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_update_activity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winlink_clear_flags (struct winlink*) ; 
 int /*<<< orphan*/  winlink_stack_push (int /*<<< orphan*/ *,struct winlink*) ; 
 int /*<<< orphan*/  winlink_stack_remove (int /*<<< orphan*/ *,struct winlink*) ; 

int
session_set_current(struct session *s, struct winlink *wl)
{
	if (wl == NULL)
		return (-1);
	if (wl == s->curw)
		return (1);

	winlink_stack_remove(&s->lastw, wl);
	winlink_stack_push(&s->lastw, s->curw);
	s->curw = wl;
	winlink_clear_flags(wl);
	window_update_activity(wl->window);
	tty_update_window_offset(wl->window);
	notify_session("session-window-changed", s);
	return (0);
}