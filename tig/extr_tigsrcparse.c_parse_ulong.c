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
 scalar_t__ isspace (char) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static bool
parse_ulong(const char **pos_ptr, unsigned long *value, char skip, bool optional)
{
	const char *start = *pos_ptr;
	char *end;

	if (*start != skip)
		return optional;

	start++;
	*value = strtoul(start, &end, 10);
	if (end == start)
		return false;

	while (isspace(*end))
		end++;
	*pos_ptr = end;
	return true;
}