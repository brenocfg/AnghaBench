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
struct window_pane {scalar_t__ active_point; } ;

/* Variables and functions */

__attribute__((used)) static int
window_tree_cmp_pane_time(const void *a0, const void *b0)
{
	const struct window_pane *const *a = a0;
	const struct window_pane *const *b = b0;

	if ((*a)->active_point < (*b)->active_point)
		return (-1);
	if ((*a)->active_point > (*b)->active_point)
		return (1);
	return (0);
}