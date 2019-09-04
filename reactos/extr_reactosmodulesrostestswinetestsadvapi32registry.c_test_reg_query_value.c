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
typedef  int /*<<< orphan*/  valW ;
typedef  int /*<<< orphan*/  expected ;
typedef  char WCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_BADKEY ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int RegCreateKeyA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ *,char*) ; 
 int RegQueryValueA (int /*<<< orphan*/ *,char*,char*,int*) ; 
 int RegQueryValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*) ; 
 int RegSetValueA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int RegSetValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * hkey_main ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_reg_query_value(void)
{
    HKEY subkey;
    CHAR val[MAX_PATH];
    WCHAR valW[5];
    LONG size, ret;

    static const WCHAR expected[] = {'d','a','t','a',0};

    ret = RegCreateKeyA(hkey_main, "subkey", &subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegSetValueA(subkey, NULL, REG_SZ, "data", 4);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    /* try an invalid hkey */
    SetLastError(0xdeadbeef);
    size = MAX_PATH;
    ret = RegQueryValueA((HKEY)0xcafebabe, "subkey", val, &size);
    ok(ret == ERROR_INVALID_HANDLE ||
       ret == ERROR_BADKEY || /* Windows 98 returns BADKEY */
       ret == ERROR_ACCESS_DENIED, /* non-admin winxp */
       "Expected ERROR_INVALID_HANDLE or ERROR_BADKEY, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a NULL hkey */
    SetLastError(0xdeadbeef);
    size = MAX_PATH;
    ret = RegQueryValueA(NULL, "subkey", val, &size);
    ok(ret == ERROR_INVALID_HANDLE || ret == ERROR_BADKEY, /* Windows 98 returns BADKEY */
       "Expected ERROR_INVALID_HANDLE or ERROR_BADKEY, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a NULL value */
    size = MAX_PATH;
    ret = RegQueryValueA(hkey_main, "subkey", NULL, &size);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* try a NULL size */
    SetLastError(0xdeadbeef);
    val[0] = '\0';
    ret = RegQueryValueA(hkey_main, "subkey", val, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(!val[0], "Expected val to be untouched, got %s\n", val);

    /* try a NULL value and size */
    ret = RegQueryValueA(hkey_main, "subkey", NULL, NULL);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    /* try a size too small */
    SetLastError(0xdeadbeef);
    val[0] = '\0';
    size = 1;
    ret = RegQueryValueA(hkey_main, "subkey", val, &size);
    ok(ret == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(!val[0], "Expected val to be untouched, got %s\n", val);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* successfully read the value using 'subkey' */
    size = MAX_PATH;
    ret = RegQueryValueA(hkey_main, "subkey", val, &size);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(!lstrcmpA(val, "data"), "Expected 'data', got '%s'\n", val);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* successfully read the value using the subkey key */
    size = MAX_PATH;
    ret = RegQueryValueA(subkey, NULL, val, &size);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(!lstrcmpA(val, "data"), "Expected 'data', got '%s'\n", val);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* unicode - try size too small */
    SetLastError(0xdeadbeef);
    valW[0] = '\0';
    size = 0;
    ret = RegQueryValueW(subkey, NULL, valW, &size);
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("RegQueryValueW is not implemented\n");
        goto cleanup;
    }
    ok(ret == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(!valW[0], "Expected valW to be untouched\n");
    ok(size == sizeof(expected), "Got wrong size: %d\n", size);

    /* unicode - try size in WCHARS */
    SetLastError(0xdeadbeef);
    size = sizeof(valW) / sizeof(WCHAR);
    ret = RegQueryValueW(subkey, NULL, valW, &size);
    ok(ret == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(!valW[0], "Expected valW to be untouched\n");
    ok(size == sizeof(expected), "Got wrong size: %d\n", size);

    /* unicode - successfully read the value */
    size = sizeof(valW);
    ret = RegQueryValueW(subkey, NULL, valW, &size);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(!lstrcmpW(valW, expected), "Got wrong value\n");
    ok(size == sizeof(expected), "Got wrong size: %d\n", size);

    /* unicode - set the value without a NULL terminator */
    ret = RegSetValueW(subkey, NULL, REG_SZ, expected, sizeof(expected)-sizeof(WCHAR));
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    /* unicode - read the unterminated value, value is terminated for us */
    memset(valW, 'a', sizeof(valW));
    size = sizeof(valW);
    ret = RegQueryValueW(subkey, NULL, valW, &size);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(!lstrcmpW(valW, expected), "Got wrong value\n");
    ok(size == sizeof(expected), "Got wrong size: %d\n", size);

cleanup:
    RegDeleteKeyA(subkey, "");
    RegCloseKey(subkey);
}