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
mode3compress(unsigned char *out, const unsigned char *in, unsigned char *prev, int in_len)
{
	unsigned char *compressed = out;
	const unsigned char *cur = in;
	const unsigned char *end = in + in_len;

	while (cur < end) {		/* Detect a maximum run of unchanged bytes. */
		const unsigned char *run = cur;
		const unsigned char *diff;
		const unsigned char *stop;
		int offset, cbyte;

		while (cur < end && *cur == *prev) {
			cur++, prev++;
		}
		if (cur == end)
			break;		/* rest of row is unchanged */
		/* Detect a run of up to 8 changed bytes. */
		/* We know that *cur != *prev. */
		diff = cur;
		stop = (end - cur > 8 ? cur + 8 : end);
		do
		{
			*prev++ = *cur++;
		}
		while (cur < stop && *cur != *prev);
		/* Now [run..diff) are unchanged, and */
		/* [diff..cur) are changed. */
		/* Generate the command byte(s). */
		offset = diff - run;
		cbyte = (cur - diff - 1) << 5;
		if (offset < 31)
			*out++ = cbyte + offset;
		else {
			*out++ = cbyte + 31;
			offset -= 31;
			while (offset >= 255)
				*out++ = 255, offset -= 255;
			*out++ = offset;
		}
		/* Copy the changed data. */
		while (diff < cur)
			*out++ = *diff++;
	}
	return out - compressed;
}