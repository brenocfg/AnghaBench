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
struct child_blackbox {int /*<<< orphan*/  failures; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  blackbox ;
struct TYPE_7__ {int /*<<< orphan*/ * hProcess; int /*<<< orphan*/ * hThread; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int INFINITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * OpenEventA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  child_failures ; 
 int /*<<< orphan*/  child_ok (int,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_blackbox (char const*,struct child_blackbox*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void doChildren(int argc, char **argv)
{
    const char *arguments = "debugger children last";
    struct child_blackbox blackbox;
    const char *blackbox_file, *p;
    char event_name[MAX_PATH];
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    HANDLE event;
    char *cmd;
    BOOL ret;

    if (!strcmp(argv[3], "last")) return;

    blackbox_file = argv[3];

    p = strrchr(blackbox_file, '\\');
    p = p ? p+1 : blackbox_file;
    strcpy(event_name, p);
    strcat(event_name, "_init");
    event = OpenEventA(EVENT_ALL_ACCESS, FALSE, event_name);
    child_ok(event != NULL, "OpenEvent failed, last error %d.\n", GetLastError());
    SetEvent(event);
    CloseHandle(event);

    p = strrchr(blackbox_file, '\\');
    p = p ? p+1 : blackbox_file;
    strcpy(event_name, p);
    strcat(event_name, "_attach");
    event = OpenEventA(EVENT_ALL_ACCESS, FALSE, event_name);
    child_ok(event != NULL, "OpenEvent failed, last error %d.\n", GetLastError());
    WaitForSingleObject(event, INFINITE);
    CloseHandle(event);

    cmd = HeapAlloc(GetProcessHeap(), 0, strlen(argv[0]) + strlen(arguments) + 2);
    sprintf(cmd, "%s %s", argv[0], arguments);

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    ret = CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    child_ok(ret, "CreateProcess failed, last error %d.\n", GetLastError());

    child_ok(WaitForSingleObject(pi.hProcess, 10000) == WAIT_OBJECT_0,
            "Timed out waiting for the child to exit\n");

    ret = CloseHandle(pi.hThread);
    child_ok(ret, "CloseHandle failed, last error %d.\n", GetLastError());
    ret = CloseHandle(pi.hProcess);
    child_ok(ret, "CloseHandle failed, last error %d.\n", GetLastError());

    blackbox.failures = child_failures;
    save_blackbox(blackbox_file, &blackbox, sizeof(blackbox));

    HeapFree(GetProcessHeap(), 0, cmd);
}