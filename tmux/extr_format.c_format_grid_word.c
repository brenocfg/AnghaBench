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
struct utf8_data {scalar_t__ size; } ;
struct grid_line {int flags; } ;
struct grid_cell {int flags; int /*<<< orphan*/  data; } ;
struct grid {scalar_t__ hsize; int sy; struct grid_line* linedata; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int GRID_LINE_WRAPPED ; 
 int /*<<< orphan*/  free (struct utf8_data*) ; 
 int /*<<< orphan*/  global_s_options ; 
 int /*<<< orphan*/  grid_get_cell (struct grid*,scalar_t__,scalar_t__,struct grid_cell*) ; 
 scalar_t__ grid_line_length (struct grid*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct utf8_data*,int /*<<< orphan*/ *,int) ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ utf8_cstrhas (char const*,int /*<<< orphan*/ *) ; 
 char* utf8_tocstr (struct utf8_data*) ; 
 struct utf8_data* xreallocarray (struct utf8_data*,size_t,int) ; 

char *
format_grid_word(struct grid *gd, u_int x, u_int y)
{
	struct grid_line	*gl;
	struct grid_cell	 gc;
	const char		*ws;
	struct utf8_data	*ud = NULL;
	u_int			 end;
	size_t			 size = 0;
	int			 found = 0;
	char			*s = NULL;

	ws = options_get_string(global_s_options, "word-separators");

	y = gd->hsize + y;
	for (;;) {
		grid_get_cell(gd, x, y, &gc);
		if (gc.flags & GRID_FLAG_PADDING)
			break;
		if (utf8_cstrhas(ws, &gc.data)) {
			found = 1;
			break;
		}

		if (x == 0) {
			if (y == 0)
				break;
			gl = &gd->linedata[y - 1];
			if (~gl->flags & GRID_LINE_WRAPPED)
				break;
			y--;
			x = grid_line_length(gd, y);
			if (x == 0)
				break;
		}
		x--;
	}
	for (;;) {
		if (found) {
			end = grid_line_length(gd, y);
			if (end == 0 || x == end - 1) {
				if (y == gd->hsize + gd->sy - 1)
					break;
				gl = &gd->linedata[y];
				if (~gl->flags & GRID_LINE_WRAPPED)
					break;
				y++;
				x = 0;
			} else
				x++;
		}
		found = 1;

		grid_get_cell(gd, x, y, &gc);
		if (gc.flags & GRID_FLAG_PADDING)
			break;
		if (utf8_cstrhas(ws, &gc.data))
			break;

		ud = xreallocarray(ud, size + 2, sizeof *ud);
		memcpy(&ud[size++], &gc.data, sizeof *ud);
	}
	if (size != 0) {
		ud[size].size = 0;
		s = utf8_tocstr(ud);
		free(ud);
	}
	return (s);
}