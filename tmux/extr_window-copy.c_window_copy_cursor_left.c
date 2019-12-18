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
typedef  scalar_t__ u_int ;
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ cx; TYPE_1__* backing; } ;
struct grid_cell {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  grid; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int /*<<< orphan*/  grid_get_cell (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct grid_cell*) ; 
 scalar_t__ screen_hsize (TYPE_1__*) ; 
 int /*<<< orphan*/  window_copy_cursor_end_of_line (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_cursor_up (struct window_mode_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_cursor_left(struct window_mode_entry *wme)
{
	struct window_copy_mode_data	*data = wme->data;
	u_int				 py, cx;
	struct grid_cell		 gc;

	py = screen_hsize(data->backing) + data->cy - data->oy;
	cx = data->cx;
	while (cx > 0) {
		grid_get_cell(data->backing->grid, cx, py, &gc);
		if (~gc.flags & GRID_FLAG_PADDING)
			break;
		cx--;
	}
	if (cx == 0 && py > 0) {
		window_copy_cursor_up(wme, 0);
		window_copy_cursor_end_of_line(wme);
	} else if (cx > 0) {
		window_copy_update_cursor(wme, cx - 1, data->cy);
		if (window_copy_update_selection(wme, 1))
			window_copy_redraw_lines(wme, data->cy, 1);
	}
}