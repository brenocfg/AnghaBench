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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int BOOL ;

/* Variables and functions */
 int AddERExcludedApplicationA (char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ is_process_limited () ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  regpath_exclude ; 
 int /*<<< orphan*/  regpath_root ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_AddERExcludedApplicationA(void)
{
    BOOL res;
    LONG lres;
    HKEY hroot;
    HKEY hexclude = 0;

    /* clean state */
    lres = RegCreateKeyA(HKEY_LOCAL_MACHINE, regpath_root, &hroot);
    if (lres == ERROR_ACCESS_DENIED)
    {
        skip("Not enough access rights\n");
        return;
    }

    if (!lres)
        lres = RegOpenKeyA(hroot, regpath_exclude, &hexclude);

    if (!lres)
        RegDeleteValueA(hexclude, "winetest_faultrep.exe");


    SetLastError(0xdeadbeef);
    res = AddERExcludedApplicationA(NULL);
    ok(!res, "got %d and 0x%x (expected FALSE)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = AddERExcludedApplicationA("");
    ok(!res, "got %d and 0x%x (expected FALSE)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    /* existence of the path doesn't matter this function succeeded */
    res = AddERExcludedApplicationA("winetest_faultrep.exe");
    if (is_process_limited())
    {
        /* LastError is not set! */
        ok(!res, "AddERExcludedApplicationA should have failed got %d\n", res);
    }
    else
    {
        ok(res, "AddERExcludedApplicationA failed (le=0x%x)\n", GetLastError());

        /* add, when already present */
        SetLastError(0xdeadbeef);
        res = AddERExcludedApplicationA("winetest_faultrep.exe");
        ok(res, "AddERExcludedApplicationA failed (le=0x%x)\n", GetLastError());
    }

    /* cleanup */
    RegDeleteValueA(hexclude, "winetest_faultrep.exe");

    RegCloseKey(hexclude);
    RegCloseKey(hroot);
}