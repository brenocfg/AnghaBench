#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Protect; int /*<<< orphan*/  State; int /*<<< orphan*/  RegionSize; int /*<<< orphan*/  AllocationProtect; int /*<<< orphan*/  BaseAddress; int /*<<< orphan*/  AllocationBase; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  MemoryBasicInfo ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;

/* Variables and functions */
 char* LastStackAllocation ; 
 scalar_t__ MEM_COMMIT ; 
 scalar_t__ MEM_PRIVATE ; 
 int /*<<< orphan*/  MemoryBasicInformation ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtQueryVirtualMemory (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_READWRITE ; 
 scalar_t__ PAGE_ROUND_DOWN (char*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ StackAllocationBase ; 
 scalar_t__ StackSize ; 
 int /*<<< orphan*/  iteration ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ptr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
infinite_recursive(void)
{
    MEMORY_BASIC_INFORMATION MemoryBasicInfo;
    NTSTATUS Status;
    char Buffer[0x500];

    sprintf(Buffer, "Iteration %d.\n", iteration++);

    Status = NtQueryVirtualMemory(
        NtCurrentProcess(),
        &Buffer[0],
        MemoryBasicInformation,
        &MemoryBasicInfo,
        sizeof(MemoryBasicInfo),
        NULL);
    ok_ntstatus(Status, STATUS_SUCCESS);
    /* This never changes */
    ok_ptr(MemoryBasicInfo.AllocationBase, StackAllocationBase);
    /* Stack is committed one page at a time */
    ok_ptr(MemoryBasicInfo.BaseAddress, (PVOID)PAGE_ROUND_DOWN(&Buffer[0]));
    /* This is the protection of the memory when it was reserved. */
    ok_long(MemoryBasicInfo.AllocationProtect, PAGE_READWRITE);
    /* Windows commits the whole used stack at once, +2 pages. */
#if 0
    ok_long(MemoryBasicInfo.RegionSize, ((ULONG_PTR)StackAllocationBase + StackSize + 2* PAGE_SIZE) - PAGE_ROUND_DOWN(&Buffer[0]));
#endif
    /* This is the state of the queried address */
    ok_long(MemoryBasicInfo.State, MEM_COMMIT);
    /* This is the protection of the queried address */
    ok_long(MemoryBasicInfo.Protect, PAGE_READWRITE);
    /* Of course this is private memory. */
    ok_long(MemoryBasicInfo.Type, MEM_PRIVATE);

    LastStackAllocation = &Buffer[-0x500];

    infinite_recursive();
}