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
Strncpy(char *const dst, const char *const src, const size_t n)
{
	register char *d;
	register const char *s;
	register size_t i;

	d = dst;
	*d = 0;
	if (n != 0) {
		s = src;
		/* If they specified a maximum of n characters, use n - 1 chars to
		 * hold the copy, and the last character in the array as a NUL.
		 * This is the difference between the regular strncpy routine.
		 * strncpy doesn't guarantee that your new string will have a
		 * NUL terminator, but this routine does.
		 */
		for (i=1; i<n; i++) {
			if ((*d++ = *s++) == 0) {
#if (STRN_ZERO_PAD == 1)
				/* Pad with zeros. */
				for (; i<n; i++)
					*d++ = 0;
#endif	/* STRN_ZERO_PAD */
				return dst;
			}
		}
		/* If we get here, then we have a full string, with n - 1 characters,
		 * so now we NUL terminate it and go home.
		 */
		*d = 0;
	}
	return (dst);
}