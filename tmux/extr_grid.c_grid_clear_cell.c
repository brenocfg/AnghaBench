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
struct grid_line {struct grid_cell_entry* extddata; int /*<<< orphan*/  flags; struct grid_cell_entry* celldata; } ;
struct TYPE_2__ {size_t bg; } ;
struct grid_cell_entry {size_t offset; size_t bg; TYPE_1__ data; int /*<<< orphan*/  flags; } ;
struct grid_cell {size_t offset; size_t bg; TYPE_1__ data; int /*<<< orphan*/  flags; } ;
struct grid {struct grid_line* linedata; } ;

/* Variables and functions */
 size_t COLOUR_FLAG_256 ; 
 size_t COLOUR_FLAG_RGB ; 
 int /*<<< orphan*/  GRID_FLAG_BG256 ; 
 int /*<<< orphan*/  GRID_LINE_EXTENDED ; 
 int /*<<< orphan*/  grid_cleared_cell ; 
 int /*<<< orphan*/  grid_cleared_entry ; 
 int /*<<< orphan*/  grid_get_extended_cell (struct grid_line*,struct grid_cell_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell_entry*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
grid_clear_cell(struct grid *gd, u_int px, u_int py, u_int bg)
{
	struct grid_line	*gl = &gd->linedata[py];
	struct grid_cell_entry	*gce = &gl->celldata[px];
	struct grid_cell	*gc;

	memcpy(gce, &grid_cleared_entry, sizeof *gce);
	if (bg != 8) {
		if (bg & COLOUR_FLAG_RGB) {
			grid_get_extended_cell(gl, gce, gce->flags);
			gl->flags |= GRID_LINE_EXTENDED;

			gc = &gl->extddata[gce->offset];
			memcpy(gc, &grid_cleared_cell, sizeof *gc);
			gc->bg = bg;
		} else {
			if (bg & COLOUR_FLAG_256)
				gce->flags |= GRID_FLAG_BG256;
			gce->data.bg = bg;
		}
	}
}