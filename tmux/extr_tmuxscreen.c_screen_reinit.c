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
struct screen {int mode; TYPE_1__* grid; scalar_t__ rlower; scalar_t__ rupper; scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_2__ {int /*<<< orphan*/  sy; int /*<<< orphan*/  hsize; } ;

/* Variables and functions */
 int MODE_CURSOR ; 
 int MODE_WRAP ; 
 int /*<<< orphan*/  grid_clear_lines (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  screen_clear_selection (struct screen*) ; 
 int /*<<< orphan*/  screen_free_titles (struct screen*) ; 
 int /*<<< orphan*/  screen_reset_tabs (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 

void
screen_reinit(struct screen *s)
{
	s->cx = 0;
	s->cy = 0;

	s->rupper = 0;
	s->rlower = screen_size_y(s) - 1;

	s->mode = MODE_CURSOR | MODE_WRAP;

	screen_reset_tabs(s);

	grid_clear_lines(s->grid, s->grid->hsize, s->grid->sy, 8);

	screen_clear_selection(s);
	screen_free_titles(s);
}