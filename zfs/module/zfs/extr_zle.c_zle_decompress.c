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
typedef  int /*<<< orphan*/  uchar_t ;

/* Variables and functions */

int
zle_decompress(void *s_start, void *d_start, size_t s_len, size_t d_len, int n)
{
	uchar_t *src = s_start;
	uchar_t *dst = d_start;
	uchar_t *s_end = src + s_len;
	uchar_t *d_end = dst + d_len;

	while (src < s_end && dst < d_end) {
		int len = 1 + *src++;
		if (len <= n) {
			if (src + len > s_end || dst + len > d_end)
				return (-1);
			while (len-- != 0)
				*dst++ = *src++;
		} else {
			len -= n;
			if (dst + len > d_end)
				return (-1);
			while (len-- != 0)
				*dst++ = 0;
		}
	}
	return (dst == d_end ? 0 : -1);
}