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
struct tty {int last_wp; int flags; int /*<<< orphan*/  mode; void* rright; void* rlower; void* rleft; void* rupper; void* cy; void* cx; int /*<<< orphan*/  last_cell; int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_MODES ; 
 int /*<<< orphan*/  MODE_CURSOR ; 
 int /*<<< orphan*/  TTYC_SGR0 ; 
 int TTY_STARTED ; 
 void* UINT_MAX ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_cursor (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_margin_off (struct tty*) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_puts (struct tty*,char*) ; 
 int /*<<< orphan*/  tty_region_off (struct tty*) ; 
 int /*<<< orphan*/  tty_update_mode (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tty_use_margin (struct tty*) ; 

__attribute__((used)) static void
tty_invalidate(struct tty *tty)
{
	memcpy(&tty->cell, &grid_default_cell, sizeof tty->cell);

	memcpy(&tty->last_cell, &grid_default_cell, sizeof tty->last_cell);
	tty->last_wp = -1;

	tty->cx = tty->cy = UINT_MAX;

	tty->rupper = tty->rleft = UINT_MAX;
	tty->rlower = tty->rright = UINT_MAX;

	if (tty->flags & TTY_STARTED) {
		if (tty_use_margin(tty))
			tty_puts(tty, "\033[?69h"); /* DECLRMM */
		tty_putcode(tty, TTYC_SGR0);

		tty->mode = ALL_MODES;
		tty_update_mode(tty, MODE_CURSOR, NULL);

		tty_cursor(tty, 0, 0);
		tty_region_off(tty);
		tty_margin_off(tty);
	} else
		tty->mode = MODE_CURSOR;
}