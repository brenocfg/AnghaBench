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
typedef  scalar_t__ u_int ;
struct window_pane {int /*<<< orphan*/  modes; } ;
struct window_mode_entry {struct window_copy_mode_data* data; int /*<<< orphan*/ * mode; } ;
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; int /*<<< orphan*/  dragtimer; int /*<<< orphan*/  screen; } ;
struct timeval {int /*<<< orphan*/  tv_usec; } ;
struct mouse_event {int dummy; } ;
struct client {int dummy; } ;

/* Variables and functions */
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINDOW_COPY_DRAG_REPEAT_TIME ; 
 scalar_t__ cmd_mouse_at (struct window_pane*,struct mouse_event*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct window_pane* cmd_mouse_pane (struct mouse_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int screen_size_y (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_copy_cursor_down (struct window_mode_entry*,int) ; 
 int /*<<< orphan*/  window_copy_cursor_up (struct window_mode_entry*,int) ; 
 int /*<<< orphan*/  window_copy_mode ; 
 int /*<<< orphan*/  window_copy_redraw_selection (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 
 int /*<<< orphan*/  window_view_mode ; 

__attribute__((used)) static void
window_copy_drag_update(struct client *c, struct mouse_event *m)
{
	struct window_pane		*wp;
	struct window_mode_entry	*wme;
	struct window_copy_mode_data	*data;
	u_int				 x, y, old_cx, old_cy;
	struct timeval			 tv = {
		.tv_usec = WINDOW_COPY_DRAG_REPEAT_TIME
	};

	if (c == NULL)
		return;

	wp = cmd_mouse_pane(m, NULL, NULL);
	if (wp == NULL)
		return;
	wme = TAILQ_FIRST(&wp->modes);
	if (wme == NULL)
		return;
	if (wme->mode != &window_copy_mode && wme->mode != &window_view_mode)
		return;

	data = wme->data;
	evtimer_del(&data->dragtimer);

	if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
		return;
	old_cx = data->cx;
	old_cy = data->cy;

	window_copy_update_cursor(wme, x, y);
	if (window_copy_update_selection(wme, 1))
		window_copy_redraw_selection(wme, old_cy);
	if (old_cy != data->cy || old_cx == data->cx) {
		if (y == 0) {
			evtimer_add(&data->dragtimer, &tv);
			window_copy_cursor_up(wme, 1);
		} else if (y == screen_size_y(&data->screen) - 1) {
			evtimer_add(&data->dragtimer, &tv);
			window_copy_cursor_down(wme, 1);
		}
	}
}