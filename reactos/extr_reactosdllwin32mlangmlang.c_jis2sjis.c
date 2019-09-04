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

__attribute__((used)) static inline void jis2sjis(unsigned char *p1, unsigned char *p2)
{
    unsigned char c1 = *p1;
    unsigned char c2 = *p2;
    int row = c1 < 95 ? 112 : 176;
    int cell = c1 % 2 ? 31 + (c2 > 95) : 126;

    *p1 = ((c1 + 1) >> 1) + row;
    *p2 = c2 + cell;
}