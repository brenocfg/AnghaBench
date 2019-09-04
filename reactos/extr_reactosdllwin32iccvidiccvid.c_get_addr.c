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
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static inline long get_addr(BOOL inverted, unsigned long x, unsigned long y,
                       int frm_stride, int bpp, unsigned int out_height)
{
    /* Returns the starting position of a line from top-down or bottom-up */
    if (inverted)
        return y * frm_stride + x * bpp;
    else
        return (out_height - 1 - y) * frm_stride + x * bpp;
}