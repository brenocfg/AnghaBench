#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct child_blackbox {int failures; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  blackbox ;
struct TYPE_10__ {scalar_t__ dwDebugEventCode; scalar_t__ dwProcessId; int /*<<< orphan*/  dwThreadId; } ;
struct TYPE_9__ {scalar_t__ dwProcessId; int /*<<< orphan*/ * hProcess; int /*<<< orphan*/ * hThread; } ;
struct TYPE_8__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  TYPE_3__ DEBUG_EVENT ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int ContinueDebugEvent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateEventA (int /*<<< orphan*/ *,int,int,char*) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 int DebugActiveProcess (scalar_t__) ; 
 int DeleteFileA (char*) ; 
 scalar_t__ EXIT_PROCESS_DEBUG_EVENT ; 
 int FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int MAX_PATH ; 
 int SetEvent (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int WaitForDebugEvent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_file_name (char*) ; 
 int /*<<< orphan*/  load_blackbox (char*,struct child_blackbox*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pCheckRemoteDebuggerPresent (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pDebugActiveProcessStop ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_debug_children(char *name, DWORD flag, BOOL debug_child)
{
    const char *arguments = "debugger children";
    struct child_blackbox blackbox;
    char blackbox_file[MAX_PATH], *p;
    char event_name[MAX_PATH];
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    HANDLE event_init, event_attach;
    char *cmd;
    BOOL debug, ret;
    BOOL got_child_event = FALSE;

    if (!pDebugActiveProcessStop || !pCheckRemoteDebuggerPresent)
    {
        win_skip("DebugActiveProcessStop or CheckRemoteDebuggerPresent not available, skipping test.\n");
        return;
    }

    get_file_name(blackbox_file);
    cmd = HeapAlloc(GetProcessHeap(), 0, strlen(name) + strlen(arguments) + strlen(blackbox_file) + 5);
    sprintf(cmd, "%s %s \"%s\"", name, arguments, blackbox_file);

    p = strrchr(blackbox_file, '\\');
    p = p ? p+1 : blackbox_file;
    strcpy(event_name, p);
    strcat(event_name, "_init");
    event_init = CreateEventA(NULL, FALSE, FALSE, event_name);
    ok(event_init != NULL, "OpenEvent failed, last error %d.\n", GetLastError());

    p = strrchr(blackbox_file, '\\');
    p = p ? p+1 : blackbox_file;
    strcpy(event_name, p);
    strcat(event_name, "_attach");
    event_attach = CreateEventA(NULL, FALSE, flag!=0, event_name);
    ok(event_attach != NULL, "CreateEvent failed, last error %d.\n", GetLastError());

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);

    ret = CreateProcessA(NULL, cmd, NULL, NULL, FALSE, flag, NULL, NULL, &si, &pi);
    ok(ret, "CreateProcess failed, last error %d.\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, cmd);
    if (!flag)
    {
        WaitForSingleObject(event_init, INFINITE);
        ret = DebugActiveProcess(pi.dwProcessId);
        ok(ret, "DebugActiveProcess failed, last error %d.\n", GetLastError());
        ret = SetEvent(event_attach);
        ok(ret, "SetEvent failed, last error %d.\n", GetLastError());
    }

    ret = pCheckRemoteDebuggerPresent(pi.hProcess, &debug);
    ok(ret, "CheckRemoteDebuggerPresent failed, last error %d.\n", GetLastError());
    ok(debug, "Expected debug != 0, got %x.\n", debug);

    for (;;)
    {
        DEBUG_EVENT ev;

        ret = WaitForDebugEvent(&ev, INFINITE);
        ok(ret, "WaitForDebugEvent failed, last error %d.\n", GetLastError());
        if (!ret) break;

        if (ev.dwDebugEventCode==EXIT_PROCESS_DEBUG_EVENT && ev.dwProcessId==pi.dwProcessId) break;
        else if (ev.dwProcessId != pi.dwProcessId) got_child_event = TRUE;

        ret = ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, DBG_CONTINUE);
        ok(ret, "ContinueDebugEvent failed, last error %d.\n", GetLastError());
        if (!ret) break;
    }
    if(debug_child)
        ok(got_child_event, "didn't get any child events (flag: %x).\n", flag);
    else
        ok(!got_child_event, "got child event (flag: %x).\n", flag);
    CloseHandle(event_init);
    CloseHandle(event_attach);

    ret = CloseHandle(pi.hThread);
    ok(ret, "CloseHandle failed, last error %d.\n", GetLastError());
    ret = CloseHandle(pi.hProcess);
    ok(ret, "CloseHandle failed, last error %d.\n", GetLastError());

    load_blackbox(blackbox_file, &blackbox, sizeof(blackbox));
    ok(!blackbox.failures, "Got %d failures from child process.\n", blackbox.failures);

    ret = DeleteFileA(blackbox_file);
    ok(ret, "DeleteFileA failed, last error %d.\n", GetLastError());
}