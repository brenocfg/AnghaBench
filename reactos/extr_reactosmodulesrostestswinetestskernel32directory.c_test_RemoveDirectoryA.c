#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* Peb; } ;
struct TYPE_7__ {TYPE_2__* ProcessParameters; } ;
struct TYPE_5__ {int /*<<< orphan*/  Handle; } ;
struct TYPE_6__ {TYPE_1__ CurrentDirectory; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 scalar_t__ ERROR_SHARING_VIOLATION ; 
 scalar_t__ FALSE ; 
 int FILE_TRAVERSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 TYPE_4__* NtCurrentTeb () ; 
 scalar_t__ RemoveDirectoryA (char*) ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TEST_GRANTED_ACCESS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_RemoveDirectoryA(void)
{
    char curdir[MAX_PATH];
    char tmpdir[MAX_PATH];
    BOOL ret;

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE, "CreateDirectoryA should always succeed\n");

    GetCurrentDirectoryA(MAX_PATH, curdir);
    ok(SetCurrentDirectoryA(tmpdir), "SetCurrentDirectoryA failed\n");

    SetLastError(0xdeadbeef);
    ok(!RemoveDirectoryA(tmpdir), "RemoveDirectoryA succeeded\n");
    ok(GetLastError() == ERROR_SHARING_VIOLATION,
       "Expected ERROR_SHARING_VIOLATION, got %u\n", GetLastError());

    TEST_GRANTED_ACCESS(NtCurrentTeb()->Peb->ProcessParameters->CurrentDirectory.Handle,
                        FILE_TRAVERSE | SYNCHRONIZE);

    SetCurrentDirectoryA(curdir);
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE, "RemoveDirectoryA should always succeed\n");

    lstrcatA(tmpdir, "?");
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == FALSE && (GetLastError() == ERROR_INVALID_NAME ||
			GetLastError() == ERROR_PATH_NOT_FOUND),
       "RemoveDirectoryA with ? wildcard name should fail, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());

    tmpdir[lstrlenA(tmpdir) - 1] = '*';
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == FALSE && (GetLastError() == ERROR_INVALID_NAME ||
			GetLastError() == ERROR_PATH_NOT_FOUND),
       "RemoveDirectoryA with * wildcard name should fail, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());
}