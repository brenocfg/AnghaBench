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
typedef  scalar_t__ RETCODE ;

/* Variables and functions */
 int /*<<< orphan*/  SQLGetInstalledDrivers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLInstallerError (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SQL_ERROR ; 
 scalar_t__ SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SQLInstallerError(void)
{
    RETCODE sql_ret;

    /* MSDN states that the error number should be between 1 and 8.  Passing 0 is an error */
    sql_ret = SQLInstallerError(0, NULL, NULL, 0, NULL);
    ok(sql_ret == SQL_ERROR, "SQLInstallerError(0...) failed with %d instead of SQL_ERROR\n", sql_ret);
    /* However numbers greater than 8 do not return SQL_ERROR.
     * I am currently unsure as to whether it should return SQL_NO_DATA or "the same as for error 8";
     * I have never been able to generate 8 errors to test it
     */
    sql_ret = SQLInstallerError(65535, NULL, NULL, 0, NULL);
    ok(sql_ret == SQL_NO_DATA, "SQLInstallerError(>8...) failed with %d instead of SQL_NO_DATA\n", sql_ret);

    /* Force an error to work with.  This should generate ODBC_ERROR_INVALID_BUFF_LEN */
    ok(!SQLGetInstalledDrivers(0, 0, 0), "Failed to force an error for testing\n");
    sql_ret = SQLInstallerError(2, NULL, NULL, 0, NULL);
    ok(sql_ret == SQL_NO_DATA, "Too many errors when forcing an error for testing\n");

    /* Null pointers are acceptable in all obvious places */
    sql_ret = SQLInstallerError(1, NULL, NULL, 0, NULL);
    ok(sql_ret == SQL_SUCCESS_WITH_INFO, "SQLInstallerError(null addresses) failed with %d instead of SQL_SUCCESS_WITH_INFO\n", sql_ret);
}