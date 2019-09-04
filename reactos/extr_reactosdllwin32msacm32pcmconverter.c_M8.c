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

__attribute__((used)) static inline unsigned char M8(unsigned char a, unsigned char b)
{
    int l = a - 128;
    int r = b - 128;
    int	sum = (l + r) + 128;

    /* clip sum to saturation */
    if (sum > 0xff)
        sum = 0xff;
    else if (sum < 0)
        sum = 0;

    return sum;
}