#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sel; } ;
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ cx; TYPE_1__* backing; TYPE_2__ screen; scalar_t__ rectflag; } ;
struct grid_cell {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  grid; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int /*<<< orphan*/  grid_get_cell (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct grid_cell*) ; 
 scalar_t__ screen_hsize (TYPE_1__*) ; 
 scalar_t__ screen_size_x (TYPE_2__*) ; 
 scalar_t__ screen_size_y (TYPE_1__*) ; 
 int /*<<< orphan*/  window_copy_cursor_down (struct window_mode_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_cursor_start_of_line (struct window_mode_entry*) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_cursor_right(struct window_mode_entry *wme)
{
	struct window_copy_mode_data	*data = wme->data;
	u_int				 px, py, yy, cx, cy;
	struct grid_cell		 gc;

	py = screen_hsize(data->backing) + data->cy - data->oy;
	yy = screen_hsize(data->backing) + screen_size_y(data->backing) - 1;
	if (data->screen.sel != NULL && data->rectflag)
		px = screen_size_x(&data->screen);
	else
		px = window_copy_find_length(wme, py);

	if (data->cx >= px && py < yy) {
		window_copy_cursor_start_of_line(wme);
		window_copy_cursor_down(wme, 0);
	} else if (data->cx < px) {
		cx = data->cx + 1;
		cy = screen_hsize(data->backing) + data->cy - data->oy;
		while (cx < px) {
			grid_get_cell(data->backing->grid, cx, cy, &gc);
			if (~gc.flags & GRID_FLAG_PADDING)
				break;
			cx++;
		}
		window_copy_update_cursor(wme, cx, data->cy);
		if (window_copy_update_selection(wme, 1))
			window_copy_redraw_lines(wme, data->cy, 1);
	}
}