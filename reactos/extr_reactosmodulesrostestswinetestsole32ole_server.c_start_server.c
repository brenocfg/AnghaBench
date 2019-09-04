#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_9__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_8__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
struct TYPE_7__ {int cb; void* hStdOutput; void* hStdError; void* hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessA (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static HANDLE start_server(const char *argv0)
{
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    SECURITY_ATTRIBUTES sa;
    char cmdline[MAX_PATH * 2];
    BOOL ret;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput =  GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = si.hStdOutput;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    sprintf(cmdline, "\"%s\" ole_server -server", argv0);
    ret = CreateProcessA(argv0, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    ok(ret, "CreateProcess(%s) error %d\n", cmdline, GetLastError());
    if (!ret) return 0;

    CloseHandle(pi.hThread);
    return pi.hProcess;
}