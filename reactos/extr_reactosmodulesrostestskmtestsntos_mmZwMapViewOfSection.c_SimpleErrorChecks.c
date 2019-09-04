#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_4__ {int QuadPart; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int MEM_COMMIT ; 
 int MEM_LARGE_PAGES ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int MEM_RESERVE ; 
 int MM_ALLOCATION_GRANULARITY ; 
 scalar_t__ MmSystemRangeStart ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NtCurrentProcess () ; 
 int PAGE_EXECUTE ; 
 int PAGE_EXECUTE_READ ; 
 int PAGE_EXECUTE_WRITECOPY ; 
 int PAGE_NOACCESS ; 
 int PAGE_READONLY ; 
 int PAGE_READWRITE ; 
 int PAGE_WRITECOPY ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  STATUS_CONFLICTING_ADDRESSES ; 
 int /*<<< orphan*/  STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  STATUS_INVALID_PAGE_PROTECTION ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_3 ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_4 ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_5 ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_9 ; 
 int /*<<< orphan*/  STATUS_INVALID_VIEW_SIZE ; 
 int /*<<< orphan*/  STATUS_MAPPED_ALIGNMENT ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_OBJECT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  STATUS_SECTION_PROTECTION ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TestMapView (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int,TYPE_1__*,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TestStringSize ; 
 int /*<<< orphan*/  ViewUnmap ; 
 int /*<<< orphan*/  ZwAllocateVirtualMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwCreateSection (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwFreeVirtualMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_eq_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_eq_ulonglong (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
VOID
SimpleErrorChecks(HANDLE FileHandleReadOnly, HANDLE FileHandleWriteOnly, HANDLE ExecutableImg)
{
    NTSTATUS Status;
    HANDLE WriteSectionHandle;
    HANDLE ReadOnlySection;
    HANDLE PageFileSectionHandle;
    LARGE_INTEGER MaximumSize;
    LARGE_INTEGER SectionOffset;
    SIZE_T AllocSize = TestStringSize;
    SIZE_T ViewSize = 0;
    PVOID BaseAddress = NULL;
    PVOID AllocBase = NULL;
    MaximumSize.QuadPart = TestStringSize;

    //Used for parameters working on file-based section
    Status = ZwCreateSection(&WriteSectionHandle, SECTION_ALL_ACCESS, NULL, &MaximumSize, PAGE_READWRITE, SEC_COMMIT, FileHandleWriteOnly);
    ok_eq_hex(Status, STATUS_SUCCESS);

    Status = ZwCreateSection(&ReadOnlySection, SECTION_ALL_ACCESS, NULL, &MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleReadOnly);
    ok_eq_hex(Status, STATUS_SUCCESS);

    //Used for parameters taking effect only on page-file backed section
    MaximumSize.QuadPart = 5 * MM_ALLOCATION_GRANULARITY;
    Status = ZwCreateSection(&PageFileSectionHandle, SECTION_ALL_ACCESS, NULL, &MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    ok_eq_hex(Status, STATUS_SUCCESS);

    MaximumSize.QuadPart = TestStringSize;

    //section handle
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView((HANDLE)(ULONG_PTR)0xDEADBEEFDEADBEEFull, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);
    TestMapView(INVALID_HANDLE_VALUE, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_OBJECT_TYPE_MISMATCH, IGNORE);
    TestMapView(NULL, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);

    //process handle
    TestMapView(WriteSectionHandle, (HANDLE)(ULONG_PTR)0xDEADBEEFDEADBEEFull, &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);
    TestMapView(WriteSectionHandle, (HANDLE)NULL, &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);

    //base address
    BaseAddress = (PVOID)(ULONG_PTR)0x00567A20;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_MAPPED_ALIGNMENT, IGNORE);

    BaseAddress = (PVOID)(ULONG_PTR)0x60000000;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    BaseAddress = (PVOID)((char *)MmSystemRangeStart + 200);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_3, IGNORE);

    //invalid section handle AND unaligned base address
    BaseAddress = (PVOID)(ULONG_PTR)0x00567A20;
    TestMapView((HANDLE)(ULONG_PTR)0xDEADBEEFDEADBEEFull, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);

    //invalid process handle AND unaligned base address
    BaseAddress = (PVOID)(ULONG_PTR)0x00567A20;
    TestMapView(WriteSectionHandle, (HANDLE)(ULONG_PTR)0xDEADBEEFDEADBEEFull, &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_HANDLE, IGNORE);

    //try mapping section to an already mapped address
    Status = ZwAllocateVirtualMemory(NtCurrentProcess(), &AllocBase, 0, &AllocSize, MEM_COMMIT, PAGE_READWRITE);
    if (!skip(NT_SUCCESS(Status), "Cannot allocate memory\n"))
    {
        BaseAddress = AllocBase;
        TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_CONFLICTING_ADDRESSES, IGNORE);
        Status = ZwFreeVirtualMemory(NtCurrentProcess(), &AllocBase, &AllocSize, MEM_RELEASE);
        ok_eq_hex(Status, STATUS_SUCCESS);
    }

    //zero bits
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 1, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 5, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, -1, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_4, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 20, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_NO_MEMORY, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 21, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_NO_MEMORY, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 22, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_4, IGNORE);

    //commit size
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 500, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, -1, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_5, IGNORE);
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0x10000000, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_5, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 500, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_5, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 500, NULL, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    //section offset
    SectionOffset.QuadPart = 0;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, &SectionOffset, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    ok_eq_ulonglong(SectionOffset.QuadPart, 0);

    SectionOffset.QuadPart = 0x00040211; //MSDN is wrong, in w2k3 the ZwMapViewOfSection doesn't align offsets automatically
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 500, &SectionOffset, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_MAPPED_ALIGNMENT, IGNORE);

    SectionOffset.QuadPart = -1;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, &SectionOffset, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_MAPPED_ALIGNMENT, IGNORE);

    //View Size
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    ViewSize = -1;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_PARAMETER_3, IGNORE);

    ViewSize = TestStringSize+1;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_VIEW_SIZE, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    ViewSize = TestStringSize;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    ViewSize = TestStringSize-1;
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    //allocation type
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(PageFileSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READWRITE, STATUS_INVALID_PARAMETER_9, STATUS_SUCCESS);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, (MEM_RESERVE | MEM_COMMIT), PAGE_READWRITE, STATUS_INVALID_PARAMETER_9, IGNORE);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, (MEM_LARGE_PAGES | MEM_RESERVE), PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);

    //win32protect
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_NOACCESS, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(WriteSectionHandle, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE_WRITECOPY, STATUS_SECTION_PROTECTION, IGNORE);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, IGNORE);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_WRITECOPY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE_READ, STATUS_SECTION_PROTECTION, IGNORE);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, IGNORE);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_NOACCESS, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, (PAGE_READWRITE | PAGE_READONLY), STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    TestMapView(ReadOnlySection, NtCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READONLY, STATUS_SECTION_PROTECTION, IGNORE);

    ZwClose(WriteSectionHandle);
    ZwClose(PageFileSectionHandle);
    ZwClose(ReadOnlySection);
}