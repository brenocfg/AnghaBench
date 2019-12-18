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

__attribute__((used)) static float acrobat_compatible_atof(char *s)
{
	int neg = 0;
	int i = 0;

	while (*s == '-')
	{
		neg = 1;
		++s;
	}
	while (*s == '+')
	{
		++s;
	}

	while (*s >= '0' && *s <= '9')
	{
		/* We deliberately ignore overflow here.
		 * Tests show that Acrobat handles * overflows in exactly the same way we do:
		 * 123450000000000000000678 is read as 678.
		 */
		i = i * 10 + (*s - '0');
		++s;
	}

	if (*s == '.')
	{
		float v = i;
		float n = 0;
		float d = 1;
		++s;
		while (*s >= '0' && *s <= '9')
		{
			n = 10 * n + (*s - '0');
			d = 10 * d;
			++s;
		}
		v += n / d;
		return neg ? -v : v;
	}
	else
	{
		return neg ? -i : i;
	}
}