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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  cmd_AddPortW ; 
 int /*<<< orphan*/  cmd_DeletePortW ; 
 int /*<<< orphan*/  hXcv ; 
 int lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pXcvDataPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ portname_lpt1W ; 
 scalar_t__ tempfileW ; 

__attribute__((used)) static void test_XcvDataPort_AddPort(void)
{
    DWORD   res;

    /*
     * The following tests crash with native localspl.dll on w2k and xp,
     * but it works, when the native dll (w2k and xp) is used in wine.
     * also tested (same crash): replacing emptyW with portname_lpt1W
     * and replacing "NULL, 0, NULL" with "buffer, MAX_PATH, &needed"
     *
     * We need to use a different API (AddPortEx) instead
     */
    if (0)
    {
    /* create a Port for a normal, writable file */
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_AddPortW, (PBYTE) tempfileW, (lstrlenW(tempfileW) + 1) * sizeof(WCHAR), NULL, 0, NULL);
    ok( res == ERROR_SUCCESS, "returned %d with %u (expected ERROR_SUCCESS)\n", res, GetLastError());

    /* add our testport again */
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_AddPortW, (PBYTE) tempfileW, (lstrlenW(tempfileW) + 1) * sizeof(WCHAR), NULL, 0, NULL);
    ok( res == ERROR_ALREADY_EXISTS, "returned %d with %u (expected ERROR_ALREADY_EXISTS)\n", res, GetLastError());

    /* create a well-known Port  */
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_AddPortW, (PBYTE) portname_lpt1W, (lstrlenW(portname_lpt1W) + 1) * sizeof(WCHAR), NULL, 0, NULL);
    ok( res == ERROR_ALREADY_EXISTS, "returned %d with %u (expected ERROR_ALREADY_EXISTS)\n", res, GetLastError());

    /* ERROR_ALREADY_EXISTS is also returned from native localspl.dll on wine,
       when "RPT1:" was already installed for redmonnt.dll:
       res = pXcvDataPort(hXcv, cmd_AddPortW, (PBYTE) portname_rpt1W, ...
    */

    /* cleanup */
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_DeletePortW, (PBYTE) tempfileW, (lstrlenW(tempfileW) + 1) * sizeof(WCHAR), NULL, 0, NULL);
    ok( res == ERROR_SUCCESS, "returned %d with %u (expected ERROR_SUCCESS)\n", res, GetLastError());
    }

}