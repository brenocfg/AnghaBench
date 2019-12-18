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
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
tty_term_strip(const char *s)
{
	const char     *ptr;
	static char	buf[8192];
	size_t		len;

	/* Ignore strings with no padding. */
	if (strchr(s, '$') == NULL)
		return (xstrdup(s));

	len = 0;
	for (ptr = s; *ptr != '\0'; ptr++) {
		if (*ptr == '$' && *(ptr + 1) == '<') {
			while (*ptr != '\0' && *ptr != '>')
				ptr++;
			if (*ptr == '>')
				ptr++;
		}

		buf[len++] = *ptr;
		if (len == (sizeof buf) - 1)
			break;
	}
	buf[len] = '\0';

	return (xstrdup(buf));
}