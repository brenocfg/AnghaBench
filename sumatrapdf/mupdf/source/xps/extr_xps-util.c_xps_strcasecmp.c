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
 int xps_tolower (char) ; 

int
xps_strcasecmp(char *a, char *b)
{
	while (xps_tolower(*a) == xps_tolower(*b))
	{
		if (*a++ == 0)
			return 0;
		b++;
	}
	return xps_tolower(*a) - xps_tolower(*b);
}