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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_FILE_INVALID ; 
 int ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  LogSevInformation ; 
 int /*<<< orphan*/  LogSevMaximum ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseLog () ; 
 int SetupLogErrorA (char*,int /*<<< orphan*/ ) ; 
 int SetupOpenLog (int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_SetupLogError(void)
{
    BOOL ret;
    DWORD error;

    SetLastError(0xdeadbeef);
    ret = SetupLogErrorA("Test without opening\r\n", LogSevInformation);
    error = GetLastError();
    ok(!ret, "SetupLogError succeeded\n");
    ok(error == ERROR_FILE_INVALID, "got wrong error: %d\n", error);

    SetLastError(0xdeadbeef);
    ret = SetupOpenLog(FALSE);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("SetupOpenLog() failed on insufficient permissions\n");
        return;
    }
    ok(ret, "SetupOpenLog failed, error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupLogErrorA("Test with wrong log severity\r\n", LogSevMaximum);
    error = GetLastError();
    ok(!ret, "SetupLogError succeeded\n");
    ok(error == 0xdeadbeef, "got wrong error: %d\n", error);
    ret = SetupLogErrorA("Test without EOL", LogSevInformation);
    ok(ret, "SetupLogError failed\n");

    SetLastError(0xdeadbeef);
    ret = SetupLogErrorA(NULL, LogSevInformation);
    ok(ret || broken(!ret && GetLastError() == ERROR_INVALID_PARAMETER /* Win Vista+ */),
        "SetupLogError failed: %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupOpenLog(FALSE);
    ok(ret, "SetupOpenLog failed, error %d\n", GetLastError());

    SetupCloseLog();
}