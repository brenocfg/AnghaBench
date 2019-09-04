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
struct window_pane {int* palette; } ;

/* Variables and functions */
 int COLOUR_FLAG_256 ; 

int
window_pane_get_palette(struct window_pane *wp, int c)
{
	int	new;

	if (wp == NULL || wp->palette == NULL)
		return (-1);

	new = -1;
	if (c < 8)
		new = wp->palette[c];
	else if (c >= 90 && c <= 97)
		new = wp->palette[8 + c - 90];
	else if (c & COLOUR_FLAG_256)
		new = wp->palette[c & ~COLOUR_FLAG_256];
	if (new == 0)
		return (-1);
	return (new);
}