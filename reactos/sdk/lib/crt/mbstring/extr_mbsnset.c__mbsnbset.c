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

unsigned char * _mbsnbset(unsigned char *src, unsigned int val, size_t count)
{
	unsigned char *char_src = (unsigned char *)src;
	unsigned short *short_src = (unsigned short *)src;

	if ( _mbclen2(val) == 1 ) {

		while(count > 0) {
			*char_src = val;
			char_src++;
			count--;
		}
		*char_src = 0;
	}
	else {
		while(count > 0) {
			*short_src = val;
			short_src++;
			count-=2;
		}
		*short_src = 0;
	}

	return src;
}