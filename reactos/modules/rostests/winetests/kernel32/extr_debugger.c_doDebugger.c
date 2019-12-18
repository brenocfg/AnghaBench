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
struct TYPE_3__ {int argc; void* detach_rc; void* detach_err; scalar_t__ pid; void* nokill_rc; void* nokill_err; void* debug_rc; void* debug_err; void* attach_rc; void* attach_err; } ;
typedef  TYPE_1__ debugger_blackbox_t ;
typedef  int /*<<< orphan*/  blackbox ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 void* DebugActiveProcess (scalar_t__) ; 
 int /*<<< orphan*/  ExitProcess (int) ; 
 int /*<<< orphan*/  FALSE ; 
 void* GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 void* SetEvent (int /*<<< orphan*/ *) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atol (char*) ; 
 int /*<<< orphan*/  get_events (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * myARGV ; 
 void* pDebugActiveProcessStop (scalar_t__) ; 
 void* pDebugSetProcessKillOnExit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_blackbox (char const*,TYPE_1__*,int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void doDebugger(int argc, char** argv)
{
    const char* logfile;
    debugger_blackbox_t blackbox;
    HANDLE start_event = 0, done_event = 0, debug_event;

    blackbox.argc=argc;
    logfile=(argc >= 4 ? argv[3] : NULL);
    blackbox.pid=(argc >= 5 ? atol(argv[4]) : 0);

    blackbox.attach_err=0;
    if (strstr(myARGV[2], "attach"))
    {
        blackbox.attach_rc=DebugActiveProcess(blackbox.pid);
        if (!blackbox.attach_rc)
            blackbox.attach_err=GetLastError();
    }
    else
        blackbox.attach_rc=TRUE;

    debug_event=(argc >= 6 ? (HANDLE)(INT_PTR)atol(argv[5]) : NULL);
    blackbox.debug_err=0;
    if (debug_event && strstr(myARGV[2], "event"))
    {
        blackbox.debug_rc=SetEvent(debug_event);
        if (!blackbox.debug_rc)
            blackbox.debug_err=GetLastError();
    }
    else
        blackbox.debug_rc=TRUE;

    if (logfile)
    {
        get_events(logfile, &start_event, &done_event);
    }

    if (strstr(myARGV[2], "order"))
    {
        trace("debugger: waiting for the start signal...\n");
        WaitForSingleObject(start_event, INFINITE);
    }

    blackbox.nokill_err=0;
    if (strstr(myARGV[2], "nokill"))
    {
        blackbox.nokill_rc=pDebugSetProcessKillOnExit(FALSE);
        if (!blackbox.nokill_rc)
            blackbox.nokill_err=GetLastError();
    }
    else
        blackbox.nokill_rc=TRUE;

    blackbox.detach_err=0;
    if (strstr(myARGV[2], "detach"))
    {
        blackbox.detach_rc=pDebugActiveProcessStop(blackbox.pid);
        if (!blackbox.detach_rc)
            blackbox.detach_err=GetLastError();
    }
    else
        blackbox.detach_rc=TRUE;

    if (logfile)
    {
        save_blackbox(logfile, &blackbox, sizeof(blackbox));
    }
    trace("debugger: done debugging...\n");
    SetEvent(done_event);

    /* Just exit with a known value */
    ExitProcess(0xdeadbeef);
}