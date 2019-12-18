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
typedef  scalar_t__ PVOID ;
typedef  scalar_t__* PSIZE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ Allocate (scalar_t__) ; 
 int /*<<< orphan*/  Free (scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static
PVOID
ReAllocate(
    PVOID OldUserBuffer,
    SIZE_T NewDataSize)
{
    PVOID NewUserBuffer;
    SIZE_T OldDataSize;

    OldDataSize = ((PSIZE_T)OldUserBuffer)[-1];
    ASSERT(OldDataSize != 0);

    NewUserBuffer = Allocate(NewDataSize);
    ASSERT(((PSIZE_T)OldUserBuffer)[-1] == OldDataSize);
    RtlCopyMemory(NewUserBuffer, OldUserBuffer, min(OldDataSize, NewDataSize));
    ASSERT(((PSIZE_T)OldUserBuffer)[-1] == OldDataSize);
    Free(OldUserBuffer);
    return NewUserBuffer;
}