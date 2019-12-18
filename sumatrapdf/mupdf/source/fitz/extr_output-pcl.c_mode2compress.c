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
mode2compress(unsigned char *out, const unsigned char *in, int in_len)
{
	int x;
	int out_len = 0;
	int run;

	for (x = 0; x < in_len; x += run)
	{
		/* How far do we have to look to find a value that isn't repeated? */
		for (run = 1; run < 127 && x+run < in_len; run++)
			if (in[0] != in[run])
				break;
		if (run > 1)
		{
			/* We have a run of matching bytes */
			out[out_len++] = 257-run;
			out[out_len++] = in[0];
		}
		else
		{
			/* Now copy as many literals as possible. We only
			 * break the run at a length of 127, at the end,
			 * or where we have 3 repeated values. */
			int i;

			/* How many literals do we need to copy? */
			for (; run < 127 && x+run+2 < in_len; run++)
				if (in[run] == in[run+1] && in[run] == in[run+2])
					break;
			/* Don't leave stragglers at the end */
			if (x + run + 2 >= in_len)
			{
				run = in_len - x;
				if (run > 127)
					run = 127;
			}
			out[out_len++] = run-1;
			for (i = 0; i < run; i++)
			{
				out[out_len++] = in[i];
			}
		}
		in += run;
	}

	return out_len;
}