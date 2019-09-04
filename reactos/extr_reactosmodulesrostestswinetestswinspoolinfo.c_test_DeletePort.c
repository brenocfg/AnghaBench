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
 scalar_t__ DeletePortA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * does_not_exist ; 
 int /*<<< orphan*/ * empty ; 
 scalar_t__ is_access_denied (scalar_t__,scalar_t__) ; 
 scalar_t__ is_spooler_deactivated (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_DeletePort(void)
{
    DWORD   res;

    SetLastError(0xdeadbeef);
    res = DeletePortA(NULL, 0, NULL);
    if (is_spooler_deactivated(res, GetLastError())) return;

    SetLastError(0xdeadbeef);
    res = DeletePortA(NULL, 0, empty);
    /* Allowed only for (Printer-)Administrators */
    if (is_access_denied(res, GetLastError())) return;

    /* XP: ERROR_NOT_SUPPORTED, NT351 and 9x: ERROR_INVALID_PARAMETER */
    ok( !res && ((GetLastError() == ERROR_NOT_SUPPORTED) || 
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with ERROR_NOT_SUPPORTED or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());


    SetLastError(0xdeadbeef);
    res = DeletePortA(NULL, 0, does_not_exist);
    /* XP: ERROR_NOT_SUPPORTED, NT351 and 9x: ERROR_INVALID_PARAMETER */
    ok( !res && ((GetLastError() == ERROR_NOT_SUPPORTED) || 
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with ERROR_NOT_SUPPORTED or "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError());

}