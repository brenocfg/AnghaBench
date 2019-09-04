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
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_special_tables(void)
{
    const char *query;
    MSIHANDLE hdb = 0;
    UINT r;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `_Properties` ( "
        "`foo` INT NOT NULL, `bar` INT LOCALIZABLE PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    query = "CREATE TABLE `_Storages` ( "
        "`foo` INT NOT NULL, `bar` INT LOCALIZABLE PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "created _Streams table\n");

    query = "CREATE TABLE `_Streams` ( "
        "`foo` INT NOT NULL, `bar` INT LOCALIZABLE PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "created _Streams table\n");

    query = "CREATE TABLE `_Tables` ( "
        "`foo` INT NOT NULL, `bar` INT LOCALIZABLE PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "created _Tables table\n");

    query = "CREATE TABLE `_Columns` ( "
        "`foo` INT NOT NULL, `bar` INT LOCALIZABLE PRIMARY KEY `foo`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "created _Columns table\n");

    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");
}