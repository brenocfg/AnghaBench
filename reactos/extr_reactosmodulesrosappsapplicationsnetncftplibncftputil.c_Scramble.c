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
 size_t strlen (char*) ; 

void
Scramble(unsigned char *dst, size_t dsize, unsigned char *src, char *key)
{
	int i;
	unsigned int ch;
	unsigned char *k2;
	size_t keyLen;

	keyLen = strlen(key);
	k2 = (unsigned char *) key;
	for (i=0; i < (int) dsize - 1; i++) {
		ch = src[i];
		if (ch == 0)
			break;
		dst[i] = (unsigned char) (ch ^ (int) (k2[i % (int) keyLen]));
	}
	dst[i] = '\0';
}