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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SECTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_HANDLE_CLOSE ; 
 int /*<<< orphan*/  PAGE_EXECUTE ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  PAGE_WRITECOPY ; 
 int /*<<< orphan*/  SECTION_MAP_EXECUTE ; 
 int /*<<< orphan*/  SECTION_MAP_READ ; 
 int /*<<< orphan*/  SECTION_MAP_WRITE ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  STATUS_SECTION_PROTECTION ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TestMapView (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestStringSize ; 
 int /*<<< orphan*/  ViewUnmap ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwCurrentProcess () ; 

__attribute__((used)) static
VOID
FileSectionViewPermissionCheck(HANDLE ReadOnlyFile, HANDLE WriteOnlyFile, HANDLE ExecutableFile)
{
    NTSTATUS Status;
    HANDLE SectionHandle = NULL;
    PVOID BaseAddress = NULL;
    SIZE_T ViewSize = 0;
    LARGE_INTEGER MaximumSize;

    MaximumSize.QuadPart = TestStringSize;

    //READ-ONLY FILE COMBINATIONS
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ReadOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    //WRITE-ONLY FILE COMBINATIONS
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SUCCESS, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, WriteOnlyFile, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READONLY, STATUS_SUCCESS, STATUS_SUCCESS);
    TestMapView(SectionHandle, ZwCurrentProcess(), &BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_EXECUTE, STATUS_SECTION_PROTECTION, STATUS_SUCCESS);
    ZwClose(SectionHandle);

    //EXECUTE ONLY FILE
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_READ, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);

    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_WRITE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);

    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_EXECUTE, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(SectionHandle, SECTION_MAP_EXECUTE, NULL, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, ExecutableFile, STATUS_SUCCESS, STATUS_SUCCESS);
}