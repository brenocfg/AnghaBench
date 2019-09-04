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

__attribute__((used)) static inline unsigned int wined3d_popcount(unsigned int x)
{
#ifdef HAVE___BUILTIN_POPCOUNT
    return __builtin_popcount(x);
#else
    x -= x >> 1 & 0x55555555;
    x = (x & 0x33333333) + (x >> 2 & 0x33333333);
    return ((x + (x >> 4)) & 0x0f0f0f0f) * 0x01010101 >> 24;
#endif
}