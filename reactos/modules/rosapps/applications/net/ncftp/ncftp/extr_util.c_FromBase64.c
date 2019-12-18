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
 scalar_t__* B64DecodeTable ; 

void
FromBase64(void *dst0, const void *src0, size_t n, int terminate)
{
	unsigned char *dst;
	const unsigned char *src, *srclim;
	unsigned int c0, c1, c2, c3;
	unsigned int ch;

	src = src0;
	srclim = src + n;
	dst = dst0;

	while (src < srclim) {
		c0 = *src++;
		if (src < srclim) {
			c1 = *src++;
		} else {
			c1 = 0;
		}
		if (src < srclim) {
			c2 = *src++;
		} else {
			c2 = 0;
		}
		if (src < srclim) {
			c3 = *src++;
		} else {
			c3 = 0;
		}

		ch = (((unsigned int) B64DecodeTable[c0]) << 2) | (((unsigned int) B64DecodeTable[c1]) >> 4);
		dst[0] = (unsigned char) ch;

		ch = (((unsigned int) B64DecodeTable[c1]) << 4) | (((unsigned int) B64DecodeTable[c2]) >> 2);
		dst[1] = (unsigned char) ch;

		ch = (((unsigned int) B64DecodeTable[c2]) << 6) | (((unsigned int) B64DecodeTable[c3]));
		dst[2] = (unsigned char) ch;

		dst += 3;
	}
	if (terminate != 0)
		*dst = '\0';
}