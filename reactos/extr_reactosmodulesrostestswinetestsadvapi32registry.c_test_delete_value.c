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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_delete_value(void)
{
    LONG res;
    char longname[401];

    res = RegSetValueExA( hkey_main, "test", 0, REG_SZ, (const BYTE*)"value", 6 );
    ok(res == ERROR_SUCCESS, "expect ERROR_SUCCESS, got %i\n", res);

    res = RegQueryValueExA( hkey_main, "test", NULL, NULL, NULL, NULL);
    ok(res == ERROR_SUCCESS, "expect ERROR_SUCCESS, got %i\n", res);

    res = RegDeleteValueA( hkey_main, "test" );
    ok(res == ERROR_SUCCESS, "expect ERROR_SUCCESS, got %i\n", res);

    res = RegQueryValueExA( hkey_main, "test", NULL, NULL, NULL, NULL);
    ok(res == ERROR_FILE_NOT_FOUND, "expect ERROR_FILE_NOT_FOUND, got %i\n", res);

    res = RegDeleteValueA( hkey_main, "test" );
    ok(res == ERROR_FILE_NOT_FOUND, "expect ERROR_FILE_NOT_FOUND, got %i\n", res);

    memset(longname, 'a', 400);
    longname[400] = 0;
    res = RegDeleteValueA( hkey_main, longname );
    ok(res == ERROR_FILE_NOT_FOUND || broken(res == ERROR_MORE_DATA), /* nt4, win2k */
       "expect ERROR_FILE_NOT_FOUND, got %i\n", res);

    /* Default registry value */
    res = RegSetValueExA(hkey_main, "", 0, REG_SZ, (const BYTE *)"value", 6);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res);

    res = RegQueryValueExA(hkey_main, "", NULL, NULL, NULL, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res);

    res = RegDeleteValueA(hkey_main, "" );
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res);

    res = RegQueryValueExA(hkey_main, "", NULL, NULL, NULL, NULL);
    ok(res == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n", res);
}