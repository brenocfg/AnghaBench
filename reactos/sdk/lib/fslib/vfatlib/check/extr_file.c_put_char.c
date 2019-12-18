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
 scalar_t__ dos_char_to_printable (char**,unsigned char) ; 

__attribute__((used)) static void put_char(char **p, unsigned char c)
{
#ifndef __REACTOS__
    if (dos_char_to_printable(p, c))
	return;
#endif
    if ((c >= ' ' && c < 0x7f) || c >= 0xa0)
	*(*p)++ = c;
    else {
	*(*p)++ = '\\';
	*(*p)++ = '0' + (c >> 6);
	*(*p)++ = '0' + ((c >> 3) & 7);
	*(*p)++ = '0' + (c & 7);
    }
}