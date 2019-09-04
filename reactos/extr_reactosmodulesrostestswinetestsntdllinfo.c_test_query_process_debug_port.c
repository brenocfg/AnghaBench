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
typedef  int /*<<< orphan*/  debug_port ;
struct TYPE_9__ {scalar_t__ dwDebugEventCode; int /*<<< orphan*/  dwThreadId; int /*<<< orphan*/  dwProcessId; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hProcess; int /*<<< orphan*/ * hThread; } ;
struct TYPE_7__ {int cb; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_3__ DEBUG_EVENT ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int ContinueDebugEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 int /*<<< orphan*/  DEBUG_PROCESS ; 
 scalar_t__ EXIT_PROCESS_DEBUG_EVENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ProcessDebugPort ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_INVALID_HANDLE ; 
 int WaitForDebugEvent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pNtQueryInformationProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void test_query_process_debug_port(int argc, char **argv)
{
    DWORD_PTR debug_port = 0xdeadbeef;
    char cmdline[MAX_PATH];
    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { 0 };
    NTSTATUS status;
    BOOL ret;

    sprintf(cmdline, "%s %s %s", argv[0], argv[1], "debuggee");

    si.cb = sizeof(si);
    ret = CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &si, &pi);
    ok(ret, "CreateProcess failed, last error %#x.\n", GetLastError());
    if (!ret) return;

    status = pNtQueryInformationProcess(NULL, ProcessDebugPort,
            NULL, 0, NULL);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %#x.\n", status);

    status = pNtQueryInformationProcess(NULL, ProcessDebugPort,
            NULL, sizeof(debug_port), NULL);
    ok(status == STATUS_INVALID_HANDLE || status == STATUS_ACCESS_VIOLATION,
            "Expected STATUS_INVALID_HANDLE, got %#x.\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort,
            NULL, sizeof(debug_port), NULL);
    ok(status == STATUS_ACCESS_VIOLATION, "Expected STATUS_ACCESS_VIOLATION, got %#x.\n", status);

    status = pNtQueryInformationProcess(NULL, ProcessDebugPort,
            &debug_port, sizeof(debug_port), NULL);
    ok(status == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got %#x.\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort,
            &debug_port, sizeof(debug_port) - 1, NULL);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %#x.\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort,
            &debug_port, sizeof(debug_port) + 1, NULL);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %#x.\n", status);

    status = pNtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort,
            &debug_port, sizeof(debug_port), NULL);
    ok(!status, "NtQueryInformationProcess failed, status %#x.\n", status);
    ok(debug_port == 0, "Expected port 0, got %#lx.\n", debug_port);

    status = pNtQueryInformationProcess(pi.hProcess, ProcessDebugPort,
            &debug_port, sizeof(debug_port), NULL);
    ok(!status, "NtQueryInformationProcess failed, status %#x.\n", status);
    ok(debug_port == ~(DWORD_PTR)0, "Expected port %#lx, got %#lx.\n", ~(DWORD_PTR)0, debug_port);

    for (;;)
    {
        DEBUG_EVENT ev;

        ret = WaitForDebugEvent(&ev, INFINITE);
        ok(ret, "WaitForDebugEvent failed, last error %#x.\n", GetLastError());
        if (!ret) break;

        if (ev.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) break;

        ret = ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, DBG_CONTINUE);
        ok(ret, "ContinueDebugEvent failed, last error %#x.\n", GetLastError());
        if (!ret) break;
    }

    ret = CloseHandle(pi.hThread);
    ok(ret, "CloseHandle failed, last error %#x.\n", GetLastError());
    ret = CloseHandle(pi.hProcess);
    ok(ret, "CloseHandle failed, last error %#x.\n", GetLastError());
}