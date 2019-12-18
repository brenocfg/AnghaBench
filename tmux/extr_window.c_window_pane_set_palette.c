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
struct window_pane {int* palette; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int* xcalloc (int,int) ; 

void
window_pane_set_palette(struct window_pane *wp, u_int n, int colour)
{
	if (n > 0xff)
		return;

	if (wp->palette == NULL)
		wp->palette = xcalloc(0x100, sizeof *wp->palette);

	wp->palette[n] = colour;
	wp->flags |= PANE_REDRAW;
}