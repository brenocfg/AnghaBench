#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_6__ {scalar_t__ dwFlags; } ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_DEFAULT_ERROR_MODE ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,int*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetStartupInfo (TYPE_1__*) ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  R_ERROR ; 
 int /*<<< orphan*/  R_FATAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int) ; 
#define  WAIT_FAILED 130 
#define  WAIT_OBJECT_0 129 
#define  WAIT_TIMEOUT 128 
 int WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int dup2 (int,int) ; 
 int errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
run_ex (char *cmd, const char *out, const char *tempdir, DWORD ms)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    int fd, oldstdout = -1;
    DWORD wait, status;

    GetStartupInfo (&si);
    si.dwFlags = 0;

    if (out) {
        fd = open (out, O_WRONLY | O_CREAT, 0666);
        if (-1 == fd)
            report (R_FATAL, "Can't open '%s': %d", out, errno);
        oldstdout = dup (1);
        if (-1 == oldstdout)
            report (R_FATAL, "Can't save stdout: %d", errno);
        if (-1 == dup2 (fd, 1))
            report (R_FATAL, "Can't redirect stdout: %d", errno);
        close (fd);
    }

    if (!CreateProcessA (NULL, cmd, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE,
                         NULL, tempdir, &si, &pi)) {
        status = -2;
    } else {
        CloseHandle (pi.hThread);
        wait = WaitForSingleObject (pi.hProcess, ms);
        if (wait == WAIT_OBJECT_0) {
            GetExitCodeProcess (pi.hProcess, &status);
        } else {
            switch (wait) {
            case WAIT_FAILED:
                report (R_ERROR, "Wait for '%s' failed: %d", cmd,
                        GetLastError ());
                break;
            case WAIT_TIMEOUT:
                report (R_ERROR, "Process '%s' timed out.", cmd);
                break;
            default:
                report (R_ERROR, "Wait returned %d", wait);
            }
            status = wait;
            if (!TerminateProcess (pi.hProcess, 257))
                report (R_ERROR, "TerminateProcess failed: %d",
                        GetLastError ());
            wait = WaitForSingleObject (pi.hProcess, 5000);
            switch (wait) {
            case WAIT_FAILED:
                report (R_ERROR,
                        "Wait for termination of '%s' failed: %d",
                        cmd, GetLastError ());
                break;
            case WAIT_OBJECT_0:
                break;
            case WAIT_TIMEOUT:
                report (R_ERROR, "Can't kill process '%s'", cmd);
                break;
            default:
                report (R_ERROR, "Waiting for termination: %d",
                        wait);
            }
        }
        CloseHandle (pi.hProcess);
    }

    if (out) {
        close (1);
        if (-1 == dup2 (oldstdout, 1))
            report (R_FATAL, "Can't recover stdout: %d", errno);
        close (oldstdout);
    }
    return status;
}