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
typedef  int UINT ;
typedef  scalar_t__ MSIHANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiDatabaseCommit (scalar_t__) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char const*,scalar_t__*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordGetStringA (scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiRecordSetInteger (scalar_t__,int,int) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (scalar_t__,int,char*) ; 
 int MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (scalar_t__,scalar_t__,char const*) ; 

__attribute__((used)) static void test_update(void)
{
    MSIHANDLE hdb = 0, view = 0, rec = 0;
    CHAR result[MAX_PATH];
    const char *query;
    DWORD size;
    UINT r;

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    /* create the Control table */
    query = "CREATE TABLE `Control` ( "
        "`Dialog_` CHAR(72) NOT NULL, `Control` CHAR(50) NOT NULL, `Type` SHORT NOT NULL, "
        "`X` SHORT NOT NULL, `Y` SHORT NOT NULL, `Width` SHORT NOT NULL, `Height` SHORT NOT NULL,"
        "`Attributes` LONG, `Property` CHAR(50), `Text` CHAR(0) LOCALIZABLE, "
        "`Control_Next` CHAR(50), `Help` CHAR(50) LOCALIZABLE PRIMARY KEY `Dialog_`, `Control`)";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* add a control */
    query = "INSERT INTO `Control` ( "
        "`Dialog_`, `Control`, `Type`, `X`, `Y`, `Width`, `Height`, "
        "`Property`, `Text`, `Control_Next`, `Help` )"
        "VALUES('ErrorDialog', 'ErrorText', '1', '5', '5', '5', '5', '', '', '', '')";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* add a second control */
    query = "INSERT INTO `Control` ( "
        "`Dialog_`, `Control`, `Type`, `X`, `Y`, `Width`, `Height`, "
        "`Property`, `Text`, `Control_Next`, `Help` )"
        "VALUES('ErrorDialog', 'Button', '1', '5', '5', '5', '5', '', '', '', '')";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* add a third control */
    query = "INSERT INTO `Control` ( "
        "`Dialog_`, `Control`, `Type`, `X`, `Y`, `Width`, `Height`, "
        "`Property`, `Text`, `Control_Next`, `Help` )"
        "VALUES('AnotherDialog', 'ErrorText', '1', '5', '5', '5', '5', '', '', '', '')";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* bad table */
    query = "UPDATE `NotATable` SET `Text` = 'this is text' WHERE `Dialog_` = 'ErrorDialog'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* bad set column */
    query = "UPDATE `Control` SET `NotAColumn` = 'this is text' WHERE `Dialog_` = 'ErrorDialog'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* bad where condition */
    query = "UPDATE `Control` SET `Text` = 'this is text' WHERE `NotAColumn` = 'ErrorDialog'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* just the dialog_ specified */
    query = "UPDATE `Control` SET `Text` = 'this is text' WHERE `Dialog_` = 'ErrorDialog'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* check the modified text */
    query = "SELECT `Text` FROM `Control` WHERE `Control` = 'ErrorText'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(result, "this is text"), "Expected `this is text`, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!result[0], "Expected an empty string, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* dialog_ and control specified */
    query = "UPDATE `Control` SET `Text` = 'this is text' WHERE `Dialog_` = 'ErrorDialog' AND `Control` = 'ErrorText'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* check the modified text */
    query = "SELECT `Text` FROM `Control` WHERE `Control` = 'ErrorText'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(result, "this is text"), "Expected `this is text`, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!result[0], "Expected an empty string, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* no where condition */
    query = "UPDATE `Control` SET `Text` = 'this is text'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* check the modified text */
    query = "SELECT `Text` FROM `Control`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(result, "this is text"), "Expected `this is text`, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(result, "this is text"), "Expected `this is text`, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, result, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(result, "this is text"), "Expected `this is text`, got %s\n", result);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "CREATE TABLE `Apple` ( `Banana` CHAR(72) NOT NULL, "
        "`Orange` CHAR(72),  `Pear` INT PRIMARY KEY `Banana`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Apple` ( `Banana`, `Orange`, `Pear` )"
        "VALUES('one', 'two', 3)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Apple` ( `Banana`, `Orange`, `Pear` )"
        "VALUES('three', 'four', 5)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Apple` ( `Banana`, `Orange`, `Pear` )"
        "VALUES('six', 'two', 7)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    rec = MsiCreateRecord(2);
    MsiRecordSetInteger(rec, 1, 8);
    MsiRecordSetStringA(rec, 2, "two");

    query = "UPDATE `Apple` SET `Pear` = ? WHERE `Orange` = ?";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(rec);

    query = "SELECT `Pear` FROM `Apple` ORDER BY `Orange`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == 8, "Expected 8, got %d\n", r);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == 8, "Expected 8, got %d\n", r);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == 5, "Expected 5, got %d\n", r);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);

    r = MsiDatabaseCommit(hdb);
    ok(r == ERROR_SUCCESS, "MsiDatabaseCommit failed\n");
    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    DeleteFileA(msifile);
}