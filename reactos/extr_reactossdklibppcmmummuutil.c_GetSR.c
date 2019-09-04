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

inline int GetSR(int n) {
    register int res = 0;
    switch( n ) {
    case 0:
	__asm__("mfsr %0,0" : "=r" (res));
	break;
    case 1:
	__asm__("mfsr %0,1" : "=r" (res));
	break;
    case 2:
	__asm__("mfsr %0,2" : "=r" (res));
	break;
    case 3:
	__asm__("mfsr %0,3" : "=r" (res));
	break;
    case 4:
	__asm__("mfsr %0,4" : "=r" (res));
	break;
    case 5:
	__asm__("mfsr %0,5" : "=r" (res));
	break;
    case 6:
	__asm__("mfsr %0,6" : "=r" (res));
	break;
    case 7:
	__asm__("mfsr %0,7" : "=r" (res));
	break;
    case 8:
	__asm__("mfsr %0,8" : "=r" (res));
	break;
    case 9:
	__asm__("mfsr %0,9" : "=r" (res));
	break;
    case 10:
	__asm__("mfsr %0,10" : "=r" (res));
	break;
    case 11:
	__asm__("mfsr %0,11" : "=r" (res));
	break;
    case 12:
	__asm__("mfsr %0,12" : "=r" (res));
	break;
    case 13:
	__asm__("mfsr %0,13" : "=r" (res));
	break;
    case 14:
	__asm__("mfsr %0,14" : "=r" (res));
	break;
    case 15:
	__asm__("mfsr %0,15" : "=r" (res));
	break;
    }
    return res;
}