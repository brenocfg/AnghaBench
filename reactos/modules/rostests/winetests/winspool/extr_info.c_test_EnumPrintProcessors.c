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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_ENVIRONMENT ; 
 scalar_t__ ERROR_INVALID_LEVEL ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_INVALID_USER_BUFFER ; 
 int EnumPrintProcessorsA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*,int*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RPC_X_NULL_REF_POINTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * empty ; 
 int /*<<< orphan*/ * invalid_env ; 
 scalar_t__ is_spooler_deactivated (int,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_EnumPrintProcessors(void)
{
    DWORD   res;
    LPBYTE  buffer;
    DWORD   cbBuf;
    DWORD   pcbNeeded;
    DWORD   pcReturned;


    cbBuf = 0xdeadbeef;
    pcReturned = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = EnumPrintProcessorsA(NULL, NULL, 1, NULL, 0, &cbBuf, &pcReturned);
    if (is_spooler_deactivated(res, GetLastError())) return;

    if (res && !cbBuf) {
        skip("No Printprocessor installed\n");
        return;
    }

    ok((!res) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "got %u with %u (expected '0' with ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError());

    buffer = HeapAlloc(GetProcessHeap(), 0, cbBuf + 4);
    if (buffer == NULL)
        return;

    SetLastError(0xdeadbeef);
    pcbNeeded = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, NULL, 1, buffer, cbBuf, &pcbNeeded, &pcReturned);
    ok(res, "got %u with %u (expected '!=0')\n", res, GetLastError());
    /* validate the returned data here. */


    SetLastError(0xdeadbeef);
    pcReturned = 0xdeadbeef;
    pcbNeeded = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, NULL, 1, buffer, cbBuf+1, &pcbNeeded, &pcReturned);
    ok(res, "got %u with %u (expected '!=0')\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    pcbNeeded = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, NULL, 1, buffer, cbBuf-1, &pcbNeeded, &pcReturned);
    ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "got %u with %u (expected '0' with ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError());

    /* only level 1 is valid */
    if (0) {
        /* both tests crash on win98se */
        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        res = EnumPrintProcessorsA(NULL, NULL, 0, buffer, cbBuf, &pcbNeeded, &pcReturned);
        ok( !res && (GetLastError() == ERROR_INVALID_LEVEL),
            "got %u with %u (expected '0' with ERROR_INVALID_LEVEL)\n",
            res, GetLastError());

        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        res = EnumPrintProcessorsA(NULL, NULL, 2, buffer, cbBuf, &pcbNeeded, &pcReturned);
        ok( !res && (GetLastError() == ERROR_INVALID_LEVEL),
            "got %u with %u (expected '0' with ERROR_INVALID_LEVEL)\n",
            res, GetLastError());
    }

    /* an empty environment is ignored */
    SetLastError(0xdeadbeef);
    pcbNeeded = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, empty, 1, buffer, cbBuf, &pcbNeeded, &pcReturned);
    ok(res, "got %u with %u (expected '!=0')\n", res, GetLastError());

    /* the environment is checked */
    SetLastError(0xdeadbeef);
    pcbNeeded = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, invalid_env, 1, buffer, cbBuf, &pcbNeeded, &pcReturned);
    /* NT5: ERROR_INVALID_ENVIRONMENT, NT4: res != 0, 9x: ERROR_INVALID_PARAMETER */
    ok( broken(res) || /* NT4 */
        (GetLastError() == ERROR_INVALID_ENVIRONMENT) ||
        (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_ENVIRONMENT or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());


    /* failure-Codes for NULL */
    if (0) {
        /* this test crashes on win98se */
        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        res = EnumPrintProcessorsA(NULL, NULL, 1, NULL, cbBuf, &pcbNeeded, &pcReturned);
        ok( !res && (GetLastError() == ERROR_INVALID_USER_BUFFER) ,
            "got %u with %u (expected '0' with ERROR_INVALID_USER_BUFFER)\n",
            res, GetLastError());
    }

    SetLastError(0xdeadbeef);
    pcbNeeded = 0xdeadbeef;
    pcReturned = 0xdeadbeef;
    res = EnumPrintProcessorsA(NULL, NULL, 1, buffer, cbBuf, NULL, &pcReturned);
    /* the NULL is ignored on win9x */
    ok( broken(res) || (!res && (GetLastError() == RPC_X_NULL_REF_POINTER)),
        "got %u with %u (expected '0' with RPC_X_NULL_REF_POINTER)\n",
        res, GetLastError());

    pcbNeeded = 0xdeadbeef;
    pcReturned = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = EnumPrintProcessorsA(NULL, NULL, 1, buffer, cbBuf, &pcbNeeded, NULL);
    /* the NULL is ignored on win9x */
    ok( broken(res) || (!res && (GetLastError() == RPC_X_NULL_REF_POINTER)),
        "got %u with %u (expected '0' with RPC_X_NULL_REF_POINTER)\n",
        res, GetLastError());

    HeapFree(GetProcessHeap(), 0, buffer);

}