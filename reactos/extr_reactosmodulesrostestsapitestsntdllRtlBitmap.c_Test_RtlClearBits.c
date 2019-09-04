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
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 

void
Test_RtlClearBits(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;
    ULONG BufferSize = 2 * sizeof(*Buffer);

    Buffer = AllocateGuarded(BufferSize);
    RtlInitializeBitMap(&BitMapHeader, Buffer, 19);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 0, 0);
    ok_hex(Buffer[0], 0xffffffff);
    ok_hex(Buffer[1], 0xffffffff);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 0, 1);
    ok_hex(Buffer[0], 0xfffffffe);
    ok_hex(Buffer[1], 0xffffffff);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 21, 1);
    ok_hex(Buffer[0], 0xffdfffff);
    ok_hex(Buffer[1], 0xffffffff);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 7, 9);
    ok_hex(Buffer[0], 0xffff007f);
    ok_hex(Buffer[1], 0xffffffff);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 13, 22);
    ok_hex(Buffer[0], 0x00001fff);
    ok_hex(Buffer[1], 0xfffffff8);

    memset(Buffer, 0xff, BufferSize);
    RtlClearBits(&BitMapHeader, 63, 1);
    ok_hex(Buffer[0], 0xffffffff);
    ok_hex(Buffer[1], 0x7fffffff);

    memset(Buffer, 0xcc, BufferSize);
    RtlClearBits(&BitMapHeader, 3, 6);
    RtlClearBits(&BitMapHeader, 11, 5);
    RtlClearBits(&BitMapHeader, 21, 7);
    RtlClearBits(&BitMapHeader, 37, 4);
    ok_hex(Buffer[0], 0xc00c0404);
    ok_hex(Buffer[1], 0xcccccc0c);
    FreeGuarded(Buffer);
}