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
struct winlinks {int dummy; } ;
struct winlink {int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,struct winlinks*,struct winlink*) ; 
 int /*<<< orphan*/ * winlink_find_by_index (struct winlinks*,int) ; 
 int winlink_next_index (struct winlinks*,int) ; 
 int /*<<< orphan*/  winlinks ; 
 struct winlink* xcalloc (int,int) ; 

struct winlink *
winlink_add(struct winlinks *wwl, int idx)
{
	struct winlink	*wl;

	if (idx < 0) {
		if ((idx = winlink_next_index(wwl, -idx - 1)) == -1)
			return (NULL);
	} else if (winlink_find_by_index(wwl, idx) != NULL)
		return (NULL);

	wl = xcalloc(1, sizeof *wl);
	wl->idx = idx;
	RB_INSERT(winlinks, wwl, wl);

	return (wl);
}