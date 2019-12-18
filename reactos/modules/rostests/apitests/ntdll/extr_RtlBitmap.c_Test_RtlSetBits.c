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
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 

void
Test_RtlSetBits(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;
    ULONG BufferSize = 2 * sizeof(*Buffer);

    Buffer = AllocateGuarded(BufferSize);
    RtlInitializeBitMap(&BitMapHeader, Buffer, 19);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 0, 0);
    ok_hex(Buffer[0], 0x00000000);
    ok_hex(Buffer[1], 0x00000000);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 0, 1);
    ok_hex(Buffer[0], 0x00000001);
    ok_hex(Buffer[1], 0x00000000);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 21, 1);
    ok_hex(Buffer[0], 0x00200000);
    ok_hex(Buffer[1], 0x00000000);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 7, 9);
    ok_hex(Buffer[0], 0x0000ff80);
    ok_hex(Buffer[1], 0x00000000);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 13, 22);
    ok_hex(Buffer[0], 0xffffe000);
    ok_hex(Buffer[1], 0x00000007);

    memset(Buffer, 0x00, BufferSize);
    RtlSetBits(&BitMapHeader, 63, 1);
    ok_hex(Buffer[0], 0x00000000);
    ok_hex(Buffer[1], 0x80000000);

    memset(Buffer, 0xcc, BufferSize);
    RtlSetBits(&BitMapHeader, 3, 6);
    RtlSetBits(&BitMapHeader, 11, 5);
    RtlSetBits(&BitMapHeader, 21, 7);
    RtlSetBits(&BitMapHeader, 37, 4);
    ok_hex(Buffer[0], 0xcfecfdfc);
    ok_hex(Buffer[1], 0xcccccdec);
    FreeGuarded(Buffer);
}