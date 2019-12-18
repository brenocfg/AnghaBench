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
 scalar_t__ sscanf (char*,char*,unsigned int*) ; 

void
URLCopyToken(char *dst, size_t dsize, const char *src, size_t howmuch)
{
	char *dlim;
	const char *slim;
	unsigned int hc;
	int c;
	char h[4];

	dlim = dst + dsize - 1;		/* leave room for \0 */
	slim = src + howmuch;
	while (src < slim) {
		c = *src++;
		if (c == '\0')
			break;
		if (c == '%') {
			/* hex representation */
			if (src < slim + 2) {
				h[0] = *src++;
				h[1] = *src++;
				h[2] = '\0';
				hc = 0xeeff;
				if ((sscanf(h, "%x", &hc) >= 0) && (hc != 0xeeff)) {
					if (dst < dlim) {
						*(unsigned char *)dst = (unsigned char) hc;
						dst++;
					}
				}
			} else {
				break;
			}
		} else {
			*dst++ = (char) c;
		}
	}
	*dst = '\0';
}