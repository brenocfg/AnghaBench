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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * GetCurrentProcess () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCheckRemoteDebuggerPresent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RemoteDebugger(void)
{
    BOOL bret, present;
    if(!pCheckRemoteDebuggerPresent)
    {
        win_skip("CheckRemoteDebuggerPresent is not available\n");
        return;
    }
    present = TRUE;
    SetLastError(0xdeadbeef);
    bret = pCheckRemoteDebuggerPresent(GetCurrentProcess(),&present);
    ok(bret , "expected CheckRemoteDebuggerPresent to succeed\n");
    ok(0xdeadbeef == GetLastError(),
       "expected error to be unchanged, got %d/%x\n",GetLastError(), GetLastError());

    present = TRUE;
    SetLastError(0xdeadbeef);
    bret = pCheckRemoteDebuggerPresent(NULL,&present);
    ok(!bret , "expected CheckRemoteDebuggerPresent to fail\n");
    ok(present, "expected parameter to be unchanged\n");
    ok(ERROR_INVALID_PARAMETER == GetLastError(),
       "expected error ERROR_INVALID_PARAMETER, got %d/%x\n",GetLastError(), GetLastError());

    SetLastError(0xdeadbeef);
    bret = pCheckRemoteDebuggerPresent(GetCurrentProcess(),NULL);
    ok(!bret , "expected CheckRemoteDebuggerPresent to fail\n");
    ok(ERROR_INVALID_PARAMETER == GetLastError(),
       "expected error ERROR_INVALID_PARAMETER, got %d/%x\n",GetLastError(), GetLastError());
}