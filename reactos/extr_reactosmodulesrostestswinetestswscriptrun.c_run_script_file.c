#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {int member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ GetExitCodeProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  reportSuccess ; 
 char const* script_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wscript_process ; 

__attribute__((used)) static void run_script_file(const char *file_name, DWORD expected_exit_code)
{
    char command[MAX_PATH];
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    DWORD exit_code;
    BOOL bres;

    script_name = file_name;
    sprintf(command, "wscript.exe %s arg1 2 ar3", file_name);

    SET_EXPECT(reportSuccess);

    bres = CreateProcessA(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if(!bres) {
        win_skip("script.exe is not available\n");
        CLEAR_CALLED(reportSuccess);
        return;
    }

    wscript_process = pi.hProcess;
    WaitForSingleObject(pi.hProcess, INFINITE);

    bres = GetExitCodeProcess(pi.hProcess, &exit_code);
    ok(bres, "GetExitCodeProcess failed: %u\n", GetLastError());
    ok(exit_code == expected_exit_code, "exit_code = %u, expected %u\n", exit_code, expected_exit_code);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    CHECK_CALLED(reportSuccess);
}