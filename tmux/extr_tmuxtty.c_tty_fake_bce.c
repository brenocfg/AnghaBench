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
typedef  int /*<<< orphan*/  u_int ;
struct window_pane {int dummy; } ;
struct tty {int /*<<< orphan*/  term; } ;
struct grid_cell {int /*<<< orphan*/  bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOUR_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTYC_BCE ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_default_colours (struct grid_cell*,struct window_pane*) ; 
 scalar_t__ tty_term_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tty_fake_bce(const struct tty *tty, struct window_pane *wp, u_int bg)
{
	struct grid_cell	gc;

	if (tty_term_flag(tty->term, TTYC_BCE))
		return (0);

	memcpy(&gc, &grid_default_cell, sizeof gc);
	if (wp != NULL)
		tty_default_colours(&gc, wp);

	if (!COLOUR_DEFAULT(bg) || !COLOUR_DEFAULT(gc.bg))
		return (1);
	return (0);
}