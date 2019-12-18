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

__attribute__((used)) static int
starts_with(const char **s, const char *string)
{
	const char *x = *s, *y = string;
	while (*x && *y && (*x == *y || *x == *y + 32))
		++x, ++y;
	if (*y == 0)
	{
		/* Match.  */
		*s = x;
		return 1;
	}
	else
		return 0;
}