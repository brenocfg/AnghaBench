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
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 int RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegQueryValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int RegSetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  lstrlenA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pRegDeleteTreeA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_reg_delete_tree(void)
{
    CHAR buffer[MAX_PATH];
    HKEY subkey, subkey2;
    DWORD dwsize, type;
    LONG size, ret;

    if(!pRegDeleteTreeA) {
        win_skip("Skipping RegDeleteTreeA tests, function not present\n");
        return;
    }

    ret = RegCreateKeyA(hkey_main, "subkey", &subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCreateKeyA(subkey, "subkey2", &subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegSetValueA(subkey, NULL, REG_SZ, "data", 4);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegSetValueA(subkey2, NULL, REG_SZ, "data2", 5);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCloseKey(subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    ret = pRegDeleteTreeA(subkey, "subkey2");
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(RegOpenKeyA(subkey, "subkey2", &subkey2),
        "subkey2 was not deleted\n");
    size = MAX_PATH;
    ok(!RegQueryValueA(subkey, NULL, buffer, &size),
        "Default value of subkey no longer present\n");

    ret = RegCreateKeyA(subkey, "subkey2", &subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCloseKey(subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = pRegDeleteTreeA(hkey_main, "subkey\\subkey2");
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(RegOpenKeyA(subkey, "subkey2", &subkey2),
        "subkey2 was not deleted\n");
    ok(!RegQueryValueA(subkey, NULL, buffer, &size),
        "Default value of subkey no longer present\n");

    ret = RegCreateKeyA(subkey, "subkey2", &subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCloseKey(subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCreateKeyA(subkey, "subkey3", &subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCloseKey(subkey2);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegSetValueA(subkey, NULL, REG_SZ, "data", 4);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegSetValueExA(subkey, "value", 0, REG_SZ, (const BYTE *)"data2", 5);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = pRegDeleteTreeA(subkey, NULL);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ok(!RegOpenKeyA(hkey_main, "subkey", &subkey),
        "subkey was deleted\n");
    ok(RegOpenKeyA(subkey, "subkey2", &subkey2),
        "subkey2 was not deleted\n");
    ok(RegOpenKeyA(subkey, "subkey3", &subkey2),
        "subkey3 was not deleted\n");
    size = MAX_PATH;
    ret = RegQueryValueA(subkey, NULL, buffer, &size);
    ok(ret == ERROR_SUCCESS,
        "Default value of subkey is not present\n");
    ok(!buffer[0], "Expected length 0 got length %u(%s)\n", lstrlenA(buffer), buffer);
    dwsize = MAX_PATH;
    ok(RegQueryValueExA(subkey, "value", NULL, &type, (BYTE *)buffer, &dwsize),
        "Value is still present\n");
    ret = RegCloseKey(subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegOpenKeyA(hkey_main, "subkey", &subkey);
    ok(ret == ERROR_SUCCESS, "subkey was deleted\n");
    ret = pRegDeleteTreeA(subkey, "");
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);
    ret = RegCloseKey(subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegOpenKeyA(hkey_main, "subkey", &subkey);
    ok(ret == ERROR_SUCCESS, "subkey was deleted\n");
    ret = RegCloseKey(subkey);
    ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", ret);

    ret = pRegDeleteTreeA(hkey_main, "not-here");
    ok(ret == ERROR_FILE_NOT_FOUND,
        "Expected ERROR_FILE_NOT_FOUND, got %d\n", ret);
}