#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statusproc ;
struct TYPE_5__ {int dwCurrentState; } ;
struct TYPE_4__ {scalar_t__ dwCurrentState; scalar_t__ dwProcessId; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  TYPE_2__ SERVICE_STATUS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ControlService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ERROR_SERVICE_NOT_ACTIVE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SC_STATUS_PROCESS_INFO ; 
 int /*<<< orphan*/  SERVICE_CONTROL_STOP ; 
 scalar_t__ SERVICE_STOPPED ; 
 int StartServiceA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int pQueryServiceStatusEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static DWORD try_start_stop(SC_HANDLE svc_handle, const char* name, DWORD is_nt4)
{
    BOOL ret;
    DWORD le1, le2;
    SERVICE_STATUS status;

#ifdef __REACTOS__
    fprintf(stdout, "ROSTESTS-56: Hello sysreg, I am awake\n");
#endif
    ret = StartServiceA(svc_handle, 0, NULL);
    le1 = GetLastError();
    ok(!ret, "%s: StartServiceA() should have failed\n", name);

    if (pQueryServiceStatusEx)
    {
        DWORD needed;
        SERVICE_STATUS_PROCESS statusproc;

        ret = pQueryServiceStatusEx(svc_handle, SC_STATUS_PROCESS_INFO, (BYTE*)&statusproc, sizeof(statusproc), &needed);
        ok(ret, "%s: QueryServiceStatusEx() failed le=%u\n", name, GetLastError());
        ok(statusproc.dwCurrentState == SERVICE_STOPPED, "%s: should be stopped state=%x\n", name, statusproc.dwCurrentState);
        ok(statusproc.dwProcessId == 0, "%s: ProcessId should be 0 instead of %x\n", name, statusproc.dwProcessId);
    }

    ret = StartServiceA(svc_handle, 0, NULL);
    le2 = GetLastError();
    ok(!ret, "%s: StartServiceA() should have failed\n", name);
    ok(le2 == le1, "%s: the second try should yield the same error: %u != %u\n", name, le1, le2);

    status.dwCurrentState = 0xdeadbeef;
    ret = ControlService(svc_handle, SERVICE_CONTROL_STOP, &status);
    le2 = GetLastError();
    ok(!ret, "%s: ControlService() should have failed\n", name);
    ok(le2 == ERROR_SERVICE_NOT_ACTIVE, "%s: %d != ERROR_SERVICE_NOT_ACTIVE\n", name, le2);
    ok(status.dwCurrentState == SERVICE_STOPPED ||
       broken(is_nt4), /* NT4 returns a random value */
       "%s: should be stopped state=%x\n", name, status.dwCurrentState);

    return le1;
}