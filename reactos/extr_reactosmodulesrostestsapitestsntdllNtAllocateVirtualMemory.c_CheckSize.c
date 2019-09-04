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
typedef  int ULONG_PTR ;
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtAllocateVirtualMemory (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFreeVirtualMemory (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

VOID
CheckSize(ULONG_PTR Base, SIZE_T InSize, SIZE_T ExpectedSize)
{
    NTSTATUS Status;
    PVOID BaseAddress;
    SIZE_T Size;

    /* Reserve memory */
    BaseAddress = (PVOID)Base;
    Size = InSize;
    Status = NtAllocateVirtualMemory(NtCurrentProcess(),
                                     &BaseAddress,
                                     0,
                                     &Size,
                                     MEM_RESERVE,
                                     PAGE_NOACCESS);
    ok(NT_SUCCESS(Status), "NtAllocateVirtualMemory failed!\n");
    ok(BaseAddress == (PVOID)(Base & ~((ULONG_PTR)0xFFFF)), "Got back wrong base address: %p\n", BaseAddress);
    ok(Size == ExpectedSize, "Alloc of 0x%Ix: got back wrong size: 0x%Ix, expected 0x%Ix\n", InSize, Size, ExpectedSize);
    Status = NtFreeVirtualMemory(NtCurrentProcess(), &BaseAddress, &Size, MEM_RELEASE);
    ok(NT_SUCCESS(Status), "NtFreeVirtualMemory failed!\n");
}