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
struct winlink {int idx; } ;
struct session {int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  server_link_window (struct session*,struct winlink*,struct session*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_unlink_window (struct session*,struct winlink*) ; 
 struct winlink* winlink_find_by_index (int /*<<< orphan*/ *,int) ; 

int
winlink_shuffle_up(struct session *s, struct winlink *wl)
{
	int	 idx, last;

	if (wl == NULL)
		return (-1);
	idx = wl->idx + 1;

	/* Find the next free index. */
	for (last = idx; last < INT_MAX; last++) {
		if (winlink_find_by_index(&s->windows, last) == NULL)
			break;
	}
	if (last == INT_MAX)
		return (-1);

	/* Move everything from last - 1 to idx up a bit. */
	for (; last > idx; last--) {
		wl = winlink_find_by_index(&s->windows, last - 1);
		server_link_window(s, wl, s, last, 0, 0, NULL);
		server_unlink_window(s, wl);
	}

	return (idx);
}