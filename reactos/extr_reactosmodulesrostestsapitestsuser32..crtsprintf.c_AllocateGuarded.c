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
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtAllocateVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 scalar_t__ NtFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 scalar_t__ PAGE_ROUND_UP (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static
PVOID
AllocateGuarded(
    SIZE_T SizeRequested)
{
    NTSTATUS Status;
    SIZE_T Size = PAGE_ROUND_UP(SizeRequested + PAGE_SIZE);
    PVOID VirtualMemory = NULL;
    PCHAR StartOfBuffer;

    Status = NtAllocateVirtualMemory(NtCurrentProcess(), &VirtualMemory, 0, &Size, MEM_RESERVE, PAGE_NOACCESS);

    if (!NT_SUCCESS(Status))
        return NULL;

    Size -= PAGE_SIZE;
    if (Size)
    {
        Status = NtAllocateVirtualMemory(NtCurrentProcess(), &VirtualMemory, 0, &Size, MEM_COMMIT, PAGE_READWRITE);
        if (!NT_SUCCESS(Status))
        {
            Size = 0;
            Status = NtFreeVirtualMemory(NtCurrentProcess(), &VirtualMemory, &Size, MEM_RELEASE);
            ok(Status == STATUS_SUCCESS, "Status = %lx\n", Status);
            return NULL;
        }
    }

    StartOfBuffer = VirtualMemory;
    StartOfBuffer += Size - SizeRequested;

    return StartOfBuffer;
}