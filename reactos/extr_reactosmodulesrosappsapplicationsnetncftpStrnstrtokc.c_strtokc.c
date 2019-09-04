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

char *
strtokc(char *parsestr, const char *delims, char **context)
{
	char *cp;
	const char *cp2;
	char c, c2;
	char *start;

	if (parsestr == NULL)
		start = *context;
	else
		start = parsestr;

	if ((start == NULL) || (delims == NULL)) {
		*context = NULL;
		return NULL;
	}

	/* Eat leading delimiters. */
	for (cp = start; ; ) {
next1:
		c = *cp++;
		if (c == '\0') {
			/* No more tokens. */
			*context = NULL;
			return (NULL);
		}
		for (cp2 = delims; ; ) {
			c2 = (char) *cp2++;
			if (c2 == '\0') {
				/* This character was not a delimiter.
				 * The token starts here.
				 */
				start = cp - 1;
				goto starttok;
			}
			if (c2 == c) {
				/* This char was a delimiter. */
				/* Skip it, look at next character. */
				goto next1;
			}
		}
		/*NOTREACHED*/
	}

starttok:
	for ( ; ; cp++) {
		c = *cp;
		if (c == '\0') {
			/* Token is finished. */
			*context = cp;
			break;
		}
		for (cp2 = delims; ; ) {
			c2 = (char) *cp2++;
			if (c2 == '\0') {
				/* This character was not a delimiter.
				 * Keep it as part of current token.
				 */
				break;
			}
			if (c2 == c) {
				/* This char was a delimiter. */
				/* End of token. */
				*cp++ = '\0';
				*context = cp;
				return (start);
			}
		}
	}
	return (start);
}