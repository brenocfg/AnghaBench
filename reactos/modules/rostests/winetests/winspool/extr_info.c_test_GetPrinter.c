#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pDriverName; int /*<<< orphan*/ * pPrinterName; } ;
typedef  TYPE_1__ PRINTER_INFO_2A ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ClosePrinter (scalar_t__) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_LEVEL ; 
 int ERROR_NOT_SUPPORTED ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int GetPrinterA (scalar_t__,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OpenPrinterA (int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int default_printer ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  on_win9x ; 
 int pGetPrinterW (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*,int) ; 

__attribute__((used)) static void test_GetPrinter(void)
{
    HANDLE hprn;
    BOOL ret;
    BYTE *buf;
    INT level;
    DWORD needed, filled;

    if (!default_printer)
    {
        skip("There is no default printer installed\n");
        return;
    }

    hprn = 0;
    ret = OpenPrinterA(default_printer, &hprn, NULL);
    if (!ret)
    {
        skip("Unable to open the default printer (%s)\n", default_printer);
        return;
    }
    ok(hprn != 0, "wrong hprn %p\n", hprn);

    for (level = 1; level <= 9; level++)
    {
        SetLastError(0xdeadbeef);
        needed = (DWORD)-1;
        ret = GetPrinterA(hprn, level, NULL, 0, &needed);
        if (ret)
        {
            win_skip("Level %d is not supported on Win9x/WinMe\n", level);
            ok(GetLastError() == ERROR_SUCCESS, "wrong error %d\n", GetLastError());
            ok(needed == 0,"Expected 0, got %d\n", needed);
            continue;
        }
        ok(!ret, "level %d: GetPrinter should fail\n", level);
        /* Not all levels are supported on all Windows-Versions */
        if (GetLastError() == ERROR_INVALID_LEVEL ||
            GetLastError() == ERROR_NOT_SUPPORTED /* Win9x/WinMe */)
        {
            skip("Level %d not supported\n", level);
            continue;
        }
        ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "wrong error %d\n", GetLastError());
        ok(needed > 0,"not expected needed buffer size %d\n", needed);

        /* GetPrinterA returns the same number of bytes as GetPrinterW */
        if (!on_win9x && !ret && pGetPrinterW && level != 6 && level != 7)
        {
            DWORD double_needed;
            ret = pGetPrinterW(hprn, level, NULL, 0, &double_needed);
            ok(!ret, "level %d: GetPrinter error %d\n", level, GetLastError());
            ok(double_needed == needed, "level %d: GetPrinterA returned different size %d than GetPrinterW (%d)\n", level, needed, double_needed);
        }

        buf = HeapAlloc(GetProcessHeap(), 0, needed);

        SetLastError(0xdeadbeef);
        filled = -1;
        ret = GetPrinterA(hprn, level, buf, needed, &filled);
        ok(ret, "level %d: GetPrinter error %d\n", level, GetLastError());
        ok(needed == filled, "needed %d != filled %d\n", needed, filled);

        if (level == 2)
        {
            PRINTER_INFO_2A *pi_2 = (PRINTER_INFO_2A *)buf;

            ok(pi_2->pPrinterName!= NULL, "not expected NULL ptr\n");
            ok(pi_2->pDriverName!= NULL, "not expected NULL ptr\n");

            trace("pPrinterName %s\n", pi_2->pPrinterName);
            trace("pDriverName %s\n", pi_2->pDriverName);
        }

        HeapFree(GetProcessHeap(), 0, buf);
    }

    SetLastError(0xdeadbeef);
    ret = ClosePrinter(hprn);
    ok(ret, "ClosePrinter error %d\n", GetLastError());
}