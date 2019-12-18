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
 int /*<<< orphan*/  PacketWriteChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hex ; 

int PacketWriteHexNumber(int hnum, int dig)
{
    int i;
    hnum <<= (8 - dig) * 4;
    for (i = 0; i < dig; i++)
    {
        PacketWriteChar(hex[(hnum >> 28) & 15]);
        hnum <<= 4;
    }
    return i;
}