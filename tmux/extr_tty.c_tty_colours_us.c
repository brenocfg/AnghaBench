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
typedef  int u_int ;
typedef  int u_char ;
struct grid_cell {int us; } ;
struct tty {struct grid_cell cell; } ;

/* Variables and functions */
 int COLOUR_FLAG_RGB ; 
 int /*<<< orphan*/  TTYC_SETULC ; 
 int /*<<< orphan*/  colour_split_rgb (int,int*,int*,int*) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tty_colours_us(struct tty *tty, const struct grid_cell *gc)
{
	struct grid_cell	*tc = &tty->cell;
	u_int			 c;
	u_char			 r, g, b;

	/* Must be an RGB colour - this should never happen. */
	if (~gc->us & COLOUR_FLAG_RGB)
		return;

	/*
	 * Setulc follows the ncurses(3) one argument "direct colour"
	 * capability format. Calculate the colour value.
	 */
	colour_split_rgb(gc->us, &r, &g, &b);
	c = (65536 * r) + (256 * g) + b;

	/* Write the colour. */
	tty_putcode1(tty, TTYC_SETULC, c);

	/* Save the new values in the terminal current cell. */
	tc->us = gc->us;
}