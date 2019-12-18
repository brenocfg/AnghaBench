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
tty_term_override_next(const char *s, size_t *offset)
{
	static char	value[8192];
	size_t		n = 0, at = *offset;

	if (s[at] == '\0')
		return (NULL);

	while (s[at] != '\0') {
		if (s[at] == ':') {
			if (s[at + 1] == ':') {
				value[n++] = ':';
				at += 2;
			} else
				break;
		} else {
			value[n++] = s[at];
			at++;
		}
		if (n == (sizeof value) - 1)
			return (NULL);
	}
	if (s[at] != '\0')
		*offset = at + 1;
	else
		*offset = at;
	value[n] = '\0';
	return (value);
}