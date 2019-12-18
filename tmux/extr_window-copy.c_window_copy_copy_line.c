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
struct window_copy_mode_data {TYPE_1__* backing; } ;
struct utf8_data {int size; char* data; } ;
struct grid_line {int flags; scalar_t__ cellsize; } ;
struct grid_cell {int flags; int attr; int /*<<< orphan*/  data; } ;
struct grid {scalar_t__ sx; } ;
struct TYPE_2__ {struct grid* grid; } ;

/* Variables and functions */
 int GRID_ATTR_CHARSET ; 
 int GRID_FLAG_PADDING ; 
 int GRID_LINE_WRAPPED ; 
 int /*<<< orphan*/  grid_get_cell (struct grid*,scalar_t__,scalar_t__,struct grid_cell*) ; 
 struct grid_line* grid_get_line (struct grid*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* tty_acs_get (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  utf8_copy (struct utf8_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
window_copy_copy_line(struct window_mode_entry *wme, char **buf, size_t *off,
    u_int sy, u_int sx, u_int ex)
{
	struct window_copy_mode_data	*data = wme->data;
	struct grid			*gd = data->backing->grid;
	struct grid_cell		 gc;
	struct grid_line		*gl;
	struct utf8_data		 ud;
	u_int				 i, xx, wrapped = 0;
	const char			*s;

	if (sx > ex)
		return;

	/*
	 * Work out if the line was wrapped at the screen edge and all of it is
	 * on screen.
	 */
	gl = grid_get_line(gd, sy);
	if (gl->flags & GRID_LINE_WRAPPED && gl->cellsize <= gd->sx)
		wrapped = 1;

	/* If the line was wrapped, don't strip spaces (use the full length). */
	if (wrapped)
		xx = gl->cellsize;
	else
		xx = window_copy_find_length(wme, sy);
	if (ex > xx)
		ex = xx;
	if (sx > xx)
		sx = xx;

	if (sx < ex) {
		for (i = sx; i < ex; i++) {
			grid_get_cell(gd, i, sy, &gc);
			if (gc.flags & GRID_FLAG_PADDING)
				continue;
			utf8_copy(&ud, &gc.data);
			if (ud.size == 1 && (gc.attr & GRID_ATTR_CHARSET)) {
				s = tty_acs_get(NULL, ud.data[0]);
				if (s != NULL && strlen(s) <= sizeof ud.data) {
					ud.size = strlen(s);
					memcpy(ud.data, s, ud.size);
				}
			}

			*buf = xrealloc(*buf, (*off) + ud.size);
			memcpy(*buf + *off, ud.data, ud.size);
			*off += ud.size;
		}
	}

	/* Only add a newline if the line wasn't wrapped. */
	if (!wrapped || ex != xx) {
		*buf = xrealloc(*buf, (*off) + 1);
		(*buf)[(*off)++] = '\n';
	}
}