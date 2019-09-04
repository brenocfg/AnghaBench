#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_4__ {int LowPart; scalar_t__ HighPart; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * CreateFileMappingA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * CreateMutexA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * CreateSemaphoreA (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  DIRECTORY_QUERY ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NotificationTimer ; 
 int /*<<< orphan*/  OBJ_OPENIF ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  SECTION_MAP_WRITE ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_COLLISION ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_EXISTS ; 
 int /*<<< orphan*/  STATUS_OBJECT_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_OBJECT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_base_dir () ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * pCreateWaitableTimerA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtCreateDirectoryObject (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtCreateEvent (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateMutant (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateSection (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateSemaphore (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pNtCreateTimer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_name_collisions(void)
{
    NTSTATUS status;
    UNICODE_STRING str;
    OBJECT_ATTRIBUTES attr;
    HANDLE dir, h, h1, h2;
    DWORD winerr;
    LARGE_INTEGER size;

    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\");
    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_NAME_COLLISION, "NtCreateDirectoryObject got %08x\n", status );
    InitializeObjectAttributes(&attr, &str, OBJ_OPENIF, 0, NULL);

    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_NAME_EXISTS, "NtCreateDirectoryObject got %08x\n", status );
    pNtClose(h);
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_TYPE_MISMATCH,
        "NtCreateMutant should have failed with STATUS_OBJECT_TYPE_MISMATCH got(%08x)\n", status);
    pRtlFreeUnicodeString(&str);

    pRtlCreateUnicodeStringFromAsciiz(&str, "\\??\\PIPE\\om.c-mutant");
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_TYPE_MISMATCH || status == STATUS_OBJECT_PATH_NOT_FOUND,
        "NtCreateMutant should have failed with STATUS_OBJECT_TYPE_MISMATCH got(%08x)\n", status);
    pRtlFreeUnicodeString(&str);

    if (!(dir = get_base_dir()))
    {
        win_skip( "couldn't find the BaseNamedObjects dir\n" );
        return;
    }
    pRtlCreateUnicodeStringFromAsciiz(&str, "om.c-test");
    InitializeObjectAttributes(&attr, &str, OBJ_OPENIF, dir, NULL);
    h = CreateMutexA(NULL, FALSE, "om.c-test");
    ok(h != 0, "CreateMutexA failed got ret=%p (%d)\n", h, GetLastError());
    status = pNtCreateMutant(&h1, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_NAME_EXISTS && h1 != NULL,
        "NtCreateMutant should have succeeded with STATUS_OBJECT_NAME_EXISTS got(%08x)\n", status);
    h2 = CreateMutexA(NULL, FALSE, "om.c-test");
    winerr = GetLastError();
    ok(h2 != 0 && winerr == ERROR_ALREADY_EXISTS,
        "CreateMutexA should have succeeded with ERROR_ALREADY_EXISTS got ret=%p (%d)\n", h2, winerr);
    pNtClose(h);
    pNtClose(h1);
    pNtClose(h2);

    h = CreateEventA(NULL, FALSE, FALSE, "om.c-test");
    ok(h != 0, "CreateEventA failed got ret=%p (%d)\n", h, GetLastError());
    status = pNtCreateEvent(&h1, GENERIC_ALL, &attr, FALSE, FALSE);
    ok(status == STATUS_OBJECT_NAME_EXISTS && h1 != NULL,
        "NtCreateEvent should have succeeded with STATUS_OBJECT_NAME_EXISTS got(%08x)\n", status);
    h2 = CreateEventA(NULL, FALSE, FALSE, "om.c-test");
    winerr = GetLastError();
    ok(h2 != 0 && winerr == ERROR_ALREADY_EXISTS,
        "CreateEventA should have succeeded with ERROR_ALREADY_EXISTS got ret=%p (%d)\n", h2, winerr);
    pNtClose(h);
    pNtClose(h1);
    pNtClose(h2);

    h = CreateSemaphoreA(NULL, 1, 2, "om.c-test");
    ok(h != 0, "CreateSemaphoreA failed got ret=%p (%d)\n", h, GetLastError());
    status = pNtCreateSemaphore(&h1, GENERIC_ALL, &attr, 1, 2);
    ok(status == STATUS_OBJECT_NAME_EXISTS && h1 != NULL,
        "NtCreateSemaphore should have succeeded with STATUS_OBJECT_NAME_EXISTS got(%08x)\n", status);
    h2 = CreateSemaphoreA(NULL, 1, 2, "om.c-test");
    winerr = GetLastError();
    ok(h2 != 0 && winerr == ERROR_ALREADY_EXISTS,
        "CreateSemaphoreA should have succeeded with ERROR_ALREADY_EXISTS got ret=%p (%d)\n", h2, winerr);
    pNtClose(h);
    pNtClose(h1);
    pNtClose(h2);
    
    h = pCreateWaitableTimerA(NULL, TRUE, "om.c-test");
    ok(h != 0, "CreateWaitableTimerA failed got ret=%p (%d)\n", h, GetLastError());
    status = pNtCreateTimer(&h1, GENERIC_ALL, &attr, NotificationTimer);
    ok(status == STATUS_OBJECT_NAME_EXISTS && h1 != NULL,
        "NtCreateTimer should have succeeded with STATUS_OBJECT_NAME_EXISTS got(%08x)\n", status);
    h2 = pCreateWaitableTimerA(NULL, TRUE, "om.c-test");
    winerr = GetLastError();
    ok(h2 != 0 && winerr == ERROR_ALREADY_EXISTS,
        "CreateWaitableTimerA should have succeeded with ERROR_ALREADY_EXISTS got ret=%p (%d)\n", h2, winerr);
    pNtClose(h);
    pNtClose(h1);
    pNtClose(h2);

    h = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, "om.c-test");
    ok(h != 0, "CreateFileMappingA failed got ret=%p (%d)\n", h, GetLastError());
    size.u.LowPart = 256;
    size.u.HighPart = 0;
    status = pNtCreateSection(&h1, SECTION_MAP_WRITE, &attr, &size, PAGE_READWRITE, SEC_COMMIT, 0);
    ok(status == STATUS_OBJECT_NAME_EXISTS && h1 != NULL,
        "NtCreateSection should have succeeded with STATUS_OBJECT_NAME_EXISTS got(%08x)\n", status);
    h2 = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, "om.c-test");
    winerr = GetLastError();
    ok(h2 != 0 && winerr == ERROR_ALREADY_EXISTS,
        "CreateFileMappingA should have succeeded with ERROR_ALREADY_EXISTS got ret=%p (%d)\n", h2, winerr);
    pNtClose(h);
    pNtClose(h1);
    pNtClose(h2);

    pRtlFreeUnicodeString(&str);
    pNtClose(dir);
}