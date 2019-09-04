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
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char*,scalar_t__*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordGetStringA (scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 int do_query (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int run_query (scalar_t__,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_droptable(void)
{
    MSIHANDLE hdb, hview, hrec;
    CHAR buf[MAX_PATH];
    LPCSTR query;
    DWORD size;
    UINT r;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    query = "SELECT * FROM `_Tables` WHERE `Name` = 'One'";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'One'";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 3, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "A"), "Expected \"A\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "DROP `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    hview = 0;
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_FUNCTION_FAILED,
       "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `IDontExist`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE One";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "SELECT * FROM `_Tables` WHERE `Name` = 'One'";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'One'";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    query = "CREATE TABLE `One` ( `B` INT, `C` INT PRIMARY KEY `B` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    query = "SELECT * FROM `_Tables` WHERE `Name` = 'One'";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'One'";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 3, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "B"), "Expected \"B\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 3, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "C"), "Expected \"C\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "DROP TABLE One";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "SELECT * FROM `_Tables` WHERE `Name` = 'One'";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'One'";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}