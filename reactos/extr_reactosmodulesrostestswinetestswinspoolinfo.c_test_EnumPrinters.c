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
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ EnumPrintersA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ EnumPrintersW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PRINTER_ENUM_LOCAL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ is_spooler_deactivated (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_EnumPrinters(void)
{
    DWORD neededA, neededW, num;
    DWORD ret;

    SetLastError(0xdeadbeef);
    neededA = -1;
    ret = EnumPrintersA(PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &neededA, &num);
    if (is_spooler_deactivated(ret, GetLastError())) return;
    if (!ret)
    {
        /* We have 1 or more printers */
        ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "gle %d\n", GetLastError());
        ok(neededA > 0, "Expected neededA to show the number of needed bytes\n");
    }
    else
    {
        /* We don't have any printers defined */
        ok(GetLastError() == S_OK, "gle %d\n", GetLastError());
        ok(neededA == 0, "Expected neededA to be zero\n");
    }
    ok(num == 0, "num %d\n", num);

    SetLastError(0xdeadbeef);
    neededW = -1;
    ret = EnumPrintersW(PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &neededW, &num);
    /* EnumPrintersW is not supported on all platforms */
    if (!ret && (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED))
    {
        win_skip("EnumPrintersW is not implemented\n");
        return;
    }

    if (!ret)
    {
        /* We have 1 or more printers */
        ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "gle %d\n", GetLastError());
        ok(neededW > 0, "Expected neededW to show the number of needed bytes\n");
    }
    else
    {
        /* We don't have any printers defined */
        ok(GetLastError() == S_OK, "gle %d\n", GetLastError());
        ok(neededW == 0, "Expected neededW to be zero\n");
    }
    ok(num == 0, "num %d\n", num);

    /* Outlook2003 relies on the buffer size returned by EnumPrintersA being big enough
       to hold the buffer returned by EnumPrintersW */
    ok(neededA == neededW, "neededA %d neededW %d\n", neededA, neededW);
}