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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * does_not_existW ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pAddPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_AddPort(void)
{
    DWORD   res;

    /* moved to localui.dll since w2k */
    if (!pAddPort) return;

    if (0)
    {
        /* NT4 crash on this test */
        pAddPort(NULL, 0, NULL);
    }

    /*  Testing-Results (localmon.dll from NT4.0):
        - The Servername is ignored
        - Case of MonitorName is ignored
    */

    SetLastError(0xdeadbeef);
    res = pAddPort(NULL, 0, emptyW);
    ok(!res, "returned %d with %u (expected '0')\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pAddPort(NULL, 0, does_not_existW);
    ok(!res, "returned %d with %u (expected '0')\n", res, GetLastError());

}