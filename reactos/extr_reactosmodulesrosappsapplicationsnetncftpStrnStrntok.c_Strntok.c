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
 int /*<<< orphan*/ * strchr (char const*,int) ; 

int
Strntok(char *dstTokenStart, size_t tokenSize, char *buf, const char *delims)
{
	static char *p = NULL;
	char *end;
	char *lim;
	char *dst;
	int len;

	dst = dstTokenStart;
	lim = dst + tokenSize - 1;		/* Leave room for nul byte. */

	if (buf != NULL) {
		p = buf;
	} else {
		if (p == NULL) {
			*dst = '\0';
			return (-1);		/* No more tokens. */
		}
	}

	for (end = p; ; end++) {
		if (*end == '\0') {
			p = NULL;		/* This is the last token. */
			break;
		}
		if (strchr(delims, (int) *end) != NULL) {
			++end;
			p = end;
			break;
		}
		if (dst < lim)			/* Don't overrun token size. */
			*dst++ = *end;
	}
	*dst = '\0';
	len = (int) (dst - dstTokenStart);	/* Return length of token. */

#if (STRN_ZERO_PAD == 1)
	/* Pad with zeros. */
	for (++dst; dst <= lim; )
		*dst++ = 0;
#endif	/* STRN_ZERO_PAD */

	return (len);
}