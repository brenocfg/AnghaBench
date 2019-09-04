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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ MSIHANDLE ;
typedef  char* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int /*<<< orphan*/  MsiRecordSetInteger (scalar_t__,int,int) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (scalar_t__,int,char*) ; 
 scalar_t__ create_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ run_query (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ try_query (scalar_t__,char*) ; 

__attribute__((used)) static void test_markers(void)
{
    MSIHANDLE hdb, rec;
    LPCSTR query;
    UINT r;

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    rec = MsiCreateRecord(3);
    MsiRecordSetStringA(rec, 1, "Table");
    MsiRecordSetStringA(rec, 2, "Apples");
    MsiRecordSetStringA(rec, 3, "Oranges");

    /* try a legit create */
    query = "CREATE TABLE `Table` ( `One` SHORT NOT NULL, `Two` CHAR(255) PRIMARY KEY `One`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    MsiCloseHandle(rec);

    /* try table name as marker */
    rec = MsiCreateRecord(1);
    MsiRecordSetStringA(rec, 1, "Fable");
    query = "CREATE TABLE `?` ( `One` SHORT NOT NULL, `Two` CHAR(255) PRIMARY KEY `One`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* verify that we just created a table called '?', not 'Fable' */
    r = try_query(hdb, "SELECT * from `Fable`");
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    r = try_query(hdb, "SELECT * from `?`");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* try table name as marker without backticks */
    MsiRecordSetStringA(rec, 1, "Mable");
    query = "CREATE TABLE ? ( `One` SHORT NOT NULL, `Two` CHAR(255) PRIMARY KEY `One`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* try one column name as marker */
    MsiRecordSetStringA(rec, 1, "One");
    query = "CREATE TABLE `Mable` ( `?` SHORT NOT NULL, `Two` CHAR(255) PRIMARY KEY `One`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try column names as markers */
    rec = MsiCreateRecord(2);
    MsiRecordSetStringA(rec, 1, "One");
    MsiRecordSetStringA(rec, 2, "Two");
    query = "CREATE TABLE `Mable` ( `?` SHORT NOT NULL, `?` CHAR(255) PRIMARY KEY `One`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try names with backticks */
    rec = MsiCreateRecord(3);
    MsiRecordSetStringA(rec, 1, "One");
    MsiRecordSetStringA(rec, 2, "Two");
    MsiRecordSetStringA(rec, 3, "One");
    query = "CREATE TABLE `Mable` ( `?` SHORT NOT NULL, `?` CHAR(255) PRIMARY KEY `?`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* try names with backticks, minus definitions */
    query = "CREATE TABLE `Mable` ( `?`, `?` PRIMARY KEY `?`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* try names without backticks */
    query = "CREATE TABLE `Mable` ( ? SHORT NOT NULL, ? CHAR(255) PRIMARY KEY ?)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try one long marker */
    rec = MsiCreateRecord(1);
    MsiRecordSetStringA(rec, 1, "`One` SHORT NOT NULL, `Two` CHAR(255) PRIMARY KEY `One`");
    query = "CREATE TABLE `Mable` ( ? )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try all names as markers */
    rec = MsiCreateRecord(4);
    MsiRecordSetStringA(rec, 1, "Mable");
    MsiRecordSetStringA(rec, 2, "One");
    MsiRecordSetStringA(rec, 3, "Two");
    MsiRecordSetStringA(rec, 4, "One");
    query = "CREATE TABLE `?` ( `?` SHORT NOT NULL, `?` CHAR(255) PRIMARY KEY `?`)";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try a legit insert */
    query = "INSERT INTO `Table` ( `One`, `Two` ) VALUES ( 5, 'hello' )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = try_query(hdb, "SELECT * from `Table`");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* try values as markers */
    rec = MsiCreateRecord(2);
    MsiRecordSetInteger(rec, 1, 4);
    MsiRecordSetStringA(rec, 2, "hi");
    query = "INSERT INTO `Table` ( `One`, `Two` ) VALUES ( ?, '?' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    MsiCloseHandle(rec);

    /* try column names and values as markers */
    rec = MsiCreateRecord(4);
    MsiRecordSetStringA(rec, 1, "One");
    MsiRecordSetStringA(rec, 2, "Two");
    MsiRecordSetInteger(rec, 3, 5);
    MsiRecordSetStringA(rec, 4, "hi");
    query = "INSERT INTO `Table` ( `?`, `?` ) VALUES ( ?, '?' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try column names as markers */
    rec = MsiCreateRecord(2);
    MsiRecordSetStringA(rec, 1, "One");
    MsiRecordSetStringA(rec, 2, "Two");
    query = "INSERT INTO `Table` ( `?`, `?` ) VALUES ( 3, 'yellow' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* try table name as a marker */
    rec = MsiCreateRecord(1);
    MsiRecordSetStringA(rec, 1, "Table");
    query = "INSERT INTO `?` ( `One`, `Two` ) VALUES ( 2, 'green' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    MsiCloseHandle(rec);

    /* try table name and values as markers */
    rec = MsiCreateRecord(3);
    MsiRecordSetStringA(rec, 1, "Table");
    MsiRecordSetInteger(rec, 2, 10);
    MsiRecordSetStringA(rec, 3, "haha");
    query = "INSERT INTO `?` ( `One`, `Two` ) VALUES ( ?, '?' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_FUNCTION_FAILED, "Expected ERROR_FUNCTION_FAILED, got %d\n", r);
    MsiCloseHandle(rec);

    /* try all markers */
    rec = MsiCreateRecord(5);
    MsiRecordSetStringA(rec, 1, "Table");
    MsiRecordSetStringA(rec, 1, "One");
    MsiRecordSetStringA(rec, 1, "Two");
    MsiRecordSetInteger(rec, 2, 10);
    MsiRecordSetStringA(rec, 3, "haha");
    query = "INSERT INTO `?` ( `?`, `?` ) VALUES ( ?, '?' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);
    MsiCloseHandle(rec);

    /* insert an integer as a string */
    rec = MsiCreateRecord(2);
    MsiRecordSetStringA(rec, 1, "11");
    MsiRecordSetStringA(rec, 2, "hi");
    query = "INSERT INTO `Table` ( `One`, `Two` ) VALUES ( ?, '?' )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    MsiCloseHandle(rec);

    /* leave off the '' for the string */
    rec = MsiCreateRecord(2);
    MsiRecordSetInteger(rec, 1, 12);
    MsiRecordSetStringA(rec, 2, "hi");
    query = "INSERT INTO `Table` ( `One`, `Two` ) VALUES ( ?, ? )";
    r = run_query(hdb, rec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    MsiCloseHandle(rec);

    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}