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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static char *
format_substitute(const char *source, const char *from, const char *to)
{
	char		*copy, *new;
	const char	*cp;
	size_t		 fromlen, tolen, newlen, used;

	fromlen = strlen(from);
	tolen = strlen(to);

	newlen = strlen(source) + 1;
	copy = new = xmalloc(newlen);

	for (cp = source; *cp != '\0'; /* nothing */) {
		if (strncmp(cp, from, fromlen) != 0) {
			*new++ = *cp++;
			continue;
		}
		used = new - copy;

		newlen += tolen;
		copy = xrealloc(copy, newlen);

		new = copy + used;
		memcpy(new, to, tolen);

		new += tolen;
		cp += fromlen;
	}

	*new = '\0';
	return (copy);
}