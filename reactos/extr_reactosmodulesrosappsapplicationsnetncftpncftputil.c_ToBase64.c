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
 unsigned char* B64EncodeTable ; 

void
ToBase64(void *dst0, const void *src0, size_t n, int terminate)
{
	unsigned char *dst;
	const unsigned char *src, *srclim;
	unsigned int c0, c1, c2;
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

		ch = c0 >> 2;
		dst[0] = B64EncodeTable[ch & 077];

		ch = ((c0 << 4) & 060) | ((c1 >> 4) & 017);
		dst[1] = B64EncodeTable[ch & 077];

		ch = ((c1 << 2) & 074) | ((c2 >> 6) & 03);
		dst[2] = B64EncodeTable[ch & 077];

		ch = (c2 & 077);
		dst[3] = B64EncodeTable[ch & 077];

		dst += 4;
	}
	if (terminate != 0)
		*dst = '\0';
}