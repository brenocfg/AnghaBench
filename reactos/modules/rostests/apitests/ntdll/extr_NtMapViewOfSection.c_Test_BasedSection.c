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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_4__ {int QuadPart; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NtCreateSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtMapViewOfSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int SEC_BASED ; 
 int SEC_COMMIT ; 
 int /*<<< orphan*/  STATUS_CONFLICTING_ADDRESSES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ViewShare ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
Test_BasedSection(void)
{
    NTSTATUS Status;
    HANDLE SectionHandle1, SectionHandle2;
    LARGE_INTEGER MaximumSize, SectionOffset;
    PVOID BaseAddress1, BaseAddress2;
    SIZE_T ViewSize;

    /* Create a based section with SEC_COMMIT */
    MaximumSize.QuadPart = 0x1000;
    Status = NtCreateSection(&SectionHandle1,
                             SECTION_ALL_ACCESS,
                             NULL,
                             &MaximumSize,
                             PAGE_READWRITE,
                             SEC_COMMIT | SEC_BASED,
                             NULL);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Map the 1st section */
    BaseAddress1 = NULL;
    SectionOffset.QuadPart = 0;
    ViewSize = 0;
    Status = NtMapViewOfSection(SectionHandle1,
                                NtCurrentProcess(),
                                &BaseAddress1,
                                0,
                                0,
                                &SectionOffset,
                                &ViewSize,
                                ViewShare,
                                0,
                                PAGE_READWRITE);
#if 0 // WOW64?
    ok_ntstatus(Status, STATUS_CONFLICTING_ADDRESSES);
#else
    ok_ntstatus(Status, STATUS_SUCCESS);
#endif

    /* Create a 2nd based section with SEC_COMMIT */
    MaximumSize.QuadPart = 0x1000;
    Status = NtCreateSection(&SectionHandle2,
                             SECTION_ALL_ACCESS,
                             NULL,
                             &MaximumSize,
                             PAGE_READWRITE,
                             SEC_COMMIT | SEC_BASED,
                             NULL);
    ok_ntstatus(Status, STATUS_SUCCESS);//

    /* Map the 2nd section */
    BaseAddress2 = NULL;
    SectionOffset.QuadPart = 0;
    ViewSize = 0;
    Status = NtMapViewOfSection(SectionHandle2,
                                NtCurrentProcess(),
                                &BaseAddress2,
                                0,
                                0,
                                &SectionOffset,
                                &ViewSize,
                                ViewShare,
                                0,
                                PAGE_READWRITE);
#if 0 // WOW64?
    ok_ntstatus(Status, STATUS_CONFLICTING_ADDRESSES);
#else
    ok_ntstatus(Status, STATUS_SUCCESS);
    ok((ULONG_PTR)BaseAddress2 < (ULONG_PTR)BaseAddress1,
       "Invalid addresses: BaseAddress1=%p, BaseAddress2=%p\n", BaseAddress1, BaseAddress2);
    ok(((ULONG_PTR)BaseAddress1 - (ULONG_PTR)BaseAddress2) == 0x10000,
       "Invalid addresses: BaseAddress1=%p, BaseAddress2=%p\n", BaseAddress1, BaseAddress2);
#endif
}