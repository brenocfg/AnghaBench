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
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ cx; scalar_t__ lastcx; scalar_t__ lastsx; struct screen* backing; int /*<<< orphan*/  rectflag; struct screen screen; } ;

/* Variables and functions */
 scalar_t__ screen_hsize (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  window_copy_cursor_end_of_line (struct window_mode_entry*) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_redraw_screen (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static int
window_copy_pagedown(struct window_mode_entry *wme, int half_page,
    int scroll_exit)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	u_int				 n, ox, oy, px, py;

	oy = screen_hsize(data->backing) + data->cy - data->oy;
	ox = window_copy_find_length(wme, oy);

	if (data->cx != ox) {
		data->lastcx = data->cx;
		data->lastsx = ox;
	}
	data->cx = data->lastcx;

	n = 1;
	if (screen_size_y(s) > 2) {
		if (half_page)
			n = screen_size_y(s) / 2;
		else
			n = screen_size_y(s) - 2;
	}

	if (data->oy < n) {
		data->oy = 0;
		if (data->cy + (n - data->oy) >= screen_size_y(data->backing))
			data->cy = screen_size_y(data->backing) - 1;
		else
			data->cy += n - data->oy;
	} else
		data->oy -= n;

	if (data->screen.sel == NULL || !data->rectflag) {
		py = screen_hsize(data->backing) + data->cy - data->oy;
		px = window_copy_find_length(wme, py);
		if ((data->cx >= data->lastsx && data->cx != px) ||
		    data->cx > px)
			window_copy_cursor_end_of_line(wme);
	}

	if (scroll_exit && data->oy == 0)
		return (1);
	window_copy_update_selection(wme, 1);
	window_copy_redraw_screen(wme);
	return (0);
}