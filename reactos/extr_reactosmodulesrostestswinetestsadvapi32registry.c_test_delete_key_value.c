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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * hkey_main ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pRegDeleteKeyValueA (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_delete_key_value(void)
{
    HKEY subkey;
    LONG ret;

    if (!pRegDeleteKeyValueA)
    {
        win_skip("RegDeleteKeyValue is not available.\n");
        return;
    }

    ret = pRegDeleteKeyValueA(NULL, NULL, NULL);
    ok(ret == ERROR_INVALID_HANDLE, "got %d\n", ret);

    ret = pRegDeleteKeyValueA(hkey_main, NULL, NULL);
    ok(ret == ERROR_FILE_NOT_FOUND, "got %d\n", ret);

    ret = RegSetValueExA(hkey_main, "test", 0, REG_SZ, (const BYTE*)"value", 6);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = RegQueryValueExA(hkey_main, "test", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    /* NULL subkey name means delete from open key */
    ret = pRegDeleteKeyValueA(hkey_main, NULL, "test");
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = RegQueryValueExA(hkey_main, "test", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_FILE_NOT_FOUND, "got %d\n", ret);

    /* now with real subkey */
    ret = RegCreateKeyExA(hkey_main, "Subkey1", 0, NULL, 0, KEY_WRITE|KEY_READ, NULL, &subkey, NULL);
    ok(!ret, "failed with error %d\n", ret);

    ret = RegSetValueExA(subkey, "test", 0, REG_SZ, (const BYTE*)"value", 6);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = RegQueryValueExA(subkey, "test", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = pRegDeleteKeyValueA(hkey_main, "Subkey1", "test");
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = RegQueryValueExA(subkey, "test", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_FILE_NOT_FOUND, "got %d\n", ret);

    /* Default registry value */
    ret = RegSetValueExA(subkey, "", 0, REG_SZ, (const BYTE *)"value", 6);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegQueryValueExA(subkey, "", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    ret = pRegDeleteKeyValueA(hkey_main, "Subkey1", "" );
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegQueryValueExA(subkey, "", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n", ret);

    RegDeleteKeyA(subkey, "");
    RegCloseKey(subkey);
}