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

__attribute__((used)) static void generate_tiff_palette(void *buf, unsigned count)
{
    unsigned short *r, *g, *b;
    unsigned i;

    r = buf;
    g = r + count;
    b = g + count;

    r[0] = 0x11 * 257;
    g[0] = 0x22 * 257;
    b[0] = 0x33 * 257;
    r[1] = 0x44 * 257;
    g[1] = 0x55 * 257;
    b[1] = 0x66 * 257;
    r[2] = 0x77 * 257;
    g[2] = 0x88 * 257;
    b[2] = 0x99 * 257;
    r[3] = 0xa1 * 257;
    g[3] = 0xb5 * 257;
    b[3] = 0xff * 257;

    for (i = 4; i < count; i++)
    {
        r[i] = i * 257;
        g[i] = (i | 0x40) * 257;
        b[i] = (i | 0x80) * 257;
    }
}