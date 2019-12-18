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

__attribute__((used)) static unsigned int LongSwap(unsigned int i)
{
    unsigned char b1, b2, b3, b4;
    b1 = i & 255;
    b2 = (i >> 8) & 255;
    b3 = (i >> 16) & 255;
    b4 = (i >> 24) & 255;
    return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}