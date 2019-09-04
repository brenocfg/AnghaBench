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
 int /*<<< orphan*/  RtlFindSetBitsAndClear (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 

void
Test_RtlFindSetBitsAndClear(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;

    Buffer = AllocateGuarded(2 * sizeof(*Buffer));
    Buffer[0] = 0xF9F078B2;
    Buffer[1] = 0x3F303F30;

    RtlInitializeBitMap(&BitMapHeader, Buffer, 0);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 0, 0), 0);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 0, 3), 0);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 1, 0), -1);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 1, 1), -1);
    ok_hex(Buffer[0], 0xF9F078B2);

    Buffer[0] = 0xF9F078B2;
    RtlInitializeBitMap(&BitMapHeader, Buffer, 8);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 1, 0), 1);
    ok_hex(Buffer[0], 0xf9f078b0);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 1, 1), 4);
    ok_hex(Buffer[0], 0xf9f078a0);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 1, 2), 5);
    ok_hex(Buffer[0], 0xf9f07880);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 2, 0), -1);
    ok_hex(Buffer[0], 0xf9f07880);

    Buffer[0] = 0xF9F078B2;
    RtlInitializeBitMap(&BitMapHeader, Buffer, 32);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 4, 0), 11);
    ok_hex(Buffer[0], 0xf9f000b2);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 5, 0), 20);
    ok_hex(Buffer[0], 0xf80000b2);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 4, 11), 27);
    ok_hex(Buffer[0], 0x800000b2);

    Buffer[0] = 0xF9F078B2;
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 4, 12), 20);
    ok_hex(Buffer[0], 0xf90078b2);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 2, 11), 11);
    ok_hex(Buffer[0], 0xf90060b2);
    ok_int(RtlFindSetBitsAndClear(&BitMapHeader, 2, 12), 13);
    ok_hex(Buffer[0], 0xf90000b2);
    FreeGuarded(Buffer);
}