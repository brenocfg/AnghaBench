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
struct screen {int /*<<< orphan*/  grid; } ;
struct window_pane {struct screen base; } ;

/* Variables and functions */
 scalar_t__ fnmatch (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* grid_view_string_cells (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 

u_int
window_pane_search(struct window_pane *wp, const char *searchstr)
{
	struct screen	*s = &wp->base;
	char		*newsearchstr, *line;
	u_int		 i;

	xasprintf(&newsearchstr, "*%s*", searchstr);

	for (i = 0; i < screen_size_y(s); i++) {
		line = grid_view_string_cells(s->grid, 0, i, screen_size_x(s));
		if (fnmatch(newsearchstr, line, 0) == 0) {
			free(line);
			break;
		}
		free(line);
	}

	free(newsearchstr);
	if (i == screen_size_y(s))
		return (0);
	return (i + 1);
}