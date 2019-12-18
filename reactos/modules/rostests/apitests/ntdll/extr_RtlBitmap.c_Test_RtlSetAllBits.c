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
 int /*<<< orphan*/  RtlSetAllBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 

void
Test_RtlSetAllBits(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;
    ULONG BufferSize = 2 * sizeof(*Buffer);

    Buffer = AllocateGuarded(BufferSize);
    RtlInitializeBitMap(&BitMapHeader, Buffer, 19);
    memset(Buffer, 0xcc, BufferSize);
    RtlSetAllBits(&BitMapHeader);
    ok_hex(Buffer[0], 0xffffffff);
    ok_hex(Buffer[1], 0xcccccccc);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 0);
    memset(Buffer, 0xcc, BufferSize);
    RtlSetAllBits(&BitMapHeader);
    ok_hex(Buffer[0], 0xcccccccc);
    ok_hex(Buffer[1], 0xcccccccc);

    RtlInitializeBitMap(&BitMapHeader, Buffer, 64);
    memset(Buffer, 0xcc, BufferSize);
    RtlSetAllBits(&BitMapHeader);
    ok_hex(Buffer[0], 0xffffffff);
    ok_hex(Buffer[1], 0xffffffff);
    FreeGuarded(Buffer);
}