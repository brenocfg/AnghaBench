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

__attribute__((used)) static inline short M16(short l, short r)
{
    int	sum = l + r;

    /* clip sum to saturation */
    if (sum > 32767)
        sum = 32767;
    else if (sum < -32768)
        sum = -32768;

    return sum;
}