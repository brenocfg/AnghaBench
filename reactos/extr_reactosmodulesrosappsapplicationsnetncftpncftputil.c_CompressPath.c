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
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
CompressPath(char *const dst, const char *const src, const size_t dsize)
{
	int c;
	const char *s;
	char *d, *lim;
	char *a, *b;

	if (src[0] == '\0') {
		*dst = '\0';
		return;
	}

	s = src;
	d = dst;
	lim = d + dsize - 1;	/* leave room for nul byte. */
	for (;;) {
		c = *s;
		if (c == '.') {
			if (((s == src) || (s[-1] == '/')) && ((s[1] == '/') || (s[1] == '\0'))) {
				/* Don't copy "./" */
				if (s[1] == '/')
					++s;
				++s;
			} else if (d < lim) {
				*d++ = *s++;
			} else {
				++s;
			}
		} else if (c == '/') {
			/* Don't copy multiple slashes. */
			if (d < lim)
				*d++ = *s++;
			else
				++s;
			for (;;) {
				c = *s;
				if (c == '/') {
					/* Don't copy multiple slashes. */
					++s;
				} else if (c == '.') {
					c = s[1];
					if (c == '/') {
						/* Skip "./" */
						s += 2;
					} else if (c == '\0') {
						/* Skip "./" */
						s += 1;
					} else {
						break;
					}
				} else {
					break;
				}
			}
		} else if (c == '\0') {
			/* Remove trailing slash. */
			if ((d[-1] == '/') && (d > (dst + 1)))
				d[-1] = '\0';
			*d = '\0';
			break;
		} else if (d < lim) {
			*d++ = *s++;
		} else {
			++s;
		}
	}
	a = dst;

	/* fprintf(stderr, "<%s>\n", dst); */
	/* Go through and remove .. in the path when we know what the
	 * parent directory is.  After we get done with this, the only
	 * .. nodes in the path will be at the front.
	 */
	while (*a != '\0') {
		b = a;
		for (;;) {
			/* Get the next node in the path. */
			if (*a == '\0')
				return;
			if (*a == '/') {
				++a;
				break;
			}
			++a;
		}
		if ((b[0] == '.') && (b[1] == '.')) {
			if (b[2] == '/') {
				/* We don't know what the parent of this
				 * node would be.
				 */
				continue;
			}
		}
		if ((a[0] == '.') && (a[1] == '.')) {
			if (a[2] == '/') {
				/* Remove the .. node and the one before it. */
				if ((b == dst) && (*dst == '/'))
					(void) memmove(b + 1, a + 3, strlen(a + 3) + 1);
				else
					(void) memmove(b, a + 3, strlen(a + 3) + 1);
				a = dst;	/* Start over. */
			} else if (a[2] == '\0') {
				/* Remove a trailing .. like:  /aaa/bbb/.. */
				if ((b <= dst + 1) && (*dst == '/'))
					dst[1] = '\0';
				else
					b[-1] = '\0';
				a = dst;	/* Start over. */
			} else {
				/* continue processing this node.
				 * It is probably some bogus path,
				 * like ".../", "..foo/", etc.
				 */
			}
		}
	}
}