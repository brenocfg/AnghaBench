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
 int /*<<< orphan*/ * strchr (char const*,char const) ; 

const char *
format_skip(const char *s, const char *end)
{
	int	brackets = 0;

	for (; *s != '\0'; s++) {
		if (*s == '#' && s[1] == '{')
			brackets++;
		if (*s == '#' && strchr(",#{}", s[1]) != NULL) {
			s++;
			continue;
		}
		if (*s == '}')
			brackets--;
		if (strchr(end, *s) != NULL && brackets == 0)
			break;
	}
	if (*s == '\0')
		return (NULL);
	return (s);
}