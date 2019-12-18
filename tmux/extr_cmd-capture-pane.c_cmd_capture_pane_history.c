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
typedef  int u_int ;
struct TYPE_2__ {struct grid* grid; } ;
struct window_pane {TYPE_1__ base; struct grid* saved_grid; } ;
struct grid_line {int flags; } ;
struct grid_cell {int dummy; } ;
struct grid {int hsize; int sy; } ;
struct cmdq_item {int dummy; } ;
struct args {int dummy; } ;

/* Variables and functions */
 int GRID_LINE_WRAPPED ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 char* args_get (struct args*,char) ; 
 int args_has (struct args*,char) ; 
 int args_strtonum (struct args*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* cmd_capture_pane_append (char*,size_t*,char*,size_t) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct grid_line* grid_peek_line (struct grid*,int) ; 
 char* grid_string_cells (struct grid*,int /*<<< orphan*/ ,int,int,struct grid_cell**,int,int,int) ; 
 int screen_size_x (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
cmd_capture_pane_history(struct args *args, struct cmdq_item *item,
    struct window_pane *wp, size_t *len)
{
	struct grid		*gd;
	const struct grid_line	*gl;
	struct grid_cell	*gc = NULL;
	int			 n, with_codes, escape_c0, join_lines, no_trim;
	u_int			 i, sx, top, bottom, tmp;
	char			*cause, *buf, *line;
	const char		*Sflag, *Eflag;
	size_t			 linelen;

	sx = screen_size_x(&wp->base);
	if (args_has(args, 'a')) {
		gd = wp->saved_grid;
		if (gd == NULL) {
			if (!args_has(args, 'q')) {
				cmdq_error(item, "no alternate screen");
				return (NULL);
			}
			return (xstrdup(""));
		}
	} else
		gd = wp->base.grid;

	Sflag = args_get(args, 'S');
	if (Sflag != NULL && strcmp(Sflag, "-") == 0)
		top = 0;
	else {
		n = args_strtonum(args, 'S', INT_MIN, SHRT_MAX, &cause);
		if (cause != NULL) {
			top = gd->hsize;
			free(cause);
		} else if (n < 0 && (u_int) -n > gd->hsize)
			top = 0;
		else
			top = gd->hsize + n;
		if (top > gd->hsize + gd->sy - 1)
			top = gd->hsize + gd->sy - 1;
	}

	Eflag = args_get(args, 'E');
	if (Eflag != NULL && strcmp(Eflag, "-") == 0)
		bottom = gd->hsize + gd->sy - 1;
	else {
		n = args_strtonum(args, 'E', INT_MIN, SHRT_MAX, &cause);
		if (cause != NULL) {
			bottom = gd->hsize + gd->sy - 1;
			free(cause);
		} else if (n < 0 && (u_int) -n > gd->hsize)
			bottom = 0;
		else
			bottom = gd->hsize + n;
		if (bottom > gd->hsize + gd->sy - 1)
			bottom = gd->hsize + gd->sy - 1;
	}

	if (bottom < top) {
		tmp = bottom;
		bottom = top;
		top = tmp;
	}

	with_codes = args_has(args, 'e');
	escape_c0 = args_has(args, 'C');
	join_lines = args_has(args, 'J');
	no_trim = args_has(args, 'N');

	buf = NULL;
	for (i = top; i <= bottom; i++) {
		line = grid_string_cells(gd, 0, i, sx, &gc, with_codes,
		    escape_c0, !join_lines && !no_trim);
		linelen = strlen(line);

		buf = cmd_capture_pane_append(buf, len, line, linelen);

		gl = grid_peek_line(gd, i);
		if (!join_lines || !(gl->flags & GRID_LINE_WRAPPED))
			buf[(*len)++] = '\n';

		free(line);
	}
	return (buf);
}