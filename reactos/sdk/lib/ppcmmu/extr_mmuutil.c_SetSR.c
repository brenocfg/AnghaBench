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

inline void SetSR(int n, int val) {
    switch( n ) {
    case 0:
	__asm__("mtsr 0,%0" : : "r" (val));
	break;
    case 1:
	__asm__("mtsr 1,%0" : : "r" (val));
	break;
    case 2:
	__asm__("mtsr 2,%0" : : "r" (val));
	break;
    case 3:
	__asm__("mtsr 3,%0" : : "r" (val));
	break;
    case 4:
	__asm__("mtsr 4,%0" : : "r" (val));
	break;
    case 5:
	__asm__("mtsr 5,%0" : : "r" (val));
	break;
    case 6:
	__asm__("mtsr 6,%0" : : "r" (val));
	break;
    case 7:
	__asm__("mtsr 7,%0" : : "r" (val));
	break;
    case 8:
	__asm__("mtsr 8,%0" : : "r" (val));
	break;
    case 9:
	__asm__("mtsr 9,%0" : : "r" (val));
	break;
    case 10:
	__asm__("mtsr 10,%0" : : "r" (val));
	break;
    case 11:
	__asm__("mtsr 11,%0" : : "r" (val));
	break;
    case 12:
	__asm__("mtsr 12,%0" : : "r" (val));
	break;
    case 13:
	__asm__("mtsr 13,%0" : : "r" (val));
	break;
    case 14:
	__asm__("mtsr 14,%0" : : "r" (val));
	break;
    case 15:
	__asm__("mtsr 15,%0" : : "r" (val));
	break;
    }
}