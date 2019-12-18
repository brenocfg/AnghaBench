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
struct grid_cell {int flags; int /*<<< orphan*/  data; } ;
struct grid {scalar_t__ hsize; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int /*<<< orphan*/  free (struct utf8_data*) ; 
 int /*<<< orphan*/  grid_get_cell (struct grid*,scalar_t__,scalar_t__,struct grid_cell*) ; 
 scalar_t__ grid_line_length (struct grid*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct utf8_data*,int /*<<< orphan*/ *,int) ; 
 char* utf8_tocstr (struct utf8_data*) ; 
 struct utf8_data* xreallocarray (struct utf8_data*,size_t,int) ; 

char *
format_grid_line(struct grid *gd, u_int y)
{
	struct grid_cell	 gc;
	struct utf8_data	*ud = NULL;
	u_int			 x;
	size_t			 size = 0;
	char			*s = NULL;

	y = gd->hsize + y;
	for (x = 0; x < grid_line_length(gd, y); x++) {
		grid_get_cell(gd, x, y, &gc);
		if (gc.flags & GRID_FLAG_PADDING)
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