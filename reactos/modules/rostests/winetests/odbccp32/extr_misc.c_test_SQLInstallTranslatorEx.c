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
typedef  int /*<<< orphan*/  path ;
typedef  scalar_t__ WORD ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 scalar_t__ ODBC_ERROR_COMPONENT_NOT_FOUND ; 
 scalar_t__ ODBC_ERROR_WRITING_SYSINFO_FAILED ; 
 int /*<<< orphan*/  ODBC_INSTALL_COMPLETE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int SQLInstallTranslatorEx (char*,char*,char*,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SQLInstallerErrorW (int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SQLRemoveTranslator (char*,scalar_t__*) ; 
 scalar_t__ SQL_SUCCESS ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SQLInstallTranslatorEx(void)
{
    char path[MAX_PATH];
    char syspath[MAX_PATH];
    WORD size = 0;
    BOOL ret, sql_ret;
    DWORD cnt, error_code = 0;
    HKEY hkey;
    LONG res;

    GetSystemDirectoryA(syspath, MAX_PATH);

    ret = SQLInstallTranslatorEx("WINE ODBC Translator\0Translator=sample.dll\0Setup=sample.dll\0",
                                 NULL, path, MAX_PATH, &size, ODBC_INSTALL_COMPLETE, NULL);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    if (sql_ret && error_code == ODBC_ERROR_WRITING_SYSINFO_FAILED)
    {
         win_skip("not enough privileges\n");
         return;
    }
    ok(sql_ret && error_code == SQL_SUCCESS, "SQLInstallDriverEx failed %d, %u\n", sql_ret, error_code);
    ok(!strcmp(path, syspath), "invalid path %s\n", path);
    ok(size == strlen(path), "invalid length %d\n", size);

    ret = SQLInstallTranslatorEx("WINE ODBC Translator Path\0Translator=sample.dll\0Setup=sample.dll\0",
                                 "c:\\temp", path, MAX_PATH, &size, ODBC_INSTALL_COMPLETE, NULL);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret && error_code == SQL_SUCCESS, "SQLInstallTranslatorEx failed %d, %u\n", sql_ret, error_code);
    ok(!strcmp(path, "c:\\temp"), "invalid path %s\n", path);
    ok(size == strlen(path), "invalid length %d\n", size);

    if(ret)
    {
        res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\ODBC\\ODBCINST.INI\\WINE ODBC Translator", 0,
                            KEY_READ, &hkey);
        ok(res == ERROR_SUCCESS, "RegOpenKeyExW failed\n");
        if (res == ERROR_SUCCESS)
        {
            DWORD type = 0xdeadbeef, size = MAX_PATH;
            char driverpath[MAX_PATH];

            strcpy(driverpath, syspath);
            strcat(driverpath, "\\sample.dll");

            memset(path, 0, sizeof(path));
            res = RegQueryValueExA(hkey, "Translator", NULL, &type, (BYTE *)path, &size);
            ok(res == ERROR_SUCCESS, "RegGetValueA failed\n");
            ok(type == REG_SZ, "got %u\n", type);
            ok(size == strlen(driverpath) + 1, "got %u\n", size);
            ok(!strcmp(path, driverpath), "invalid path %s\n", path);

            RegCloseKey(hkey);
        }
    }

    cnt = 100;
    ret = SQLRemoveTranslator("WINE ODBC Translator", &cnt);
    ok(ret, "SQLRemoveTranslator failed\n");
    ok(cnt == 0, "SQLRemoveTranslator failed %d\n", cnt);

    cnt = 100;
    ret = SQLRemoveTranslator("WINE ODBC Translator Path", &cnt);
    ok(ret, "SQLRemoveTranslator failed\n");
    ok(cnt == 0, "SQLRemoveTranslator failed %d\n", cnt);

    cnt = 100;
    ret = SQLRemoveTranslator("WINE ODBC Translator NonExist", &cnt);
    ok(!ret, "SQLRemoveTranslator succeeded\n");
    ok(cnt == 100, "SQLRemoveTranslator succeeded %d\n", cnt);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret && error_code == ODBC_ERROR_COMPONENT_NOT_FOUND,
        "SQLInstallTranslatorEx failed %d, %u\n", sql_ret, error_code);

}