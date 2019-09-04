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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;

/* Variables and functions */
 int* AllocateGuarded (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeGuarded (int*) ; 
 int /*<<< orphan*/  RtlAreBitsClear (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
Test_RtlAreBitsClear(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;

    Buffer = AllocateGuarded(2 * sizeof(*Buffer));
    RtlInitializeBitMap(&BitMapHeader, Buffer, 19);
    Buffer[0] = 0x00ff00ff;
    Buffer[1] = 0xc0cfc0cf;

    ok_hex(RtlAreBitsClear(&BitMapHeader, 0, 8), FALSE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 8, 8), TRUE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 7, 8), FALSE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 8, 9), FALSE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 24, 1), FALSE);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 31);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 24, 1), TRUE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 24, 7), TRUE);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 24, 8), FALSE);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 64);
    ok_hex(RtlAreBitsClear(&BitMapHeader, 60, 4), FALSE);
    FreeGuarded(Buffer);
}