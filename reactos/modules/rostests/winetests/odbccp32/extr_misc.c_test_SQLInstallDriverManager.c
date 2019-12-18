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
typedef  int WORD ;
typedef  scalar_t__ RETCODE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int MAX_PATH ; 
 scalar_t__ ODBC_ERROR_INVALID_BUFF_LEN ; 
 scalar_t__ ODBC_ERROR_WRITING_SYSINFO_FAILED ; 
 int SQLInstallDriverManager (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ SQLInstallerErrorW (int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SQLInstallDriverManager(void)
{
    BOOL bool_ret;
    RETCODE sql_ret;
    DWORD error_code;
    CHAR target_path[MAX_PATH];
    WORD path_out;

    /* NULL check */
    bool_ret = SQLInstallDriverManager(NULL, 0, NULL);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(!bool_ret, "SQLInstallDriverManager unexpectedly succeeded\n");
    ok(sql_ret == SQL_SUCCESS_WITH_INFO && error_code == ODBC_ERROR_INVALID_BUFF_LEN,
        "Expected SQLInstallDriverManager to fail with ODBC_ERROR_INVALID_BUFF_LEN\n");

    /* Length smaller than MAX_PATH */
    bool_ret = SQLInstallDriverManager(target_path, MAX_PATH / 2, NULL);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(!bool_ret, "SQLInstallDriverManager unexpectedly succeeded\n");
    ok(sql_ret == SQL_SUCCESS_WITH_INFO && error_code == ODBC_ERROR_INVALID_BUFF_LEN,
        "Expected SQLInstallDriverManager to fail with ODBC_ERROR_INVALID_BUFF_LEN\n");

    path_out = 0xcafe;
    bool_ret = SQLInstallDriverManager(target_path, MAX_PATH / 2, &path_out);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(!bool_ret, "SQLInstallDriverManager unexpectedly succeeded\n");
    ok(sql_ret == SQL_SUCCESS_WITH_INFO && error_code == ODBC_ERROR_INVALID_BUFF_LEN,
        "Expected SQLInstallDriverManager to fail with ODBC_ERROR_INVALID_BUFF_LEN\n");
    ok(path_out == 0xcafe, "Expected path_out to not have changed\n");

    /* Length OK */
    bool_ret = SQLInstallDriverManager(target_path, MAX_PATH, NULL);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    if(!bool_ret && error_code == ODBC_ERROR_WRITING_SYSINFO_FAILED)
    {
         win_skip("not enough privileges\n");
         return;
    }
    ok(bool_ret, "SQLInstallDriverManager unexpectedly failed: %d\n",
        error_code);
    if (bool_ret)
        ok(sql_ret == SQL_NO_DATA, "Expected SQL_NO_DATA, got %d\n", sql_ret);
    else
        ok(sql_ret == SQL_SUCCESS_WITH_INFO,
            "Expected SQL_SUCCESS_WITH_INFO, got %d\n", sql_ret);

    path_out = 0xcafe;
    bool_ret = SQLInstallDriverManager(target_path, MAX_PATH, &path_out);
    sql_ret = SQLInstallerErrorW(1, &error_code, NULL, 0, NULL);
    ok(bool_ret, "SQLInstallDriverManager unexpectedly failed: %d\n",
        error_code);
    if (bool_ret)
        ok(sql_ret == SQL_NO_DATA, "Expected SQL_NO_DATA, got %d\n", sql_ret);
    else
        ok(sql_ret == SQL_SUCCESS_WITH_INFO,
            "Expected SQL_SUCCESS_WITH_INFO, got %d\n", sql_ret);
    /* path_out should in practice be less than 0xcafe */
    ok(path_out != 0xcafe, "Expected path_out to show the correct amount of bytes\n");
}