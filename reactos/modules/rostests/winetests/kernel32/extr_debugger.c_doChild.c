#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct child_blackbox {int /*<<< orphan*/  failures; } ;
typedef  int /*<<< orphan*/  blackbox ;
struct TYPE_4__ {TYPE_1__* Peb; } ;
struct TYPE_3__ {int /*<<< orphan*/  BeingDebugged; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ ) ; 
 int DebugActiveProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 TYPE_2__* NtCurrentTeb () ; 
 int /*<<< orphan*/  OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_QUERY_INFORMATION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  child_failures ; 
 int /*<<< orphan*/  child_ok (int,char*,int) ; 
 int pCheckRemoteDebuggerPresent (int /*<<< orphan*/ ,int*) ; 
 int pDebugActiveProcessStop (int /*<<< orphan*/ ) ; 
 int pIsDebuggerPresent () ; 
 int /*<<< orphan*/  save_blackbox (char const*,struct child_blackbox*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void doChild(int argc, char **argv)
{
    struct child_blackbox blackbox;
    const char *blackbox_file;
    HANDLE parent;
    DWORD ppid;
    BOOL debug;
    BOOL ret;

    blackbox_file = argv[4];
    sscanf(argv[3], "%08x", &ppid);

    parent = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ppid);
    child_ok(!!parent, "OpenProcess failed, last error %#x.\n", GetLastError());

    ret = pCheckRemoteDebuggerPresent(parent, &debug);
    child_ok(ret, "CheckRemoteDebuggerPresent failed, last error %#x.\n", GetLastError());
    child_ok(!debug, "Expected debug == 0, got %#x.\n", debug);

    ret = DebugActiveProcess(ppid);
    child_ok(ret, "DebugActiveProcess failed, last error %#x.\n", GetLastError());

    ret = pCheckRemoteDebuggerPresent(parent, &debug);
    child_ok(ret, "CheckRemoteDebuggerPresent failed, last error %#x.\n", GetLastError());
    child_ok(debug, "Expected debug != 0, got %#x.\n", debug);

    ret = pDebugActiveProcessStop(ppid);
    child_ok(ret, "DebugActiveProcessStop failed, last error %#x.\n", GetLastError());

    ret = pCheckRemoteDebuggerPresent(parent, &debug);
    child_ok(ret, "CheckRemoteDebuggerPresent failed, last error %#x.\n", GetLastError());
    child_ok(!debug, "Expected debug == 0, got %#x.\n", debug);

    ret = CloseHandle(parent);
    child_ok(ret, "CloseHandle failed, last error %#x.\n", GetLastError());

    ret = pIsDebuggerPresent();
    child_ok(ret, "Expected ret != 0, got %#x.\n", ret);
    ret = pCheckRemoteDebuggerPresent(GetCurrentProcess(), &debug);
    child_ok(ret, "CheckRemoteDebuggerPresent failed, last error %#x.\n", GetLastError());
    child_ok(debug, "Expected debug != 0, got %#x.\n", debug);

    NtCurrentTeb()->Peb->BeingDebugged = FALSE;

    ret = pIsDebuggerPresent();
    child_ok(!ret, "Expected ret != 0, got %#x.\n", ret);
    ret = pCheckRemoteDebuggerPresent(GetCurrentProcess(), &debug);
    child_ok(ret, "CheckRemoteDebuggerPresent failed, last error %#x.\n", GetLastError());
    child_ok(debug, "Expected debug != 0, got %#x.\n", debug);

    NtCurrentTeb()->Peb->BeingDebugged = TRUE;

    blackbox.failures = child_failures;
    save_blackbox(blackbox_file, &blackbox, sizeof(blackbox));
}