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
struct grid_line {size_t extdsize; int /*<<< orphan*/ * extddata; struct grid_cell_entry* celldata; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  attr; } ;
struct grid_cell_entry {int flags; size_t offset; TYPE_1__ data; } ;
struct grid_cell {int flags; int /*<<< orphan*/  data; scalar_t__ us; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOUR_FLAG_256 ; 
 int GRID_FLAG_BG256 ; 
 int GRID_FLAG_EXTENDED ; 
 int GRID_FLAG_FG256 ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  utf8_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
	struct grid_cell_entry	*gce = &gl->celldata[px];

	if (gce->flags & GRID_FLAG_EXTENDED) {
		if (gce->offset >= gl->extdsize)
			memcpy(gc, &grid_default_cell, sizeof *gc);
		else
			memcpy(gc, &gl->extddata[gce->offset], sizeof *gc);
		return;
	}

	gc->flags = gce->flags & ~(GRID_FLAG_FG256|GRID_FLAG_BG256);
	gc->attr = gce->data.attr;
	gc->fg = gce->data.fg;
	if (gce->flags & GRID_FLAG_FG256)
		gc->fg |= COLOUR_FLAG_256;
	gc->bg = gce->data.bg;
	if (gce->flags & GRID_FLAG_BG256)
		gc->bg |= COLOUR_FLAG_256;
	gc->us = 0;
	utf8_set(&gc->data, gce->data.data);
}