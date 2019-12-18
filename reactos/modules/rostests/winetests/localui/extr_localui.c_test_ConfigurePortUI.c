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
struct TYPE_4__ {int /*<<< orphan*/ * pPortName; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pPortName; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_CANCELLED ; 
 scalar_t__ ERROR_INVALID_PRINTER_NAME ; 
 scalar_t__ ERROR_UNKNOWN_PORT ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * com_absent ; 
 TYPE_2__* com_present ; 
 int /*<<< orphan*/ * does_not_existW ; 
 int /*<<< orphan*/ * emptyW ; 
 scalar_t__ file_present ; 
 int /*<<< orphan*/ * lpt_absent ; 
 TYPE_1__* lpt_present ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ pConfigurePortUI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * portname_fileW ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_ConfigurePortUI(void)
{
    DWORD   res;

    /* not present before w2k */
    if (!pConfigurePortUI) {
        skip("ConfigurePortUI not found\n");
        return;
    }

    SetLastError(0xdeadbeef);
    res = pConfigurePortUI(NULL, NULL, NULL);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pConfigurePortUI(NULL, NULL, emptyW);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());


    SetLastError(0xdeadbeef);
    res = pConfigurePortUI(NULL, NULL, does_not_existW);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    if (winetest_interactive && lpt_present) {
        SetLastError(0xdeadbeef);
        res = pConfigurePortUI(NULL, NULL, lpt_present->pPortName);
        ok( res ||
            (GetLastError() == ERROR_CANCELLED) || (GetLastError() == ERROR_ACCESS_DENIED),
            "got %d with %u (expected '!= 0' or '0' with: ERROR_CANCELLED or "
            "ERROR_ACCESS_DENIED)\n", res, GetLastError());
    }

    if (lpt_absent) {
        SetLastError(0xdeadbeef);
        res = pConfigurePortUI(NULL, NULL, lpt_absent);
        ok( !res &&
            ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
            "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
            "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());
    }

    if (winetest_interactive && com_present) {
        SetLastError(0xdeadbeef);
        res = pConfigurePortUI(NULL, NULL, com_present->pPortName);
        ok( res ||
            (GetLastError() == ERROR_CANCELLED) || (GetLastError() == ERROR_ACCESS_DENIED),
            "got %d with %u (expected '!= 0' or '0' with: ERROR_CANCELLED or "
            "ERROR_ACCESS_DENIED)\n", res, GetLastError());
    }

    if (com_absent) {
        SetLastError(0xdeadbeef);
        res = pConfigurePortUI(NULL, NULL, com_absent);
        ok( !res &&
            ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
            "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
            "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    }

    if (winetest_interactive && file_present) {
        SetLastError(0xdeadbeef);
        res = pConfigurePortUI(NULL, NULL, portname_fileW);
        ok( !res &&
            ((GetLastError() == ERROR_CANCELLED) || (GetLastError() == ERROR_ACCESS_DENIED)),
            "got %d with %u (expected '0' with: ERROR_CANCELLED or "
            "ERROR_ACCESS_DENIED)\n", res, GetLastError());
    }
}