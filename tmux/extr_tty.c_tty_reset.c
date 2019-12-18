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
struct grid_cell {int attr; } ;
struct tty {int last_wp; struct grid_cell last_cell; struct grid_cell cell; } ;

/* Variables and functions */
 int GRID_ATTR_CHARSET ; 
 int /*<<< orphan*/  TTYC_RMACS ; 
 int /*<<< orphan*/  TTYC_SGR0 ; 
 int /*<<< orphan*/  grid_cells_equal (struct grid_cell*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tty_acs_needed (struct tty*) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 

void
tty_reset(struct tty *tty)
{
	struct grid_cell	*gc = &tty->cell;

	if (!grid_cells_equal(gc, &grid_default_cell)) {
		if ((gc->attr & GRID_ATTR_CHARSET) && tty_acs_needed(tty))
			tty_putcode(tty, TTYC_RMACS);
		tty_putcode(tty, TTYC_SGR0);
		memcpy(gc, &grid_default_cell, sizeof *gc);
	}

	memcpy(&tty->last_cell, &grid_default_cell, sizeof tty->last_cell);
	tty->last_wp = -1;
}