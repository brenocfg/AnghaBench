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
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtAllocateVirtualMemory (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 scalar_t__ NtFreeVirtualMemory (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  PAGE_ROUND_DOWN (scalar_t__) ; 
 scalar_t__ PAGE_ROUND_UP (scalar_t__) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static
VOID
MakeReadOnly(
    PVOID Pointer,
    SIZE_T SizeRequested)
{
    NTSTATUS Status;
    SIZE_T Size = PAGE_ROUND_UP(SizeRequested);
    PVOID VirtualMemory = (PVOID)PAGE_ROUND_DOWN((SIZE_T)Pointer);

    if (Size)
    {
        Status = NtAllocateVirtualMemory(NtCurrentProcess(), &VirtualMemory, 0, &Size, MEM_COMMIT, PAGE_READWRITE);
        if (!NT_SUCCESS(Status))
        {
            Size = 0;
            Status = NtFreeVirtualMemory(NtCurrentProcess(), &VirtualMemory, &Size, MEM_RELEASE);
            ok(Status == STATUS_SUCCESS, "Status = %lx\n", Status);
        }
    }
}