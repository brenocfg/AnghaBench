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
typedef  int SIZE_T ;
typedef  int* PVOID ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtAllocateVirtualMemory (int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFreeVirtualMemory (int /*<<< orphan*/ ,int**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtProtectVirtualMemory (int /*<<< orphan*/ ,int**,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int,int*) ; 
 int /*<<< orphan*/  ok_hex (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
TestFreeNoAccess(void)
{
    PVOID Mem;
    SIZE_T Size;
    NTSTATUS Status;
    ULONG Iteration, PageNumber;
    PUCHAR Page;
    ULONG OldProtection;

    for (Iteration = 0; Iteration < 50000; Iteration++)
    {
        Mem = NULL;
        Size = 16 * PAGE_SIZE;
        Status = NtAllocateVirtualMemory(NtCurrentProcess(),
                                         &Mem,
                                         0,
                                         &Size,
                                         MEM_COMMIT,
                                         PAGE_READWRITE);
        ok_ntstatus(Status, STATUS_SUCCESS);
        if (!NT_SUCCESS(Status))
        {
            break;
        }

        for (PageNumber = 0; PageNumber < 16; PageNumber++)
        {
            Page = Mem;
            Page += PageNumber * PAGE_SIZE;
            ok(*Page == 0,
               "[%lu, %lu] Got non-zero memory. %x at %p\n",
               Iteration, PageNumber, *Page, Page);
            *Page = 123;
        }

        Status = NtProtectVirtualMemory(NtCurrentProcess(),
                                        &Mem,
                                        &Size,
                                        PAGE_NOACCESS,
                                        &OldProtection);
        ok_ntstatus(Status, STATUS_SUCCESS);
        ok_hex(OldProtection, PAGE_READWRITE);

        Size = 0;
        Status = NtFreeVirtualMemory(NtCurrentProcess(),
                                     &Mem,
                                     &Size,
                                     MEM_RELEASE);
        ok_ntstatus(Status, STATUS_SUCCESS);
    }
}