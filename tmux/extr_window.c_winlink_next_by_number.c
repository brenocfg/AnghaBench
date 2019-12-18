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
struct winlink {int dummy; } ;
struct session {int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 struct winlink* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct winlink* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winlink*) ; 
 int /*<<< orphan*/  winlinks ; 
 int /*<<< orphan*/  wwl ; 

struct winlink *
winlink_next_by_number(struct winlink *wl, struct session *s, int n)
{
	for (; n > 0; n--) {
		if ((wl = RB_NEXT(winlinks, wwl, wl)) == NULL)
			wl = RB_MIN(winlinks, &s->windows);
	}

	return (wl);
}