#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int ERROR_INVALID_HANDLE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  UnhookWindowsHookEx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hCBT_hook ; 
 scalar_t__ hEvent_hook ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pUnhookWinEvent (scalar_t__) ; 
 int /*<<< orphan*/  sequence_cs ; 

__attribute__((used)) static void cleanup_tests()
{
    BOOL ret;
    UnhookWindowsHookEx(hCBT_hook);
    if (pUnhookWinEvent && hEvent_hook)
    {
        ret = pUnhookWinEvent(hEvent_hook);
        ok( ret, "UnhookWinEvent error %d\n", GetLastError());
        SetLastError(0xdeadbeef);
        ok(!pUnhookWinEvent(hEvent_hook), "UnhookWinEvent succeeded\n");
        ok(GetLastError() == ERROR_INVALID_HANDLE || /* Win2k */
           GetLastError() == 0xdeadbeef, /* Win9x */
           "unexpected error %d\n", GetLastError());
    }
    DeleteCriticalSection( &sequence_cs );

}