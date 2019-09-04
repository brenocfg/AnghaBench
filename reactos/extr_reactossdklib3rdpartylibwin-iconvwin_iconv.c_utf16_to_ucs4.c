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

__attribute__((used)) static uint
utf16_to_ucs4(const ushort *wbuf)
{
    uint wc = wbuf[0];
    if (0xD800 <= wbuf[0] && wbuf[0] <= 0xDBFF)
        wc = ((wbuf[0] & 0x3FF) << 10) + (wbuf[1] & 0x3FF) + 0x10000;
    return wc;
}