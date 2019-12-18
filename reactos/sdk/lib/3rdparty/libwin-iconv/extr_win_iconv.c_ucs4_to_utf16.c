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
typedef  int ushort ;
typedef  int uint ;

/* Variables and functions */

__attribute__((used)) static void
ucs4_to_utf16(uint wc, ushort *wbuf, int *wbufsize)
{
    if (wc < 0x10000)
    {
        wbuf[0] = wc;
        *wbufsize = 1;
    }
    else
    {
        wc -= 0x10000;
        wbuf[0] = 0xD800 | ((wc >> 10) & 0x3FF);
        wbuf[1] = 0xDC00 | (wc & 0x3FF);
        *wbufsize = 2;
    }
}