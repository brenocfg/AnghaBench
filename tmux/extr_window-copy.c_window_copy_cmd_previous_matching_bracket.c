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
struct window_mode_entry {scalar_t__ prefix; struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; scalar_t__ oy; scalar_t__ modekeys; struct screen* backing; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
struct screen {int /*<<< orphan*/  grid; } ;
struct TYPE_2__ {int size; char* data; } ;
struct grid_cell {int flags; TYPE_1__ data; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 scalar_t__ MODEKEY_EMACS ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  grid_get_cell (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct grid_cell*) ; 
 scalar_t__ screen_hsize (struct screen*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  window_copy_cursor_previous_word (struct window_mode_entry*,char*,int) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_scroll_to (struct window_mode_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_previous_matching_bracket(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	u_int				 np = wme->prefix;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = data->backing;
	char				 open[] = "{[(", close[] = "}])";
	char				 tried, found, start, *cp;
	u_int				 px, py, xx, n;
	struct grid_cell		 gc;
	int				 failed;

	for (; np != 0; np--) {
		/* Get cursor position and line length. */
		px = data->cx;
		py = screen_hsize(s) + data->cy - data->oy;
		xx = window_copy_find_length(wme, py);
		if (xx == 0)
			break;

		/*
		 * Get the current character. If not on a bracket, try the
		 * previous. If still not, then behave like previous-word.
		 */
		tried = 0;
	retry:
		grid_get_cell(s->grid, px, py, &gc);
		if (gc.data.size != 1 || (gc.flags & GRID_FLAG_PADDING))
			cp = NULL;
		else {
			found = *gc.data.data;
			cp = strchr(close, found);
		}
		if (cp == NULL) {
			if (data->modekeys == MODEKEY_EMACS) {
				if (!tried && px > 0) {
					px--;
					tried = 1;
					goto retry;
				}
				window_copy_cursor_previous_word(wme, "}]) ", 1);
			}
			continue;
		}
		start = open[cp - close];

		/* Walk backward until the matching bracket is reached. */
		n = 1;
		failed = 0;
		do {
			if (px == 0) {
				if (py == 0) {
					failed = 1;
					break;
				}
				do {
					py--;
					xx = window_copy_find_length(wme, py);
				} while (xx == 0 && py > 0);
				if (xx == 0 && py == 0) {
					failed = 1;
					break;
				}
				px = xx - 1;
			} else
				px--;

			grid_get_cell(s->grid, px, py, &gc);
			if (gc.data.size == 1 &&
			    (~gc.flags & GRID_FLAG_PADDING)) {
				if (*gc.data.data == found)
					n++;
				else if (*gc.data.data == start)
					n--;
			}
		} while (n != 0);

		/* Move the cursor to the found location if any. */
		if (!failed)
			window_copy_scroll_to(wme, px, py);
	}

	return (WINDOW_COPY_CMD_NOTHING);
}