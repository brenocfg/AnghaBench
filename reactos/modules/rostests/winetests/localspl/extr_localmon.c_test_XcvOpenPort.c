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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SERVER_ACCESS_ADMINISTER ; 
 int /*<<< orphan*/  SERVER_ALL_ACCESS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pXcvClosePort (scalar_t__) ; 
 scalar_t__ pXcvOpenPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * portname_fileW ; 
 int /*<<< orphan*/ * portname_lpt1W ; 

__attribute__((used)) static void test_XcvOpenPort(void)
{
    DWORD   res;
    HANDLE  hXcv2;


    if (0)
    {
        /* crash with native localspl.dll (w2k+xp) */
        pXcvOpenPort(NULL, SERVER_ACCESS_ADMINISTER, &hXcv2);
        pXcvOpenPort(emptyW, SERVER_ACCESS_ADMINISTER, NULL);
    }


    /* The returned handle is the result from a previous "spoolss.dll,DllAllocSplMem" */
    SetLastError(0xdeadbeef);
    hXcv2 = (HANDLE) 0xdeadbeef;
    res = pXcvOpenPort(emptyW, SERVER_ACCESS_ADMINISTER, &hXcv2);
    ok(res, "returned %d with %u and %p (expected '!= 0')\n", res, GetLastError(), hXcv2);
    if (res) pXcvClosePort(hXcv2);


    /* The ACCESS_MASK is not checked in XcvOpenPort */
    SetLastError(0xdeadbeef);
    hXcv2 = (HANDLE) 0xdeadbeef;
    res = pXcvOpenPort(emptyW, 0, &hXcv2);
    ok(res, "returned %d with %u and %p (expected '!= 0')\n", res, GetLastError(), hXcv2);
    if (res) pXcvClosePort(hXcv2);


    /* A copy of pszObject is saved in the Memory-Block */
    SetLastError(0xdeadbeef);
    hXcv2 = (HANDLE) 0xdeadbeef;
    res = pXcvOpenPort(portname_lpt1W, SERVER_ALL_ACCESS, &hXcv2);
    ok(res, "returned %d with %u and %p (expected '!= 0')\n", res, GetLastError(), hXcv2);
    if (res) pXcvClosePort(hXcv2);

    SetLastError(0xdeadbeef);
    hXcv2 = (HANDLE) 0xdeadbeef;
    res = pXcvOpenPort(portname_fileW, SERVER_ALL_ACCESS, &hXcv2);
    ok(res, "returned %d with %u and %p (expected '!= 0')\n", res, GetLastError(), hXcv2);
    if (res) pXcvClosePort(hXcv2);

}