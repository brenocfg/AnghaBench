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

/* Variables and functions */
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
keyword_in_list(const char *name, const char **list, int n)
{
	int l = 0;
	int r = n - 1;
	while (l <= r)
	{
		int m = (l + r) >> 1;
		int c = strcmp(name, list[m]);
		if (c < 0)
			r = m - 1;
		else if (c > 0)
			l = m + 1;
		else
			return 1;
	}
	return 0;
}