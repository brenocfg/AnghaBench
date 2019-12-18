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
 int /*<<< orphan*/  FreeGuarded (int*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  RtlNumberOfClearBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 

void
Test_RtlNumberOfClearBits(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;

    Buffer = AllocateGuarded(2 * sizeof(*Buffer));
    Buffer[0] = 0xff00fff0;
    Buffer[1] = 0x3F303F30;

    RtlInitializeBitMap(&BitMapHeader, Buffer, 0);
    ok_int(RtlNumberOfClearBits(&BitMapHeader), 0);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 4);
    ok_int(RtlNumberOfClearBits(&BitMapHeader), 4);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 31);
    ok_int(RtlNumberOfClearBits(&BitMapHeader), 12);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 56);
    ok_int(RtlNumberOfClearBits(&BitMapHeader), 26);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 64);
    ok_int(RtlNumberOfClearBits(&BitMapHeader), 28);
    FreeGuarded(Buffer);
}