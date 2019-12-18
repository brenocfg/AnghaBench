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
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CheckBuffer (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  RtlFillMemory (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 scalar_t__ RtlReAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RtlSizeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok_hex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOLEAN
ReAllocBuffer(
    PUCHAR *Buffer,
    SIZE_T Size,
    SIZE_T *OldSizePtr,
    PCSTR Action)
{
    PUCHAR NewBuffer;
    SIZE_T OldSize = *OldSizePtr;

    RtlFillMemory(*Buffer, OldSize, 0x7a);
    NewBuffer = RtlReAllocateHeap(RtlGetProcessHeap(),
                                  HEAP_ZERO_MEMORY,
                                  *Buffer,
                                  Size);
    if (!NewBuffer)
    {
        skip("RtlReAllocateHeap failed for size %lu (%s)\n", Size, Action);
        return FALSE;
    }
    *Buffer = NewBuffer;
    ok_hex(RtlSizeHeap(RtlGetProcessHeap(), 0, NewBuffer), Size);
    if (OldSize < Size)
    {
        ok(CheckBuffer(NewBuffer, OldSize, 0x7a), "CheckBuffer failed at size 0x%lx -> 0x%lx\n", OldSize, Size);
        ok(CheckBuffer(NewBuffer + OldSize, Size - OldSize, 0), "HEAP_ZERO_MEMORY not respected for 0x%lx -> 0x%lx\n", OldSize, Size);
    }
    else
    {
        ok(CheckBuffer(NewBuffer, Size, 0x7a), "CheckBuffer failed at size 0x%lx -> 0x%lx\n", OldSize, Size);
    }
    *OldSizePtr = Size;
    return TRUE;
}