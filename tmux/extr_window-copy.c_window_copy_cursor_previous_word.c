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
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; scalar_t__ oy; int /*<<< orphan*/  backing; } ;

/* Variables and functions */
 int screen_hsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_cursor_up (struct window_mode_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 scalar_t__ window_copy_in_set (struct window_mode_entry*,scalar_t__,scalar_t__,char const*) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_cursor_previous_word(struct window_mode_entry *wme,
    const char *separators, int already)
{
	struct window_copy_mode_data	*data = wme->data;
	u_int				 px, py;

	px = data->cx;
	py = screen_hsize(data->backing) + data->cy - data->oy;

	/* Move back to the previous word character. */
	if (already || window_copy_in_set(wme, px, py, separators)) {
		for (;;) {
			if (px > 0) {
				px--;
				if (!window_copy_in_set(wme, px, py, separators))
					break;
			} else {
				if (data->cy == 0 &&
				    (screen_hsize(data->backing) == 0 ||
				    data->oy >= screen_hsize(data->backing) - 1))
					goto out;
				window_copy_cursor_up(wme, 0);

				py = screen_hsize(data->backing) + data->cy - data->oy;
				px = window_copy_find_length(wme, py);

				/* Stop if separator at EOL. */
				if (px > 0 &&
				    window_copy_in_set(wme, px - 1, py, separators))
					break;
			}
		}
	}

	/* Move back to the beginning of this word. */
	while (px > 0 && !window_copy_in_set(wme, px - 1, py, separators))
		px--;

out:
	window_copy_update_cursor(wme, px, data->cy);
	if (window_copy_update_selection(wme, 1))
		window_copy_redraw_lines(wme, data->cy, 1);
}