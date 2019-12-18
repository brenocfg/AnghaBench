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
struct TYPE_4__ {void* QuadPart; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 int /*<<< orphan*/  MmTestMapView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObReferenceObjectByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  PsGetCurrentProcess () ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  STANDARD_RIGHTS_ALL ; 
 int /*<<< orphan*/  STATUS_INVALID_VIEW_SIZE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 void* TestStringSize ; 
 int /*<<< orphan*/  ViewUnmap ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwCreateSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_eq_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
AdvancedErrorChecks(HANDLE FileHandleReadOnly, HANDLE FileHandleWriteOnly)
{
    NTSTATUS Status;
    PVOID BaseAddress;
    HANDLE FileSectionHandle;
    LARGE_INTEGER SectionOffset;
    LARGE_INTEGER MaximumSize;
    SIZE_T ViewSize = 0;
    PVOID SectionObject;

    MaximumSize.QuadPart = TestStringSize;
    //Used for parameters working on file-based section
    Status = ZwCreateSection(&FileSectionHandle, SECTION_ALL_ACCESS, NULL, &MaximumSize, PAGE_READWRITE, SEC_COMMIT, FileHandleWriteOnly);
    ok_eq_hex(Status, STATUS_SUCCESS);

    Status = ObReferenceObjectByHandle(FileSectionHandle,
        STANDARD_RIGHTS_ALL,
        NULL,
        KernelMode,
        &SectionObject,
        NULL);

    ok_eq_hex(Status, STATUS_SUCCESS);

    //Bypassing Zw function calls mean bypassing the alignment checks which are not crucial for the branches being tested here

    //test first conditional branch
    ViewSize = -1;
    MmTestMapView(SectionObject, PsGetCurrentProcess(), &BaseAddress, 0, TestStringSize, &SectionOffset, &ViewSize, ViewUnmap, MEM_RESERVE, PAGE_READWRITE, STATUS_INVALID_VIEW_SIZE, IGNORE);

    //test second conditional branch
    ViewSize = 1;
    SectionOffset.QuadPart = TestStringSize;
    MmTestMapView(SectionObject, PsGetCurrentProcess(), &BaseAddress, 0, TestStringSize, &SectionOffset, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_INVALID_VIEW_SIZE, IGNORE);

    ObDereferenceObject(SectionObject);
    ZwClose(FileSectionHandle);
}