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
struct tty {int dummy; } ;
struct grid_cell {int /*<<< orphan*/  bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_attributes (struct tty*,struct grid_cell*,struct window_pane*) ; 

__attribute__((used)) static void
tty_default_attributes(struct tty *tty, struct window_pane *wp, u_int bg)
{
	static struct grid_cell gc;

	memcpy(&gc, &grid_default_cell, sizeof gc);
	gc.bg = bg;
	tty_attributes(tty, &gc, wp);
}