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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int
delta_compression(unsigned char *curr, unsigned char *prev, unsigned char *comp, int ds, int space)
{
	int left = space;
	int x = ds;

	while (x > 0)
	{
		/* Count matching bytes */
		int match = 0;
		int diff = 0;
		while (x > 0 && *curr == *prev)
		{
			curr++;
			prev++;
			match++;
			x--;
		}

		/* Count different bytes */
		while (x > 0 && *curr != *prev)
		{
			curr++;
			prev++;
			diff++;
			x--;
		}

		while (diff > 0)
		{
			int exts;
			int mini_diff = diff;
			if (mini_diff > 8)
				mini_diff = 8;

			exts = (match+255-31)/255;
			left -= 1 + mini_diff + exts;
			if (left < 0)
				return 0;
			*comp++ = ((mini_diff-1)<<5) | (match < 31 ? match : 31);
			if (exts > 0)
			{
				match -= 31;
				while (--exts)
				{
					*comp++ = 255;
					match -= 255;
				}
				*comp++ = match;
			}
			memcpy(comp, curr-diff, mini_diff);
			comp += mini_diff;

			match = 0;
			diff -= mini_diff;
		}
	}
	return space - left;
}