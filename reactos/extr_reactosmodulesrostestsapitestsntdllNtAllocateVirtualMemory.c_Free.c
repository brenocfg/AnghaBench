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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  scalar_t__* PSIZE_T ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ ** Allocations ; 
 size_t CurrentAllocation ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 scalar_t__ NtFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  RtlFillMemory (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ValidateAllocations () ; 

__attribute__((used)) static
VOID
Free(
    PVOID UserBuffer)
{
    NTSTATUS Status;
    PVOID AllocationStart;
    SIZE_T Zero = 0;
    SIZE_T AllocationSize;
    SIZE_T DataSize;
    ULONG i;

    AllocationSize = ((PSIZE_T)UserBuffer)[-2];
    DataSize = ((PSIZE_T)UserBuffer)[-1];
    ASSERT(DataSize != 0);

    AllocationStart = (PUCHAR)UserBuffer + DataSize + PAGE_SIZE - AllocationSize;
    ASSERT((SIZE_T)AllocationStart % PAGE_SIZE == 0);

    RtlFillMemory(UserBuffer, DataSize, 0xbe);
    ((PSIZE_T)UserBuffer)[-1] = 0;
    ((PSIZE_T)UserBuffer)[-2] = 0xFAFBFCFD;

    for (i = 0; i < CurrentAllocation; ++i)
        if (Allocations[i] == UserBuffer)
        {
            Allocations[i] = NULL;
            break;
        }
    ValidateAllocations();

    Status = NtFreeVirtualMemory(NtCurrentProcess(), &AllocationStart, &Zero, MEM_RELEASE);
    ASSERT(Status == STATUS_SUCCESS);
}