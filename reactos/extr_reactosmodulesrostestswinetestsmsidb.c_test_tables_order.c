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

__attribute__((used)) static void test_tables_order(void)
{
    const char *query;
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT r;
    char buffer[100];
    DWORD sz;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `foo` ( "
        "`baz` INT NOT NULL PRIMARY KEY `baz`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    query = "CREATE TABLE `bar` ( "
        "`foo` INT NOT NULL PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    query = "CREATE TABLE `baz` ( "
        "`bar` INT NOT NULL, "
        "`baz` INT NOT NULL, "
        "`foo` INT NOT NULL PRIMARY KEY `bar`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    /* The names of the tables in the _Tables table must
       be in the same order as these names are created in
       the strings table. */
    query = "SELECT * FROM `_Tables`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "foo"), "Expected foo, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "bar"), "Expected bar, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* The names of the tables in the _Columns table must
       be in the same order as these names are created in
       the strings table. */
    query = "SELECT * FROM `_Columns`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "foo"), "Expected foo, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "bar"), "Expected bar, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "baz"), "Expected baz, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "foo"), "Expected foo, got %s\n", buffer);
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "bar"), "Expected bar, got %s\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "foo"), "Expected foo, got %s\n", buffer);
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