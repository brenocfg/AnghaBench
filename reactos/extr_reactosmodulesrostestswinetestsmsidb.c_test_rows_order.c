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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiRecordGetStringA (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_rows_order(void)
{
    const char *query;
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT r;
    char buffer[100];
    DWORD sz;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `foo` ( "
        "`bar` LONGCHAR NOT NULL PRIMARY KEY `bar`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'A' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'B' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'C' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'D' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'E' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `foo` "
            "( `bar` ) VALUES ( 'F' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    query = "CREATE TABLE `bar` ( "
        "`foo` LONGCHAR NOT NULL, "
        "`baz` LONGCHAR NOT NULL "
        "PRIMARY KEY `foo` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( 'C', 'E' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( 'F', 'A' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( 'A', 'B' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( 'D', 'E' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table\n");

    /* The rows of the table must be ordered by the column values of
       each row. For strings, the column value is the string id
       in the string table.  */

    query = "SELECT * FROM `bar`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "A"), "Expected A, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "B"), "Expected B, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "C"), "Expected E, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "E"), "Expected E, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "D"), "Expected D, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "E"), "Expected E, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "F"), "Expected F, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "A"), "Expected A, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    DeleteFileA(msifile);
}