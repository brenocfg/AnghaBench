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
 int _mbclen2 (unsigned int) ; 

unsigned char * _mbsset(unsigned char *src, unsigned int c)
{
	unsigned char *char_src = src;
	unsigned short *short_src = (unsigned short *)src;

	if ( _mbclen2(c) == 1 ) {

		while(*char_src != 0) {
			*char_src = c;
			char_src++;
		}
		*char_src = 0;
	}
	else {
		while(*short_src != 0) {
			*short_src = c;
			short_src++;
		}
		*short_src = 0;
	}

	return src;
}