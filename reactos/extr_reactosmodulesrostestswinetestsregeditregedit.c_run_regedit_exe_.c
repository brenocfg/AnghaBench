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
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {int member_0; void* hStdError; void* hStdOutput; void* hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int FALSE ; 
 void* INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static BOOL run_regedit_exe_(unsigned line, const char *cmd)
{
    STARTUPINFOA si = {sizeof(STARTUPINFOA)};
    PROCESS_INFORMATION pi;
    DWORD ret;
    char cmdline[256];

    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput  = INVALID_HANDLE_VALUE;
    si.hStdOutput = INVALID_HANDLE_VALUE;
    si.hStdError  = INVALID_HANDLE_VALUE;

    strcpy(cmdline, cmd);
    if (!CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
        return FALSE;

    ret = WaitForSingleObject(pi.hProcess, 10000);
    if (ret == WAIT_TIMEOUT)
        TerminateProcess(pi.hProcess, 1);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return (ret != WAIT_TIMEOUT);
}