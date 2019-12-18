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

__attribute__((used)) static char *
skip_scheme(char *path)
{
	char *p = path;

	/* Skip over: alpha *(alpha | digit | "+" | "-" | ".") looking for : */
	if (*p >= 'a' && *p <= 'z')
	{}
	else if (*p >= 'A' && *p <= 'Z')
	{}
	else
		return path;

	while (*++p)
	{
		if (*p >= 'a' && *p <= 'z')
		{}
		else if (*p >= 'A' && *p <= 'Z')
		{}
		else if (*p >= '0' && *p <= '9')
		{}
		else if (*p == '+')
		{}
		else if (*p == '-')
		{}
		else if (*p == '.')
		{}
		else if (*p == ':')
			return p+1;
		else
			break;
	}
	return path;
}