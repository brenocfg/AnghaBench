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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SERVER_ACCESS_ADMINISTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  emptyW ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ pXcvClosePort (int /*<<< orphan*/ *) ; 
 scalar_t__ pXcvOpenPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_XcvClosePort(void)
{
    DWORD   res;
    HANDLE hXcv2;


    if (0)
    {
        /* crash with native localspl.dll (w2k+xp) */
        pXcvClosePort(NULL);
        pXcvClosePort(INVALID_HANDLE_VALUE);
    }


    SetLastError(0xdeadbeef);
    hXcv2 = (HANDLE) 0xdeadbeef;
    res = pXcvOpenPort(emptyW, SERVER_ACCESS_ADMINISTER, &hXcv2);
    ok(res, "returned %d with %u and %p (expected '!= 0')\n", res, GetLastError(), hXcv2);

    if (res) {
        SetLastError(0xdeadbeef);
        res = pXcvClosePort(hXcv2);
        ok(res, "returned %d with %u (expected '!= 0')\n", res, GetLastError());

        if (0)
        {
            /* test for "Double Free": crash with native localspl.dll (w2k+xp) */
            pXcvClosePort(hXcv2);
        }
    }
}