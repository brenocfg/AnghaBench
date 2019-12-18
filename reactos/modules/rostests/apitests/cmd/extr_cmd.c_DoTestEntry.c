#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
struct TYPE_11__ {scalar_t__ hProcess; scalar_t__ hThread; } ;
struct TYPE_10__ {int cb; scalar_t__ hStdError; scalar_t__ hStdOutput; scalar_t__ hStdInput; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_9__ {scalar_t__ bStdOutput; scalar_t__ bStdError; scalar_t__ dwExitCode; int /*<<< orphan*/  line; scalar_t__ cmdline; } ;
typedef  TYPE_1__ TEST_ENTRY ;
typedef  TYPE_2__ STARTUPINFOA ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GetExitCodeProcess (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  PeekNamedPipe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrepareForRedirect (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TerminateProcess (scalar_t__,int) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void DoTestEntry(const TEST_ENTRY *pEntry)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    DWORD dwExitCode, dwWait;
    HANDLE hOutputRead = NULL;
    HANDLE hErrorRead = NULL;
    BYTE b;
    DWORD dwRead;
    BOOL bStdOutput, bStdError;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;

    if (!PrepareForRedirect(&si, NULL, &hOutputRead, &hErrorRead))
    {
        skip("PrepareForRedirect failed\n");
        return;
    }

    if (CreateProcessA(NULL, (char *)pEntry->cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(si.hStdInput);
        dwWait = WaitForSingleObject(pi.hProcess, TIMEOUT);
        if (dwWait == WAIT_TIMEOUT)
        {
            TerminateProcess(pi.hProcess, 9999);
        }
        GetExitCodeProcess(pi.hProcess, &dwExitCode);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
    else
    {
        dwExitCode = 8888;
    }

    PeekNamedPipe(hOutputRead, &b, 1, &dwRead, NULL, NULL);
    bStdOutput = dwRead != 0;
    PeekNamedPipe(hErrorRead, &b, 1, &dwRead, NULL, NULL);
    bStdError = dwRead != 0;

    if (si.hStdInput)
        CloseHandle(si.hStdInput);
    if (si.hStdOutput)
        CloseHandle(si.hStdOutput);
    if (si.hStdError)
        CloseHandle(si.hStdError);

    ok(pEntry->bStdOutput == bStdOutput,
       "Line %u: bStdOutput %d vs %d\n",
       pEntry->line, pEntry->bStdOutput, bStdOutput);

    ok(pEntry->bStdError == bStdError,
       "Line %u: bStdError %d vs %d\n",
       pEntry->line, pEntry->bStdError, bStdError);

    ok(pEntry->dwExitCode == dwExitCode,
       "Line %u: dwExitCode %ld vs %ld\n",
       pEntry->line, pEntry->dwExitCode, dwExitCode);
}