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
typedef  int /*<<< orphan*/  bases ;
typedef  size_t ULONG ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CheckBufferReadWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 size_t RTL_NUMBER_OF (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TestString ; 
 int /*<<< orphan*/  TestStringSize ; 
 int /*<<< orphan*/  ZwAllocateVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static
NTSTATUS
StressTesting(ULONG AllocationType)
{
    NTSTATUS Status = STATUS_SUCCESS;
    NTSTATUS ReturnStatus = STATUS_SUCCESS;
    static PVOID bases[1024]; //assume we are going to allocate only 5 gigs. static here means the arrays is not allocated on the stack but in the BSS segment of the driver
    ULONG Index = 0;
    PVOID Base = NULL;
    SIZE_T RegionSize = 5 * 1024 * 1024; // 5 megabytes;

    RtlZeroMemory(bases, sizeof(bases));

    for (Index = 0; Index < RTL_NUMBER_OF(bases) && NT_SUCCESS(Status); Index++)
    {
        Status = ZwAllocateVirtualMemory(NtCurrentProcess(), &Base, 0, &RegionSize, AllocationType, PAGE_READWRITE);

        bases[Index] = Base;
        if ((Index % 10) == 0)
        {
            if (AllocationType == MEM_COMMIT && NT_SUCCESS(Status))
            {
                CheckBufferReadWrite(Base, TestString, TestStringSize, STATUS_SUCCESS);
            }
            else
            {
                CheckBufferReadWrite(Base, TestString, TestStringSize, STATUS_ACCESS_VIOLATION);
            }
        }

        Base = NULL;
    }

    trace("Finished reserving. Error code %x. Chunks allocated: %d\n", Status, Index );

    ReturnStatus = Status;

    //free the allocated memory so that we can continue with the tests
    Status = STATUS_SUCCESS;
    Index = 0;
    while (NT_SUCCESS(Status) && Index < RTL_NUMBER_OF(bases))
    {
        RegionSize = 0;
        Status = ZwFreeVirtualMemory(NtCurrentProcess(), &bases[Index], &RegionSize, MEM_RELEASE);
        bases[Index++] = NULL;
    }

    return ReturnStatus;
}