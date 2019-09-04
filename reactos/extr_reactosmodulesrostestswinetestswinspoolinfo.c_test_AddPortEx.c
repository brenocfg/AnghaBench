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
struct TYPE_2__ {int /*<<< orphan*/  fPortType; int /*<<< orphan*/  pDescription; int /*<<< orphan*/ * pMonitorName; int /*<<< orphan*/ * pPortName; } ;
typedef  TYPE_1__ PORT_INFO_2A ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeletePortA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ ERROR_INVALID_LEVEL ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * LocalPortA ; 
 int /*<<< orphan*/  PORT_TYPE_WRITE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * does_not_exist ; 
 int /*<<< orphan*/ * empty ; 
 scalar_t__ is_spooler_deactivated (int,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 
 int pAddPortExA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 void* tempfileA ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetest ; 

__attribute__((used)) static void test_AddPortEx(void)
{
    PORT_INFO_2A pi;
    DWORD   res;


    if (!pAddPortExA) {
        win_skip("AddPortEx not supported\n");
        return;
    }

    /* start test with a clean system */
    DeletePortA(NULL, 0, tempfileA);

    pi.pPortName = tempfileA;
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, LocalPortA);
    if (is_spooler_deactivated(res, GetLastError())) return;

    /* Allowed only for (Printer-)Administrators.
       W2K+XP: ERROR_INVALID_PARAMETER  */
    if (!res && (GetLastError() == ERROR_INVALID_PARAMETER)) {
        skip("ACCESS_DENIED (ERROR_INVALID_PARAMETER)\n");
        return;
    }
    ok( res, "got %u with %u (expected '!= 0')\n", res, GetLastError());

    /* add a port that already exists */
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
    DeletePortA(NULL, 0, tempfileA);


    /* the Monitorname must match */
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, NULL);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
    if (res) DeletePortA(NULL, 0, tempfileA);

    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, empty);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
    if (res) DeletePortA(NULL, 0, tempfileA);

    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, does_not_exist);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
    if (res) DeletePortA(NULL, 0, tempfileA);


    /* We need a Portname */
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, NULL, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());

    pi.pPortName = NULL;
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 1, (LPBYTE) &pi, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u with %u (expected '0' with ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
    if (res) DeletePortA(NULL, 0, tempfileA);


    /*  level 2 is documented as supported for Printmonitors,
        but that is not supported for "Local Port" (localspl.dll) and
        AddPortEx fails with ERROR_INVALID_LEVEL */

    pi.pPortName = tempfileA;
    pi.pMonitorName = LocalPortA;
    pi.pDescription = winetest;
    pi.fPortType = PORT_TYPE_WRITE;

    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 2, (LPBYTE) &pi, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_LEVEL),
        "got %u with %u (expected '0' with ERROR_INVALID_LEVEL)\n",
        res, GetLastError());
    if (res) DeletePortA(NULL, 0, tempfileA);


    /* invalid levels */
    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 0, (LPBYTE) &pi, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_LEVEL),
        "got %u with %u (expected '0' with ERROR_INVALID_LEVEL)\n",
        res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pAddPortExA(NULL, 3, (LPBYTE) &pi, LocalPortA);
    ok( !res && (GetLastError() == ERROR_INVALID_LEVEL),
        "got %u with %u (expected '0' with ERROR_INVALID_LEVEL)\n",
        res, GetLastError());


    /* cleanup */
    DeletePortA(NULL, 0, tempfileA);

}