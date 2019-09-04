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

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/ * winlink_find_by_index (struct winlinks*,int) ; 

__attribute__((used)) static int
winlink_next_index(struct winlinks *wwl, int idx)
{
	int	i;

	i = idx;
	do {
		if (winlink_find_by_index(wwl, i) == NULL)
			return (i);
		if (i == INT_MAX)
			i = 0;
		else
			i++;
	} while (i != idx);
	return (-1);
}