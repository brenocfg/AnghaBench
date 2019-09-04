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
struct TYPE_5__ {int member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW_CONSOLE ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int) ; 
 int WAIT_OBJECT_0 ; 
 int WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static DWORD runcmd(const char* cmd)
{
    STARTUPINFOA si = {sizeof(STARTUPINFOA)};
    PROCESS_INFORMATION pi;
    char* wcmd;
    DWORD rc;

    /* Create a writable copy for CreateProcessA() */
    wcmd = HeapAlloc(GetProcessHeap(), 0, strlen(cmd) + 1);
    strcpy(wcmd, cmd);

    /* On Windows 2003 and older, xcopy.exe fails if stdin is not a console
     * handle, even with '/I /Y' options.
     */
    rc = CreateProcessA(NULL, wcmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    HeapFree(GetProcessHeap(), 0, wcmd);
    if (!rc)
        return 260;

    rc = WaitForSingleObject(pi.hProcess, 5000);
    if (rc == WAIT_OBJECT_0)
        GetExitCodeProcess(pi.hProcess, &rc);
    else
        TerminateProcess(pi.hProcess, 1);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return rc;
}