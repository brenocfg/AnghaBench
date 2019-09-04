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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseEventLog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
 scalar_t__ ERROR_EVENTLOG_FILE_CORRUPT ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetFileAttributesA (char const*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/ * OpenBackupEventLogA (char*,char const*) ; 
 scalar_t__ RPC_S_INVALID_NET_ADDR ; 
 scalar_t__ RPC_S_SERVER_UNAVAILABLE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_backup (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_openbackup(void)
{
    HANDLE handle, handle2, file;
    DWORD written;
    const char backup[] = "backup.evt";
    const char text[] = "Just some text";

    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA(NULL, NULL);
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA(NULL, "idontexist.evt");
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == ERROR_FILE_NOT_FOUND, "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA("IDontExist", NULL);
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA("IDontExist", "idontexist.evt");
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == RPC_S_SERVER_UNAVAILABLE ||
       GetLastError() == RPC_S_INVALID_NET_ADDR, /* Some Vista and Win7 */
       "Expected RPC_S_SERVER_UNAVAILABLE, got %d\n", GetLastError());

    /* Make a backup eventlog to work with */
    if (create_backup(backup))
    {
        /* FIXME: Wine stops here */
        if (GetFileAttributesA(backup) == INVALID_FILE_ATTRIBUTES)
        {
            skip("We don't have a backup eventlog to work with\n");
            return;
        }

        SetLastError(0xdeadbeef);
        handle = OpenBackupEventLogA("IDontExist", backup);
        ok(handle == NULL, "Didn't expect a handle\n");
        ok(GetLastError() == RPC_S_SERVER_UNAVAILABLE ||
           GetLastError() == RPC_S_INVALID_NET_ADDR, /* Some Vista and Win7 */
           "Expected RPC_S_SERVER_UNAVAILABLE, got %d\n", GetLastError());

        /* Empty servername should be read as local server */
        handle = OpenBackupEventLogA("", backup);
        ok(handle != NULL, "Expected a handle\n");
        CloseEventLog(handle);

        handle = OpenBackupEventLogA(NULL, backup);
        ok(handle != NULL, "Expected a handle\n");

        /* Can we open that same backup eventlog more than once? */
        handle2 = OpenBackupEventLogA(NULL, backup);
        ok(handle2 != NULL, "Expected a handle\n");
        ok(handle2 != handle, "Didn't expect the same handle\n");
        CloseEventLog(handle2);

        CloseEventLog(handle);
        DeleteFileA(backup);
    }

    /* Is there any content checking done? */
    file = CreateFileA(backup, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
    CloseHandle(file);
    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA(NULL, backup);
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == ERROR_NOT_ENOUGH_MEMORY ||
       GetLastError() == ERROR_EVENTLOG_FILE_CORRUPT, /* Vista and Win7 */
       "Expected ERROR_NOT_ENOUGH_MEMORY, got %d\n", GetLastError());
    CloseEventLog(handle);
    DeleteFileA(backup);

    file = CreateFileA(backup, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
    WriteFile(file, text, sizeof(text), &written, NULL);
    CloseHandle(file);
    SetLastError(0xdeadbeef);
    handle = OpenBackupEventLogA(NULL, backup);
    ok(handle == NULL, "Didn't expect a handle\n");
    ok(GetLastError() == ERROR_EVENTLOG_FILE_CORRUPT, "Expected ERROR_EVENTLOG_FILE_CORRUPT, got %d\n", GetLastError());
    CloseEventLog(handle);
    DeleteFileA(backup);
}