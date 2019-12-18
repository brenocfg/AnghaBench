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
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; scalar_t__ oy; struct screen* backing; } ;
struct screen {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_hsize (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  window_copy_cursor_down (struct window_mode_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int window_copy_in_set (struct window_mode_entry*,scalar_t__,scalar_t__,char const*) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_cursor_next_word(struct window_mode_entry *wme,
    const char *separators)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*back_s = data->backing;
	u_int				 px, py, xx, yy;
	int				 expected = 0;

	px = data->cx;
	py = screen_hsize(back_s) + data->cy - data->oy;
	xx = window_copy_find_length(wme, py);
	yy = screen_hsize(back_s) + screen_size_y(back_s) - 1;

	/*
	 * First skip past any nonword characters and then any word characters.
	 *
	 * expected is initially set to 0 for the former and then 1 for the
	 * latter.
	 */
	do {
		while (px > xx ||
		    window_copy_in_set(wme, px, py, separators) == expected) {
			/* Move down if we're past the end of the line. */
			if (px > xx) {
				if (py == yy)
					return;
				window_copy_cursor_down(wme, 0);
				px = 0;

				py = screen_hsize(back_s) + data->cy - data->oy;
				xx = window_copy_find_length(wme, py);
			} else
				px++;
		}
		expected = !expected;
	} while (expected == 1);

	window_copy_update_cursor(wme, px, data->cy);
	if (window_copy_update_selection(wme, 1))
		window_copy_redraw_lines(wme, data->cy, 1);
}