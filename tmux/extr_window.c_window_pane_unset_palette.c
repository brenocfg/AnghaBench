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
struct window_pane {int /*<<< orphan*/  flags; scalar_t__* palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 

void
window_pane_unset_palette(struct window_pane *wp, u_int n)
{
	if (n > 0xff || wp->palette == NULL)
		return;

	wp->palette[n] = 0;
	wp->flags |= PANE_REDRAW;
}