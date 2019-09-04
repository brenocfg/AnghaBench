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
struct window_copy_mode_data {scalar_t__ cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
window_copy_redraw_selection(struct window_mode_entry *wme, u_int old_y)
{
	struct window_copy_mode_data	*data = wme->data;
	u_int				 new_y, start, end;

	new_y = data->cy;
	if (old_y <= new_y) {
		start = old_y;
		end = new_y;
	} else {
		start = new_y;
		end = old_y;
	}
	window_copy_redraw_lines(wme, start, end - start + 1);
}