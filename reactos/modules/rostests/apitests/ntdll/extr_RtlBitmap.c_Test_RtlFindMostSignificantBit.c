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
 int /*<<< orphan*/  RtlFindMostSignificantBit (int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 

void
Test_RtlFindMostSignificantBit(void)
{
    ok_int(RtlFindMostSignificantBit(0), -1);

    ok_int(RtlFindMostSignificantBit(0x0000000000000001ULL), 0);
    ok_int(RtlFindMostSignificantBit(0x0000000000000002ULL), 1);
    ok_int(RtlFindMostSignificantBit(0x1000000000000000ULL), 60);
    ok_int(RtlFindMostSignificantBit(0x8000000000000000ULL), 63);
    ok_int(RtlFindMostSignificantBit(0x8000000000000001ULL), 63);
    ok_int(RtlFindMostSignificantBit(0xFFFFFFFFFFFFFFFFULL), 63);
    ok_int(RtlFindMostSignificantBit(0x0000000070000000ULL), 30);
}