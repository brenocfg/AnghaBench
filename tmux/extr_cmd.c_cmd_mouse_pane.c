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
struct window_pane {int dummy; } ;
struct session {int dummy; } ;
struct mouse_event {int /*<<< orphan*/  wp; } ;

/* Variables and functions */
 struct winlink* cmd_mouse_window (struct mouse_event*,struct session**) ; 
 int /*<<< orphan*/  window_has_pane (int /*<<< orphan*/ ,struct window_pane*) ; 
 struct window_pane* window_pane_find_by_id (int /*<<< orphan*/ ) ; 

struct window_pane *
cmd_mouse_pane(struct mouse_event *m, struct session **sp,
    struct winlink **wlp)
{
	struct winlink		*wl;
	struct window_pane     	*wp;

	if ((wl = cmd_mouse_window(m, sp)) == NULL)
		return (NULL);
	if ((wp = window_pane_find_by_id(m->wp)) == NULL)
		return (NULL);
	if (!window_has_pane(wl->window, wp))
		return (NULL);

	if (wlp != NULL)
		*wlp = wl;
	return (wp);
}