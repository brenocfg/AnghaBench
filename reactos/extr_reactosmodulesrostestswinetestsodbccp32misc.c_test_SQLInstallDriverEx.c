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
typedef  int /*<<< orphan*/  error ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ODBC_CONFIG_DRIVER ; 
 scalar_t__ ODBC_ERROR_COMPONENT_NOT_FOUND ; 
 scalar_t__ ODBC_ERROR_INVALID_KEYWORD_VALUE ; 
 scalar_t__ ODBC_ERROR_WRITING_SYSINFO_FAILED ; 
 int /*<<< orphan*/  ODBC_INSTALL_COMPLETE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int SQLConfigDriver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 int SQLInstallDriverEx (char*,char*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SQLInstallerErrorW (int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SQLRemoveDriver (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SQLInstallDriverEx(void)
{
    char path[MAX_PATH];
    char syspath[MAX_PATH];
    WORD size = 0;
    BOOL ret, sql_ret;
    DWORD cnt, error_code = 0;
    HKEY hkey;
    LONG res;
    char error[1000];

    GetSystemDirectoryA(syspath, MAX_PATH);

    ret = SQLConfigDriver(NULL, ODBC_CONFIG_DRIVER, "WINE ODBC Driver", "CPTimeout=59", error, sizeof(error), NULL);
    ok(!ret, "SQLConfigDriver returned %d\n", ret);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret && error_code == ODBC_ERROR_COMPONENT_NOT_FOUND, "SQLConfigDriver returned %d, %u\n", sql_ret, error_code);

    ret = SQLInstallDriverEx("WINE ODBC Driver\0Driver=sample.dll\0Setup=sample.dll\0\0", NULL,
                             path, MAX_PATH, &size, ODBC_INSTALL_COMPLETE, NULL);
    ok(ret, "SQLInstallDriverEx failed\n");
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    if (sql_ret && error_code == ODBC_ERROR_WRITING_SYSINFO_FAILED)
    {
         win_skip("not enough privileges\n");
         return;
    }
    ok(sql_ret == SQL_NO_DATA || (sql_ret && error_code == SQL_SUCCESS), "SQLInstallDriverEx failed %d, %u\n", sql_ret, error_code);
    ok(!strcmp(path, syspath), "invalid path %s\n", path);

if (0)  /* Crashes on XP. */
{
    sql_ret = 0;
    ret = SQLConfigDriver(NULL, ODBC_CONFIG_DRIVER, "WINE ODBC Driver", NULL, error, sizeof(error), NULL);
    ok(!ret, "SQLConfigDriver failed '%s'\n",error);
}

    ret = SQLConfigDriver(NULL, ODBC_CONFIG_DRIVER, "WINE ODBC Driver", "CPTimeout=59\0NoWrite=60\0", error, sizeof(error), NULL);
    ok(ret, "SQLConfigDriver failed\n");
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret == SQL_NO_DATA || (sql_ret && error_code == SQL_SUCCESS), "SQLConfigDriver failed %d, %u\n", sql_ret, error_code);

    ret = SQLInstallDriverEx("WINE ODBC Driver Path\0Driver=sample.dll\0Setup=sample.dll\0\0", "c:\\temp", path, MAX_PATH, &size, ODBC_INSTALL_COMPLETE, NULL);
    ok(ret, "SQLInstallDriverEx failed\n");
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret == SQL_NO_DATA || (sql_ret && error_code == SQL_SUCCESS), "SQLInstallDriverEx failed %d, %u\n", sql_ret, error_code);
    ok(!strcmp(path, "c:\\temp"), "invalid path %s\n", path);

    ret = SQLConfigDriver(NULL, ODBC_CONFIG_DRIVER, "WINE ODBC Driver Path", "empty", error, sizeof(error), NULL);
    ok(!ret, "SQLConfigDriver successful\n");
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret && error_code == ODBC_ERROR_INVALID_KEYWORD_VALUE, "SQLConfigDriver failed %d, %u\n", sql_ret, error_code);

    ret = SQLConfigDriver(NULL, ODBC_CONFIG_DRIVER, "WINE ODBC Driver Path", "NoWrite=60;xxxx=555", error, sizeof(error), NULL);
    ok(ret, "SQLConfigDriver failed\n");
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(sql_ret == SQL_NO_DATA || (sql_ret && error_code == SQL_SUCCESS), "SQLConfigDriver failed %d, %u\n", sql_ret, error_code);

    if (ret)
    {
        DWORD type = 0xdeadbeef, size = MAX_PATH;

        res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\ODBC\\ODBCINST.INI\\WINE ODBC Driver", 0, KEY_READ, &hkey);
        ok(res == ERROR_SUCCESS, "RegOpenKeyExW failed\n");
        if (res == ERROR_SUCCESS)
        {
            char driverpath[MAX_PATH];

            strcpy(driverpath, syspath);
            strcat(driverpath, "\\sample.dll");

            memset(path, 0, sizeof(path));
            res = RegQueryValueExA(hkey, "Driver", NULL, &type, (BYTE *)path, &size);
            ok(res == ERROR_SUCCESS, "got %d\n", res);
            ok(type == REG_SZ, "got %u\n", type);
            ok(size == strlen(driverpath) + 1, "got %u\n", size);
            ok(!strcmp(path, driverpath), "invalid path %s\n", path);

            res = RegQueryValueExA(hkey, "CPTimeout", NULL, &type, (BYTE *)&path, &size);
            ok(res == ERROR_SUCCESS, "got %d\n", res);
            ok(type == REG_SZ, "got %u\n", type);
            ok(size == strlen("59") + 1, "got %u\n", size);
            ok(!strcmp(path, "59"), "invalid value %s\n", path);

            res = RegQueryValueExA(hkey, "NoWrite", NULL, &type, (BYTE *)&path, &size);
            ok(res == ERROR_FILE_NOT_FOUND, "got %d\n", res);

            RegCloseKey(hkey);
        }

        res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\ODBC\\ODBCINST.INI\\WINE ODBC Driver Path", 0, KEY_READ, &hkey);
        ok(res == ERROR_SUCCESS, "RegOpenKeyExW failed\n");
        if (res == ERROR_SUCCESS)
        {
            size = sizeof(path);
            res = RegQueryValueExA(hkey, "NoWrite", NULL, &type, (BYTE *)&path, &size);
            ok(res == ERROR_SUCCESS, "got %d\n", res);
            ok(type == REG_SZ, "got %u\n", type);
            ok(size == strlen("60;xxxx=555") + 1, "got %u\n", size);
            ok(!strcmp(path, "60;xxxx=555"), "invalid value %s\n", path);

            res = RegQueryValueExA(hkey, "CPTimeout", NULL, &type, (BYTE *)&path, &size);
            ok(res == ERROR_FILE_NOT_FOUND, "got %d\n", res);
            RegCloseKey(hkey);
        }
    }

    cnt = 100;
    ret = SQLRemoveDriver("WINE ODBC Driver", FALSE, &cnt);
    ok(ret, "SQLRemoveDriver failed\n");
    ok(cnt == 0, "SQLRemoveDriver failed %d\n", cnt);

    cnt = 100;
    ret = SQLRemoveDriver("WINE ODBC Driver Path", FALSE, &cnt);
    ok(ret, "SQLRemoveDriver failed\n");
    ok(cnt == 0, "SQLRemoveDriver failed %d\n", cnt);
}