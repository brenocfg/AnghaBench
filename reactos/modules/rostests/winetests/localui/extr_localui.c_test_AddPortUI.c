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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_CANCELLED ; 
 scalar_t__ ERROR_INVALID_PRINTER_NAME ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ ERROR_UNKNOWN_PORT ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * does_not_existW ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/ * localportW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ pAddPortUI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_AddPortUI(void)
{
    DWORD   res;
    LPWSTR  new_portname;

    /* not present before w2k */
    if (!pAddPortUI) {
        skip("AddPortUI not found\n");
        return;
    }

    SetLastError(0xdeadbeef);
    res = pAddPortUI(NULL, NULL, NULL, NULL);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pAddPortUI(NULL, NULL, emptyW, NULL);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pAddPortUI(NULL, NULL, does_not_existW, NULL);
    ok( !res &&
        ((GetLastError() == ERROR_UNKNOWN_PORT) || (GetLastError() == ERROR_INVALID_PRINTER_NAME)),
        "got %d with %u (expected '0' with: ERROR_UNKNOWN_PORT or "
        "ERROR_INVALID_PRINTER_NAME)\n", res, GetLastError());

    if (winetest_interactive) {
        SetLastError(0xdeadbeef);
        new_portname = NULL;
        /*
         * - On MSDN, you can read that no dialog should be displayed when hWnd
         *   is NULL, but native localui does not care
         * - When the new port already exists,
         *   TRUE is returned, but new_portname is NULL
         * - When the new port starts with "COM" or "LPT",
         *   FALSE is returned with ERROR_NOT_SUPPORTED on windows
         */
        res = pAddPortUI(NULL, NULL, localportW, &new_portname);
        ok( res ||
            (GetLastError() == ERROR_CANCELLED) ||
            (GetLastError() == ERROR_ACCESS_DENIED) ||
            (GetLastError() == ERROR_NOT_SUPPORTED),
            "got %d with %u and %p (expected '!= 0' or '0' with: "
            "ERROR_CANCELLED, ERROR_ACCESS_DENIED or ERROR_NOT_SUPPORTED)\n",
            res, GetLastError(), new_portname);

        GlobalFree(new_portname);
    }
}