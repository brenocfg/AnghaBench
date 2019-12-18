#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwMonitorSize; } ;
typedef  int /*<<< orphan*/  MONITOR ;
typedef  TYPE_1__* LPMONITOREX ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * Monitors_LocalPortW ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* pInitializePrintMonitor (int /*<<< orphan*/ *) ; 
 TYPE_1__* pm ; 

__attribute__((used)) static void test_InitializePrintMonitor(void)
{
    LPMONITOREX res;

    if (!pInitializePrintMonitor) return;

    SetLastError(0xdeadbeef);
    res = pInitializePrintMonitor(NULL);
    /* The Parameter was unchecked before w2k */
    ok( res || (GetLastError() == ERROR_INVALID_PARAMETER),
        "returned %p with %u\n (expected '!= NULL' or: NULL with "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pInitializePrintMonitor(emptyW);
    ok( res || (GetLastError() == ERROR_INVALID_PARAMETER),
        "returned %p with %u\n (expected '!= NULL' or: NULL with "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());

    /* Every call with a non-empty string returns the same Pointer */
    SetLastError(0xdeadbeef);
    res = pInitializePrintMonitor(Monitors_LocalPortW);
    ok( res == pm,
        "returned %p with %u (expected %p)\n", res, GetLastError(), pm);
    ok(res->dwMonitorSize == sizeof(MONITOR), "wrong dwMonitorSize %u\n", res->dwMonitorSize);
}