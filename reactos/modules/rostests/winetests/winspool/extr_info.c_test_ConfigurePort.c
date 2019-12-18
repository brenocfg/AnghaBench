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
 scalar_t__ ConfigurePortA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ RPC_X_NULL_REF_POINTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * does_not_exist ; 
 int /*<<< orphan*/ * empty ; 
 scalar_t__ is_access_denied (scalar_t__,scalar_t__) ; 
 scalar_t__ is_spooler_deactivated (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * portname_com1 ; 
 int /*<<< orphan*/ * portname_file ; 
 int /*<<< orphan*/ * portname_lpt1 ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_ConfigurePort(void)
{
    DWORD   res;


    SetLastError(0xdeadbeef);
    res = ConfigurePortA(NULL, 0, NULL);
    if (is_spooler_deactivated(res, GetLastError())) return;
    /* NT: RPC_X_NULL_REF_POINTER, 9x: ERROR_INVALID_PARAMETER */
    ok( !res && ((GetLastError() == RPC_X_NULL_REF_POINTER) || 
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with ERROR_NOT_SUPPORTED or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = ConfigurePortA(NULL, 0, empty);
    /* Allowed only for (Printer-)Administrators */
    if (is_access_denied(res, GetLastError())) return;

    /* XP: ERROR_NOT_SUPPORTED, NT351 and 9x: ERROR_INVALID_PARAMETER */
    ok( !res && ((GetLastError() == ERROR_NOT_SUPPORTED) || 
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with ERROR_NOT_SUPPORTED or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());


    SetLastError(0xdeadbeef);
    res = ConfigurePortA(NULL, 0, does_not_exist);
    /* XP: ERROR_NOT_SUPPORTED, NT351 and 9x: ERROR_INVALID_PARAMETER */
    ok( !res && ((GetLastError() == ERROR_NOT_SUPPORTED) || 
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with ERROR_NOT_SUPPORTED or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());


    /*  Testing-Results:
        - Case of Portnames is ignored 
        - Portname without ":" => NT: ERROR_NOT_SUPPORTED, 9x: Dialog comes up
        - Empty Servername (LPT1:) => NT: ERROR_NOT_SUPPORTED, 9x: Dialog comes up

        - Port not present =>  9x: ERROR_INVALID_PARAMETER, NT:ERROR_NOT_SUPPORTED
        - "FILE:" => 9x:Success, NT:ERROR_CANCELED
        - Cancel ("Local Port") => ERROR_CANCELED
        - Cancel ("Redirected Port") => Success
    */
    if (winetest_interactive > 0) {
        SetLastError(0xdeadbeef);
        res = ConfigurePortA(NULL, 0, portname_com1);
        trace("'%s' returned %d with %d\n", portname_com1, res, GetLastError());

        SetLastError(0xdeadbeef);
        res = ConfigurePortA(NULL, 0, portname_lpt1);
        trace("'%s' returned %d with %d\n", portname_lpt1, res, GetLastError());

        SetLastError(0xdeadbeef);
        res = ConfigurePortA(NULL, 0, portname_file);
        trace("'%s' returned %d with %d\n", portname_file, res, GetLastError());
    }
}