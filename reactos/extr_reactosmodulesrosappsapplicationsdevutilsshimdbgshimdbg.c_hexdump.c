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
 int /*<<< orphan*/  xprintf (char*,...) ; 

void hexdump(unsigned char *p, unsigned int len)
{
    unsigned char *line = p;
    unsigned int i, thisline, offset = 0;

    while (offset < len)
    {
        xprintf("%04x ", offset);
        thisline = len - offset;
        if (thisline > 16)
            thisline = 16;

        for (i = 0; i < thisline; i++)
            xprintf("%02x ", line[i]);

        for (; i < 16; i++)
            xprintf("   ");

        for (i = 0; i < thisline; i++)
            xprintf("%c", (line[i] >= 0x20 && line[i] < 0x7f) ? line[i] : '.');

        xprintf("\n");
        offset += thisline;
        line += thisline;
    }
}