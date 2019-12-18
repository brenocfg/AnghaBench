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
typedef  size_t u_int ;
struct grid_line {size_t hsize; size_t sy; int flags; size_t cellused; scalar_t__ hscrolled; struct grid_line* linedata; int /*<<< orphan*/  sx; } ;
struct TYPE_2__ {size_t width; } ;
struct grid_cell {TYPE_1__ data; } ;
struct grid {size_t hsize; size_t sy; int flags; size_t cellused; scalar_t__ hscrolled; struct grid* linedata; int /*<<< orphan*/  sx; } ;

/* Variables and functions */
 int GRID_LINE_DEAD ; 
 int GRID_LINE_EXTENDED ; 
 int GRID_LINE_WRAPPED ; 
 int /*<<< orphan*/  free (struct grid_line*) ; 
 struct grid_line* grid_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_get_cell1 (struct grid_line*,size_t,struct grid_cell*) ; 
 int /*<<< orphan*/  grid_reflow_add (struct grid_line*,scalar_t__) ; 
 int /*<<< orphan*/  grid_reflow_join (struct grid_line*,struct grid_line*,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_reflow_move (struct grid_line*,struct grid_line*) ; 
 int /*<<< orphan*/  grid_reflow_split (struct grid_line*,struct grid_line*,size_t,size_t,size_t) ; 

void
grid_reflow(struct grid *gd, u_int sx)
{
	struct grid		*target;
	struct grid_line	*gl;
	struct grid_cell	 gc;
	u_int			 yy, width, i, at, first;

	/*
	 * Create a destination grid. This is just used as a container for the
	 * line data and may not be fully valid.
	 */
	target = grid_create(gd->sx, 0, 0);

	/*
	 * Loop over each source line.
	 */
	for (yy = 0; yy < gd->hsize + gd->sy; yy++) {
		gl = &gd->linedata[yy];
		if (gl->flags & GRID_LINE_DEAD)
			continue;

		/*
		 * Work out the width of this line. first is the width of the
		 * first character, at is the point at which the available
		 * width is hit, and width is the full line width.
		 */
		first = at = width = 0;
		if (~gl->flags & GRID_LINE_EXTENDED) {
			first = 1;
			width = gl->cellused;
			if (width > sx)
				at = sx;
			else
				at = width;
		} else {
			for (i = 0; i < gl->cellused; i++) {
				grid_get_cell1(gl, i, &gc);
				if (i == 0)
					first = gc.data.width;
				if (at == 0 && width + gc.data.width > sx)
					at = i;
				width += gc.data.width;
			}
		}

		/*
		 * If the line is exactly right or the first character is wider
		 * than the targe width, just move it across unchanged.
		 */
		if (width == sx || first > sx) {
			grid_reflow_move(target, gl);
			continue;
		}

		/*
		 * If the line is too big, it needs to be split, whether or not
		 * it was previously wrapped.
		 */
		if (width > sx) {
			grid_reflow_split(target, gd, sx, yy, at);
			continue;
		}

		/*
		 * If the line was previously wrapped, join as much as possible
		 * of the next line.
		 */
		if (gl->flags & GRID_LINE_WRAPPED)
			grid_reflow_join(target, gd, sx, yy, width, 0);
		else
			grid_reflow_move(target, gl);
	}

	/*
	 * Replace the old grid with the new.
	 */
	if (target->sy < gd->sy)
		grid_reflow_add(target, gd->sy - target->sy);
	gd->hsize = target->sy - gd->sy;
	if (gd->hscrolled > gd->hsize)
		gd->hscrolled = gd->hsize;
	free(gd->linedata);
	gd->linedata = target->linedata;
	free(target);
}