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
 int byteCounter ; 
 int leftMask ; 
 int rightMask ; 

void
get_masks(int x, int w)
{
    register int tmp;

    leftMask = rightMask = 0;
    byteCounter = w;
    /* right margin */
    tmp = (x+w) & 7;
    if (tmp)
    {
        byteCounter -= tmp;
        rightMask = (unsigned char)(0xff00 >> tmp);
    }
    /* left margin */
    tmp = x & 7;
    if (tmp)
    {
        byteCounter -= (8 - tmp);
        leftMask = (0xff >> tmp);
    }
    /* too small ? */
    if (byteCounter < 0)
    {
        leftMask &= rightMask;
        rightMask = 0;
        byteCounter = 0;
    }
    byteCounter /= 8;
}