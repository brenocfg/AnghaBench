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
struct window_pane {int /*<<< orphan*/  flags; int /*<<< orphan*/ * palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
window_pane_reset_palette(struct window_pane *wp)
{
	if (wp->palette == NULL)
		return;

	free(wp->palette);
	wp->palette = NULL;
	wp->flags |= PANE_REDRAW;
}