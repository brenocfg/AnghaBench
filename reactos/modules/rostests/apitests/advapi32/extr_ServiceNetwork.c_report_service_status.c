#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwControlsAccepted; scalar_t__ dwCheckPoint; scalar_t__ dwServiceSpecificExitCode; void* dwWaitHint; void* dwWin32ExitCode; void* dwCurrentState; int /*<<< orphan*/  dwServiceType; } ;
typedef  TYPE_1__ SERVICE_STATUS ;
typedef  void* DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int SERVICE_ACCEPT_SHUTDOWN ; 
 int SERVICE_ACCEPT_STOP ; 
 void* SERVICE_RUNNING ; 
 void* SERVICE_START_PENDING ; 
 void* SERVICE_STOPPED ; 
 void* SERVICE_STOP_PENDING ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dwCheckPoint ; 
 int /*<<< orphan*/  service_ok (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_handle ; 

__attribute__((used)) static void
report_service_status(DWORD dwCurrentState,
                      DWORD dwWin32ExitCode,
                      DWORD dwWaitHint)
{
    BOOL res;
    SERVICE_STATUS status;

    status.dwServiceType   = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState  = dwCurrentState;
    status.dwWin32ExitCode = dwWin32ExitCode;
    status.dwWaitHint      = dwWaitHint;

    status.dwServiceSpecificExitCode = 0;
    status.dwCheckPoint              = 0;

    if ( (dwCurrentState == SERVICE_START_PENDING) ||
         (dwCurrentState == SERVICE_STOP_PENDING)  ||
         (dwCurrentState == SERVICE_STOPPED) )
    {
        status.dwControlsAccepted = 0;
    }
    else
    {
        status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    }

#if 0
    if ( (dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED) )
        status.dwCheckPoint = 0;
    else
        status.dwCheckPoint = dwCheckPoint++;
#endif

    res = SetServiceStatus(status_handle, &status);
    service_ok(res, "SetServiceStatus(%d) failed: %lu\n", dwCurrentState, GetLastError());
}