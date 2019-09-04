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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  NTDLL_GET_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TpAllocCleanupGroup ; 
 int /*<<< orphan*/  TpAllocPool ; 
 int /*<<< orphan*/  TpAllocTimer ; 
 int /*<<< orphan*/  TpAllocWait ; 
 int /*<<< orphan*/  TpAllocWork ; 
 int /*<<< orphan*/  TpCallbackMayRunLong ; 
 int /*<<< orphan*/  TpCallbackReleaseSemaphoreOnCompletion ; 
 int /*<<< orphan*/  TpDisassociateCallback ; 
 int /*<<< orphan*/  TpIsTimerSet ; 
 int /*<<< orphan*/  TpPostWork ; 
 int /*<<< orphan*/  TpReleaseCleanupGroup ; 
 int /*<<< orphan*/  TpReleaseCleanupGroupMembers ; 
 int /*<<< orphan*/  TpReleasePool ; 
 int /*<<< orphan*/  TpReleaseTimer ; 
 int /*<<< orphan*/  TpReleaseWait ; 
 int /*<<< orphan*/  TpReleaseWork ; 
 int /*<<< orphan*/  TpSetPoolMaxThreads ; 
 int /*<<< orphan*/  TpSetTimer ; 
 int /*<<< orphan*/  TpSetWait ; 
 int /*<<< orphan*/  TpSimpleTryPost ; 
 int /*<<< orphan*/  TpWaitForTimer ; 
 int /*<<< orphan*/  TpWaitForWait ; 
 int /*<<< orphan*/  TpWaitForWork ; 
 int /*<<< orphan*/  hntdll ; 
 int /*<<< orphan*/  pTpAllocPool ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_threadpool(void)
{
    hntdll = GetModuleHandleA("ntdll");
    if (!hntdll)
    {
        win_skip("Could not load ntdll\n");
        return FALSE;
    }

    NTDLL_GET_PROC(TpAllocCleanupGroup);
    NTDLL_GET_PROC(TpAllocPool);
    NTDLL_GET_PROC(TpAllocTimer);
    NTDLL_GET_PROC(TpAllocWait);
    NTDLL_GET_PROC(TpAllocWork);
    NTDLL_GET_PROC(TpCallbackMayRunLong);
    NTDLL_GET_PROC(TpCallbackReleaseSemaphoreOnCompletion);
    NTDLL_GET_PROC(TpDisassociateCallback);
    NTDLL_GET_PROC(TpIsTimerSet);
    NTDLL_GET_PROC(TpPostWork);
    NTDLL_GET_PROC(TpReleaseCleanupGroup);
    NTDLL_GET_PROC(TpReleaseCleanupGroupMembers);
    NTDLL_GET_PROC(TpReleasePool);
    NTDLL_GET_PROC(TpReleaseTimer);
    NTDLL_GET_PROC(TpReleaseWait);
    NTDLL_GET_PROC(TpReleaseWork);
    NTDLL_GET_PROC(TpSetPoolMaxThreads);
    NTDLL_GET_PROC(TpSetTimer);
    NTDLL_GET_PROC(TpSetWait);
    NTDLL_GET_PROC(TpSimpleTryPost);
    NTDLL_GET_PROC(TpWaitForTimer);
    NTDLL_GET_PROC(TpWaitForWait);
    NTDLL_GET_PROC(TpWaitForWork);

    if (!pTpAllocPool)
    {
        win_skip("Threadpool functions not supported, skipping tests\n");
        return FALSE;
    }

    return TRUE;
}