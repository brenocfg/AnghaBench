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
 scalar_t__ strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static int
_zed_event_value_is_hex(const char *name)
{
	const char *hex_suffix[] = {
		"_guid",
		"_guids",
		NULL
	};
	const char **pp;
	char *p;

	if (!name)
		return (0);

	for (pp = hex_suffix; *pp; pp++) {
		p = strstr(name, *pp);
		if (p && strlen(p) == strlen(*pp))
			return (1);
	}
	return (0);
}