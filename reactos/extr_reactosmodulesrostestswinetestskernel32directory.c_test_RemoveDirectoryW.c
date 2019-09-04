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
typedef  char WCHAR ;
struct TYPE_8__ {TYPE_3__* Peb; } ;
struct TYPE_7__ {TYPE_2__* ProcessParameters; } ;
struct TYPE_5__ {int /*<<< orphan*/  Handle; } ;
struct TYPE_6__ {TYPE_1__ CurrentDirectory; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_SHARING_VIOLATION ; 
 scalar_t__ FALSE ; 
 int FILE_TRAVERSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 int MAX_PATH ; 
 TYPE_4__* NtCurrentTeb () ; 
 scalar_t__ RemoveDirectoryW (char*) ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TEST_GRANTED_ACCESS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RemoveDirectoryW(void)
{
    WCHAR curdir[MAX_PATH];
    WCHAR tmpdir[MAX_PATH];
    BOOL ret;
    static const WCHAR tmp_dir_name[] = {'P','l','e','a','s','e',' ','R','e','m','o','v','e',' ','M','e',0};
    static const WCHAR questionW[] = {'?',0};

    GetTempPathW(MAX_PATH, tmpdir);
    lstrcatW(tmpdir, tmp_dir_name);
    ret = CreateDirectoryW(tmpdir, NULL);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("CreateDirectoryW is not available\n");
        return;
    }

    ok(ret == TRUE, "CreateDirectoryW should always succeed\n");

    GetCurrentDirectoryW(MAX_PATH, curdir);
    ok(SetCurrentDirectoryW(tmpdir), "SetCurrentDirectoryW failed\n");

    SetLastError(0xdeadbeef);
    ok(!RemoveDirectoryW(tmpdir), "RemoveDirectoryW succeeded\n");
    ok(GetLastError() == ERROR_SHARING_VIOLATION,
       "Expected ERROR_SHARING_VIOLATION, got %u\n", GetLastError());

    TEST_GRANTED_ACCESS(NtCurrentTeb()->Peb->ProcessParameters->CurrentDirectory.Handle,
                        FILE_TRAVERSE | SYNCHRONIZE);

    SetCurrentDirectoryW(curdir);
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == TRUE, "RemoveDirectoryW should always succeed\n");

    lstrcatW(tmpdir, questionW);
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == FALSE && GetLastError() == ERROR_INVALID_NAME,
       "RemoveDirectoryW with wildcard should fail with error 183, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());

    tmpdir[lstrlenW(tmpdir) - 1] = '*';
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == FALSE && GetLastError() == ERROR_INVALID_NAME,
       "RemoveDirectoryW with * wildcard name should fail with error 183, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());
}