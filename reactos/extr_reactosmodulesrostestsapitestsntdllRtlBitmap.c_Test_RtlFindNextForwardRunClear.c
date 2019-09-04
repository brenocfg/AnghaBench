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
 int RtlFindNextForwardRunClear (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 

void
Test_RtlFindNextForwardRunClear(void)
{
    RTL_BITMAP BitMapHeader;
    ULONG *Buffer;
    ULONG Index;

    Buffer = AllocateGuarded(2 * sizeof(*Buffer));
    Buffer[0] = 0xF9F078B2;
    Buffer[1] = 0x3F303F30;

    RtlInitializeBitMap(&BitMapHeader, Buffer, 0);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 0, &Index), 0);
    ok_int(Index, 0);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 1, &Index), 0);
    ok_int(Index, 1);

    Index = -1;
    RtlInitializeBitMap(&BitMapHeader, Buffer, 8);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 0, &Index), 1);
    ok_int(Index, 0);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 1, &Index), 2);
    ok_int(Index, 2);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 7, &Index), 0);
    ok_int(Index, 8);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 17, &Index), 0);
    ok_int(Index, 17);
    ok_int(RtlFindNextForwardRunClear(&BitMapHeader, 39, &Index), 0);
    ok_int(Index, 39);
    FreeGuarded(Buffer);
}