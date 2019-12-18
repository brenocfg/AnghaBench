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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * cmd_MonitorUIW ; 
 int /*<<< orphan*/ * cmd_MonitorUI_lcaseW ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/ * hXcv ; 
 int /*<<< orphan*/ * hXcv_noaccess ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pXcvDataPort (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 

__attribute__((used)) static void test_XcvDataPort_MonitorUI(void)
{
    DWORD   res;
    BYTE    buffer[MAX_PATH + 2];
    DWORD   needed;
    DWORD   len;


    /* ask for needed size */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, NULL, 0, &needed);
    if (res == ERROR_INVALID_PARAMETER) {
        skip("'MonitorUI' nor supported\n");
        return;
    }
    ok( (res == ERROR_INSUFFICIENT_BUFFER) && (needed <= MAX_PATH),
        "returned %d with %u and 0x%x (expected 'ERROR_INSUFFICIENT_BUFFER' "
        " and '<= MAX_PATH')\n", res, GetLastError(), needed);

    if (needed > MAX_PATH) {
        skip("buffer overflow (%u)\n", needed);
        return;
    }
    len = needed;

    /* the command is required */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, emptyW, NULL, 0, NULL, 0, &needed);
    ok( res == ERROR_INVALID_PARAMETER, "returned %d with %u and 0x%x "
        "(expected 'ERROR_INVALID_PARAMETER')\n", res, GetLastError(), needed);

    if (0) {
        /* crash with native localspl.dll (w2k+xp) */
        pXcvDataPort(hXcv, NULL, NULL, 0, buffer, MAX_PATH, &needed);
        pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, NULL, len, &needed);
        pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len, NULL);
    }


    /* hXcv is ignored for the command "MonitorUI" */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(NULL, cmd_MonitorUIW, NULL, 0, buffer, len, &needed);
    ok( res == ERROR_SUCCESS, "returned %d with %u and 0x%x "
        "(expected 'ERROR_SUCCESS')\n", res, GetLastError(), needed);


    /* pszDataName is case-sensitive */
    memset(buffer, 0, len);
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_MonitorUI_lcaseW, NULL, 0, buffer, len, &needed);
    ok( res == ERROR_INVALID_PARAMETER, "returned %d with %u and 0x%x "
        "(expected 'ERROR_INVALID_PARAMETER')\n", res, GetLastError(), needed);

    /* off by one: larger  */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len+1, &needed);
    ok( res == ERROR_SUCCESS, "returned %d with %u and 0x%x "
        "(expected 'ERROR_SUCCESS')\n", res, GetLastError(), needed);


    /* off by one: smaller */
    /* the buffer is not modified for NT4, w2k, XP */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len-1, &needed);
    ok( res == ERROR_INSUFFICIENT_BUFFER, "returned %d with %u and 0x%x "
        "(expected 'ERROR_INSUFFICIENT_BUFFER')\n", res, GetLastError(), needed);

    /* Normal use. The DLL-Name without a Path is returned */
    memset(buffer, 0, len);
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len, &needed);
    ok( res == ERROR_SUCCESS, "returned %d with %u and 0x%x "
        "(expected 'ERROR_SUCCESS')\n", res, GetLastError(), needed);


    /* small check without access-rights: */
    if (!hXcv_noaccess) return;

    /* The ACCESS_MASK is ignored for "MonitorUI" */
    memset(buffer, 0, len);
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv_noaccess, cmd_MonitorUIW, NULL, 0, buffer, sizeof(buffer), &needed);
    ok( res == ERROR_SUCCESS, "returned %d with %u and 0x%x "
        "(expected 'ERROR_SUCCESS')\n", res, GetLastError(), needed);
}