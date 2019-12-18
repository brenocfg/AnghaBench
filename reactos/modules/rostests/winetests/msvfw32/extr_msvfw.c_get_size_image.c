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
typedef  int WORD ;
typedef  int LONG ;
typedef  int DWORD ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static DWORD get_size_image(LONG width, LONG height, WORD depth)
{
    DWORD ret = width * depth;
    ret = (ret + 7) / 8;    /* divide by byte size, rounding up */
    ret = (ret + 3) & ~3;   /* align to 4 bytes */
    ret *= abs(height);
    return ret;
}