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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
is_utf8(const char* src)
{
	uint8_t ch;
	size_t i;
	const uint8_t* s = (const uint8_t*) src;

	/* We make a loop over every character, until we find a null one.
	   Remember: The string is supposed to end with a NUL, so ahead checks are safe. */
	while ((ch = *s++))	{
		/* Ye olde 7bit ASCII chars 'rr fine for anything */
		if(ch < 0x80) continue;

		/* Now, we watch out for non-UTF conform sequences. */
		else if ((ch < 0xC2) || (ch > 0xFD))
			return 0;
		/* check for some misformed sequences */
		if (((ch == 0xC2) && (s[0] < 0xA0)) ||
		    ((ch == 0xEF) && (s[0] == 0xBF) && (s[1] > 0xBD)))
			/* XXX add more for outside the BMP */
			return 0;

		/* Check the continuation bytes. */
		if      (ch < 0xE0) i = 1;
		else if (ch < 0xF0) i = 2;
		else if (ch < 0xF8)	i = 3;
		else if (ch < 0xFC)	i = 4;
		else
			i = 5;

		while (i--)
			if ((*s++ & 0xC0) != 0x80)
				return 0;
	}

	/* If no check failed, the string indeed looks like valid UTF-8. */
	return 1;
}