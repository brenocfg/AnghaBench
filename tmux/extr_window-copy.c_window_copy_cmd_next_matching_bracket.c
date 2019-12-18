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
struct window_mode_entry {scalar_t__ prefix; struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; scalar_t__ oy; scalar_t__ modekeys; struct screen* backing; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
struct screen {TYPE_2__* grid; } ;
struct grid_line {int flags; scalar_t__ cellsize; } ;
struct TYPE_4__ {int size; char* data; } ;
struct grid_cell {int flags; TYPE_1__ data; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_5__ {scalar_t__ sx; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int GRID_LINE_WRAPPED ; 
 scalar_t__ MODEKEY_EMACS ; 
 scalar_t__ MODEKEY_VI ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  grid_get_cell (TYPE_2__*,scalar_t__,scalar_t__,struct grid_cell*) ; 
 struct grid_line* grid_get_line (TYPE_2__*,scalar_t__) ; 
 scalar_t__ screen_hsize (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  window_copy_cmd_previous_matching_bracket (struct window_copy_cmd_state*) ; 
 int /*<<< orphan*/  window_copy_cursor_next_word_end (struct window_mode_entry*,char*) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_scroll_to (struct window_mode_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_next_matching_bracket(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	u_int				 np = wme->prefix;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = data->backing;
	char				 open[] = "{[(", close[] = "}])";
	char				 tried, found, end, *cp;
	u_int				 px, py, xx, yy, sx, sy, n;
	struct grid_cell		 gc;
	int				 failed;
	struct grid_line		*gl;

	for (; np != 0; np--) {
		/* Get cursor position and line length. */
		px = data->cx;
		py = screen_hsize(s) + data->cy - data->oy;
		xx = window_copy_find_length(wme, py);
		yy = screen_hsize(s) + screen_size_y(s) - 1;
		if (xx == 0)
			break;

		/*
		 * Get the current character. If not on a bracket, try the
		 * next. If still not, then behave like next-word.
		 */
		tried = 0;
	retry:
		grid_get_cell(s->grid, px, py, &gc);
		if (gc.data.size != 1 || (gc.flags & GRID_FLAG_PADDING))
			cp = NULL;
		else {
			found = *gc.data.data;

			/*
			 * In vi mode, attempt to move to previous bracket if a
			 * closing bracket is found first. If this fails,
			 * return to the original cursor position.
			 */
			cp = strchr(close, found);
			if (cp != NULL && data->modekeys == MODEKEY_VI) {
				sx = data->cx;
				sy = screen_hsize(s) + data->cy - data->oy;

				window_copy_scroll_to(wme, px, py);
				window_copy_cmd_previous_matching_bracket(cs);

				px = data->cx;
				py = screen_hsize(s) + data->cy - data->oy;
				grid_get_cell(s->grid, px, py, &gc);
				if (gc.data.size != 1 ||
				    (gc.flags & GRID_FLAG_PADDING) ||
				    strchr(close, *gc.data.data) == NULL)
					window_copy_scroll_to(wme, sx, sy);
				break;
			}

			cp = strchr(open, found);
		}
		if (cp == NULL) {
			if (data->modekeys == MODEKEY_EMACS) {
				if (!tried && px <= xx) {
					px++;
					tried = 1;
					goto retry;
				}
				window_copy_cursor_next_word_end(wme, "{[( ");
				continue;
			}
			/* For vi, continue searching for bracket until EOL. */
			if (px > xx) {
				if (py == yy)
					continue;
				gl = grid_get_line(s->grid, py);
				if (~gl->flags & GRID_LINE_WRAPPED)
					continue;
				if (gl->cellsize > s->grid->sx)
					continue;
				px = 0;
				py++;
				xx = window_copy_find_length(wme, py);
			} else
				px++;
			goto retry;
		}
		end = close[cp - open];

		/* Walk forward until the matching bracket is reached. */
		n = 1;
		failed = 0;
		do {
			if (px > xx) {
				if (py == yy) {
					failed = 1;
					break;
				}
				px = 0;
				py++;
				xx = window_copy_find_length(wme, py);
			} else
				px++;

			grid_get_cell(s->grid, px, py, &gc);
			if (gc.data.size == 1 &&
			    (~gc.flags & GRID_FLAG_PADDING)) {
				if (*gc.data.data == found)
					n++;
				else if (*gc.data.data == end)
					n--;
			}
		} while (n != 0);

		/* Move the cursor to the found location if any. */
		if (!failed)
			window_copy_scroll_to(wme, px, py);
	}

	return (WINDOW_COPY_CMD_NOTHING);
}