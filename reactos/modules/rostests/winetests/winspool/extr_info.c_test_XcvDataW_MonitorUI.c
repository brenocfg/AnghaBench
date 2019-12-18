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
struct TYPE_3__ {int /*<<< orphan*/  DesiredAccess; int /*<<< orphan*/ * pDevMode; int /*<<< orphan*/ * pDatatype; } ;
typedef  TYPE_1__ PRINTER_DEFAULTSA ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 scalar_t__ OpenPrinterA (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__*) ; 
 scalar_t__ RPC_X_NULL_REF_POINTER ; 
 int /*<<< orphan*/  SERVER_ACCESS_ADMINISTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * cmd_MonitorUIW ; 
 int /*<<< orphan*/ * emptyW ; 
 scalar_t__ is_access_denied (scalar_t__,scalar_t__) ; 
 scalar_t__ is_spooler_deactivated (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 scalar_t__ pXcvDataW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  skip (char*,scalar_t__) ; 
 int /*<<< orphan*/  xcv_localport ; 

__attribute__((used)) static void test_XcvDataW_MonitorUI(void)
{
    DWORD   res;
    HANDLE  hXcv;
    BYTE    buffer[MAX_PATH + 4];
    DWORD   needed;
    DWORD   status;
    DWORD   len;
    PRINTER_DEFAULTSA pd;

    /* api is not present before w2k */
    if (pXcvDataW == NULL) return;

    pd.pDatatype = NULL;
    pd.pDevMode  = NULL;
    pd.DesiredAccess = SERVER_ACCESS_ADMINISTER;

    hXcv = NULL;
    SetLastError(0xdeadbeef);
    res = OpenPrinterA(xcv_localport, &hXcv, &pd);
    if (is_spooler_deactivated(res, GetLastError())) return;
    if (is_access_denied(res, GetLastError())) return;

    ok(res, "returned %d with %u and handle %p (expected '!= 0')\n", res, GetLastError(), hXcv);
    if (!res) return;

    /* ask for needed size */
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, NULL, 0, &needed, &status);
    ok( res && (status == ERROR_INSUFFICIENT_BUFFER) && (needed <= MAX_PATH),
        "returned %d with %u and %u for status %u (expected '!= 0' and "
        "'<= MAX_PATH' for status ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError(), needed, status);

    if (needed > MAX_PATH) {
        ClosePrinter(hXcv);
        skip("buffer overflow (%u)\n", needed);
        return;
    }
    len = needed;       /* Size is in bytes */

    /* the command is required */
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, emptyW, NULL, 0, NULL, 0, &needed, &status);
    ok( res && (status == ERROR_INVALID_PARAMETER),
        "returned %d with %u and %u for status %u (expected '!= 0' with "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError(), needed, status);

    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, NULL, NULL, 0, buffer, MAX_PATH, &needed, &status);
    ok( !res && (GetLastError() == RPC_X_NULL_REF_POINTER),
        "returned %d with %u and %u for status %u (expected '0' with "
        "RPC_X_NULL_REF_POINTER)\n", res, GetLastError(), needed, status);

    /* "PDWORD needed" is checked before RPC-Errors */
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len, NULL, &status);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "returned %d with %u and %u for status %u (expected '0' with "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError(), needed, status);

    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, NULL, len, &needed, &status);
    ok( !res && (GetLastError() == RPC_X_NULL_REF_POINTER),
        "returned %d with %u and %u for status %u (expected '0' with "
        "RPC_X_NULL_REF_POINTER)\n", res, GetLastError(), needed, status);

    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len, &needed, NULL);
    ok( !res && (GetLastError() == RPC_X_NULL_REF_POINTER),
        "returned %d with %u and %u for status %u (expected '0' with "
        "RPC_X_NULL_REF_POINTER)\n", res, GetLastError(), needed, status);

    /* off by one: larger  */
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len+1, &needed, &status);
    ok( res && (status == ERROR_SUCCESS),
        "returned %d with %u and %u for status %u (expected '!= 0' for status "
        "ERROR_SUCCESS)\n", res, GetLastError(), needed, status);

    /* off by one: smaller */
    /* the buffer is not modified for NT4, w2k, XP */
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len-1, &needed, &status);
    ok( res && (status == ERROR_INSUFFICIENT_BUFFER),
        "returned %d with %u and %u for status %u (expected '!= 0' for status "
        "ERROR_INSUFFICIENT_BUFFER)\n", res, GetLastError(), needed, status);


    /* Normal use. The DLL-Name without a Path is returned */
    memset(buffer, 0, len);
    needed = (DWORD) 0xdeadbeef;
    status = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataW(hXcv, cmd_MonitorUIW, NULL, 0, buffer, len, &needed, &status);
    ok( res && (status == ERROR_SUCCESS),
        "returned %d with %u and %u for status %u (expected '!= 0' for status "
        "ERROR_SUCCESS)\n", res, GetLastError(), needed, status);

    ClosePrinter(hXcv);
}