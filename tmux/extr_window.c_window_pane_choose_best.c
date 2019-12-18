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
typedef  size_t u_int ;
struct window_pane {scalar_t__ active_point; } ;

/* Variables and functions */

__attribute__((used)) static struct window_pane *
window_pane_choose_best(struct window_pane **list, u_int size)
{
	struct window_pane	*next, *best;
	u_int			 i;

	if (size == 0)
		return (NULL);

	best = list[0];
	for (i = 1; i < size; i++) {
		next = list[i];
		if (next->active_point > best->active_point)
			best = next;
	}
	return (best);
}