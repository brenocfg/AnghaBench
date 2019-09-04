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
struct window_pane {int id; } ;

/* Variables and functions */

int
window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
	return (wp1->id - wp2->id);
}