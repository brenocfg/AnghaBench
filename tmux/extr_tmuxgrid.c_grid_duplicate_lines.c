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
struct grid_line {int cellsize; scalar_t__ extdsize; struct grid_line* extddata; struct grid_line* celldata; } ;
struct grid {scalar_t__ hsize; scalar_t__ sy; struct grid_line* linedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_free_lines (struct grid*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct grid_line*,struct grid_line*,int) ; 
 void* xreallocarray (int /*<<< orphan*/ *,int,int) ; 

void
grid_duplicate_lines(struct grid *dst, u_int dy, struct grid *src, u_int sy,
    u_int ny)
{
	struct grid_line	*dstl, *srcl;
	u_int			 yy;

	if (dy + ny > dst->hsize + dst->sy)
		ny = dst->hsize + dst->sy - dy;
	if (sy + ny > src->hsize + src->sy)
		ny = src->hsize + src->sy - sy;
	grid_free_lines(dst, dy, ny);

	for (yy = 0; yy < ny; yy++) {
		srcl = &src->linedata[sy];
		dstl = &dst->linedata[dy];

		memcpy(dstl, srcl, sizeof *dstl);
		if (srcl->cellsize != 0) {
			dstl->celldata = xreallocarray(NULL,
			    srcl->cellsize, sizeof *dstl->celldata);
			memcpy(dstl->celldata, srcl->celldata,
			    srcl->cellsize * sizeof *dstl->celldata);
		} else
			dstl->celldata = NULL;

		if (srcl->extdsize != 0) {
			dstl->extdsize = srcl->extdsize;
			dstl->extddata = xreallocarray(NULL, dstl->extdsize,
			    sizeof *dstl->extddata);
			memcpy(dstl->extddata, srcl->extddata, dstl->extdsize *
			    sizeof *dstl->extddata);
		}

		sy++;
		dy++;
	}
}