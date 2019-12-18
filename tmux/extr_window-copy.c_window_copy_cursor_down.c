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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct screen {int /*<<< orphan*/ * sel; } ;
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ cx; scalar_t__ lastcx; scalar_t__ lastsx; scalar_t__ lineflag; scalar_t__ endsely; int /*<<< orphan*/  backing; int /*<<< orphan*/  rectflag; struct screen screen; } ;

/* Variables and functions */
 scalar_t__ LINE_SEL_LEFT_RIGHT ; 
 scalar_t__ LINE_SEL_RIGHT_LEFT ; 
 scalar_t__ screen_hsize (int /*<<< orphan*/ ) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  window_copy_cursor_end_of_line (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_cursor_start_of_line (struct window_mode_entry*) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_other_end (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  window_copy_scroll_up (struct window_mode_entry*,int) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_cursor_down(struct window_mode_entry *wme, int scroll_only)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	u_int				 ox, oy, px, py;

	oy = screen_hsize(data->backing) + data->cy - data->oy;
	ox = window_copy_find_length(wme, oy);
	if (data->cx != ox) {
		data->lastcx = data->cx;
		data->lastsx = ox;
	}

	if (data->lineflag == LINE_SEL_RIGHT_LEFT && oy == data->endsely)
		window_copy_other_end(wme);

	if (scroll_only || data->cy == screen_size_y(s) - 1) {
		data->cx = data->lastcx;
		window_copy_scroll_up(wme, 1);
		if (scroll_only && data->cy > 0)
			window_copy_redraw_lines(wme, data->cy - 1, 2);
	} else {
		window_copy_update_cursor(wme, data->lastcx, data->cy + 1);
		if (window_copy_update_selection(wme, 1))
			window_copy_redraw_lines(wme, data->cy - 1, 2);
	}

	if (data->screen.sel == NULL || !data->rectflag) {
		py = screen_hsize(data->backing) + data->cy - data->oy;
		px = window_copy_find_length(wme, py);
		if ((data->cx >= data->lastsx && data->cx != px) ||
		    data->cx > px)
			window_copy_cursor_end_of_line(wme);
	}

	if (data->lineflag == LINE_SEL_LEFT_RIGHT)
		window_copy_cursor_end_of_line(wme);
	else if (data->lineflag == LINE_SEL_RIGHT_LEFT)
		window_copy_cursor_start_of_line(wme);
}