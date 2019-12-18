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

int
strntokc(char *dstTokenStart, size_t tokenSize, char *parsestr, const char *delims, char **context)
{
	char *cp;
	const char *cp2;
	char c, c2;
	char *start;
	int len;
	char *dst, *lim;

	dst = dstTokenStart;
	lim = dst + tokenSize - 1;		/* Leave room for nul byte. */

	if (parsestr == NULL)
		start = *context;
	else
		start = parsestr;

	if ((start == NULL) || (delims == NULL)) {
		*context = NULL;
		goto done;
	}

	/* Eat leading delimiters. */
	for (cp = start; ; ) {
next1:
		c = *cp++;
		if (c == '\0') {
			/* No more tokens. */
			*context = NULL;
			goto done;
		}
		for (cp2 = delims; ; ) {
			c2 = (char) *cp2++;
			if (c2 == '\0') {
				/* This character was not a delimiter.
				 * The token starts here.
				 */
				start = cp - 1;
				if (dst < lim)
					*dst++ = c;
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
				goto done;
			}
		}
		if (dst < lim)			/* Don't overrun token size. */
			*dst++ = c;
	}

done:
	*dst = '\0';
	len = (int) (dst - dstTokenStart);	/* Return length of token. */

#if (STRN_ZERO_PAD == 1)
	/* Pad with zeros. */
	for (++dst; dst <= lim; )
		*dst++ = 0;
#endif	/* STRN_ZERO_PAD */

	return (len);
}