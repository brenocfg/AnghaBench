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

inline int BatTranslate( int batu, int batl, int virt ) {
    int mask;
    if(batu & 0x3fc)
    {
	mask = ~(0x1ffff | ((batu & 0x3fc)>>2)<<17);
	if((batu & 2) && ((batu & mask) == (virt & mask)))
	    return (batl & mask) | (virt & ~mask);
    } else {
	mask = ~(0x1ffff | (batl << 17));
	if(!(batl & 0x40) || ((batu & mask) != (virt & mask)))
	    return (batl & mask) | (virt & ~mask);
    }
    return -1;
}