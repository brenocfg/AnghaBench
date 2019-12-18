#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pName; } ;
struct TYPE_3__ {int /*<<< orphan*/  pName; int /*<<< orphan*/  pDriverPath; } ;
typedef  TYPE_1__* LPDRIVER_INFO_2A ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;
typedef  TYPE_2__ DRIVER_INFO_1A ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_ENVIRONMENT ; 
 int /*<<< orphan*/  ERROR_INVALID_LEVEL ; 
 int EnumPrinterDriversA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_X_NULL_REF_POINTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * default_printer ; 
 scalar_t__ is_spooler_deactivated (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  on_win9x ; 
 int /*<<< orphan*/  pEnumPrinterDriversW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/ * strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_EnumPrinterDrivers(void)
{
    static char env_all[] = "all";

    DWORD   res;
    LPBYTE  buffer;
    DWORD   cbBuf;
    DWORD   pcbNeeded;
    DWORD   pcReturned;
    DWORD   level;

    /* 1-3 for w95/w98/NT4; 1-3+6 for me; 1-6 for w2k/xp/2003; 1-6+8 for vista */
    for(level = 0; level < 10; level++) {
        cbBuf = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = EnumPrinterDriversA(NULL, NULL, level, NULL, 0, &cbBuf, &pcReturned);
        if (is_spooler_deactivated(res, GetLastError())) return;

        /* use only a short test when testing an invalid level */
        if(!level || (level == 7) || (level > 8)) {

            ok( (!res && (GetLastError() == ERROR_INVALID_LEVEL)) ||
                (res && (pcReturned == 0)),
                "(%d) got %u with %u and 0x%x "
                "(expected '0' with ERROR_INVALID_LEVEL or '!=0' and 0x0)\n",
                level, res, GetLastError(), pcReturned);
            continue;
        }

        /* some levels are not supported on all windows versions */
        if (!res && (GetLastError() == ERROR_INVALID_LEVEL)) {
            skip("Level %d not supported\n", level);
            continue;
        }

        ok( ((!res) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER)) ||
            (res && (default_printer == NULL)),
            "(%u) got %u with %u for %s (expected '0' with "
            "ERROR_INSUFFICIENT_BUFFER or '!= 0' without a printer)\n",
            level, res, GetLastError(), default_printer);

        if (!cbBuf) {
            skip("no valid buffer size returned\n");
            continue;
        }

        /* EnumPrinterDriversA returns the same number of bytes as EnumPrinterDriversW */
        if (!on_win9x && pEnumPrinterDriversW)
        {
            DWORD double_needed;
            DWORD double_returned;
            pEnumPrinterDriversW(NULL, NULL, level, NULL, 0, &double_needed, &double_returned);
            ok(double_needed == cbBuf, "level %d: EnumPrinterDriversA returned different size %d than EnumPrinterDriversW (%d)\n", level, cbBuf, double_needed);
        }

        buffer = HeapAlloc(GetProcessHeap(), 0, cbBuf + 4);
        if (buffer == NULL) continue;

        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        res = EnumPrinterDriversA(NULL, NULL, level, buffer, cbBuf, &pcbNeeded, &pcReturned);
        ok(res, "(%u) got %u with %u (expected '!=0')\n", level, res, GetLastError());
        ok(pcbNeeded == cbBuf, "(%d) returned %d (expected %d)\n", level, pcbNeeded, cbBuf);

        /* validate the returned data here */
        if (level > 1) {
            LPDRIVER_INFO_2A di = (LPDRIVER_INFO_2A) buffer;

            ok( strrchr(di->pDriverPath, '\\') != NULL,
                "(%u) got %s for %s (expected a full path)\n",
                level, di->pDriverPath, di->pName);

        }

        SetLastError(0xdeadbeef);
        pcReturned = 0xdeadbeef;
        pcbNeeded = 0xdeadbeef;
        res = EnumPrinterDriversA(NULL, NULL, level, buffer, cbBuf+1, &pcbNeeded, &pcReturned);
        ok(res, "(%u) got %u with %u (expected '!=0')\n", level, res, GetLastError());
        ok(pcbNeeded == cbBuf, "(%u) returned %u (expected %u)\n", level, pcbNeeded, cbBuf);

        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        res = EnumPrinterDriversA(NULL, NULL, level, buffer, cbBuf-1, &pcbNeeded, &pcReturned);
        ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
            "(%u) got %u with %u (expected '0' with ERROR_INSUFFICIENT_BUFFER)\n",
            level, res, GetLastError());
        ok(pcbNeeded == cbBuf, "(%u) returned %u (expected %u)\n", level, pcbNeeded, cbBuf);

/*
      Do not add the next test:
      NT: ERROR_INVALID_USER_BUFFER
      win9x: crash or 100% CPU

      res = EnumPrinterDriversA(NULL, NULL, level, NULL, cbBuf, &pcbNeeded, &pcReturned);
*/

        SetLastError(0xdeadbeef);
        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        res = EnumPrinterDriversA(NULL, NULL, level, buffer, cbBuf, NULL, &pcReturned);
        ok( res || GetLastError() == RPC_X_NULL_REF_POINTER,
            "(%u) got %u with %u (expected '!=0' or '0' with "
            "RPC_X_NULL_REF_POINTER)\n", level, res, GetLastError());

        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = EnumPrinterDriversA(NULL, NULL, level, buffer, cbBuf, &pcbNeeded, NULL);
        ok( res || GetLastError() == RPC_X_NULL_REF_POINTER,
            "(%u) got %u with %u (expected '!=0' or '0' with "
            "RPC_X_NULL_REF_POINTER)\n", level, res, GetLastError());

        HeapFree(GetProcessHeap(), 0, buffer);
    } /* for(level ... */

    pcbNeeded = 0;
    pcReturned = 0;
    SetLastError(0xdeadbeef);
    res = EnumPrinterDriversA(NULL, env_all, 1, NULL, 0, &pcbNeeded, &pcReturned);
    if (res)
    {
        skip("no printer drivers found\n");
        return;
    }
    if (GetLastError() == ERROR_INVALID_ENVIRONMENT)
    {
        win_skip("NT4 and below don't support the 'all' environment value\n");
        return;
    }
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "unexpected error %u\n", GetLastError());

    buffer = HeapAlloc(GetProcessHeap(), 0, pcbNeeded);
    res = EnumPrinterDriversA(NULL, env_all, 1, buffer, pcbNeeded, &pcbNeeded, &pcReturned);
    ok(res, "EnumPrinterDriversA failed %u\n", GetLastError());
    if (res && pcReturned > 0)
    {
        DRIVER_INFO_1A *di_1 = (DRIVER_INFO_1A *)buffer;
        ok((LPBYTE) di_1->pName == NULL || (LPBYTE) di_1->pName < buffer ||
            (LPBYTE) di_1->pName >= (LPBYTE)(di_1 + pcReturned),
            "Driver Information not in sequence; pName %p, top of data %p\n",
            di_1->pName, di_1 + pcReturned);
    }

    HeapFree(GetProcessHeap(), 0, buffer);
}