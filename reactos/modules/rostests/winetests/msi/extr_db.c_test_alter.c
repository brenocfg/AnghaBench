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
typedef  scalar_t__ MSICONDITION ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSICONDITION_FALSE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseIsTablePersistentA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_alter(void)
{
    MSICONDITION cond;
    MSIHANDLE hdb = 0;
    const char *query;
    UINT r;

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    query = "CREATE TABLE `T` ( `B` SHORT NOT NULL TEMPORARY, `C` CHAR(255) TEMPORARY PRIMARY KEY `C`) HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "T");
    ok( cond == MSICONDITION_FALSE, "wrong return condition\n");

    query = "ALTER TABLE `T` HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to hold table %d\n", r);

    query = "ALTER TABLE `T` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to free table\n");

    query = "ALTER TABLE `T` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to free table\n");

    query = "ALTER TABLE `T` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "failed to free table\n");

    query = "ALTER TABLE `T` HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "failed to hold table %d\n", r);

    /* table T is removed */
    query = "SELECT * FROM `T`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* create the table again */
    query = "CREATE TABLE `U` ( `A` INTEGER, `B` INTEGER PRIMARY KEY `B`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* up the ref count */
    query = "ALTER TABLE `U` HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to free table\n");

    /* add column, no data type */
    query = "ALTER TABLE `U` ADD `C`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "ALTER TABLE `U` ADD `C` INTEGER";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* add column C again */
    query = "ALTER TABLE `U` ADD `C` INTEGER";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "ALTER TABLE `U` ADD `D` INTEGER TEMPORARY";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `D` ) VALUES ( 1, 2, 3, 4 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "ALTER TABLE `U` ADD `D` INTEGER TEMPORARY HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `D` ) VALUES ( 5, 6, 7, 8 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `U` WHERE `D` = 8";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "ALTER TABLE `U` ADD `D` INTEGER TEMPORARY FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "ALTER COLUMN `D` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* drop the ref count */
    query = "ALTER TABLE `U` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* table is not empty */
    query = "SELECT * FROM `U`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* column D is removed */
    query = "SELECT * FROM `U` WHERE `D` = 8";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `D` ) VALUES ( 9, 10, 11, 12 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* add the column again */
    query = "ALTER TABLE `U` ADD `E` INTEGER TEMPORARY HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* up the ref count */
    query = "ALTER TABLE `U` HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `E` ) VALUES ( 13, 14, 15, 16 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `U` WHERE `E` = 16";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* drop the ref count */
    query = "ALTER TABLE `U` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `E` ) VALUES ( 17, 18, 19, 20 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `U` WHERE `E` = 20";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* drop the ref count */
    query = "ALTER TABLE `U` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* table still exists */
    query = "SELECT * FROM `U`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* col E is removed */
    query = "SELECT * FROM `U` WHERE `E` = 20";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "INSERT INTO `U` ( `A`, `B`, `C`, `E` ) VALUES ( 20, 21, 22, 23 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    /* drop the ref count once more */
    query = "ALTER TABLE `U` FREE";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* table still exists */
    query = "SELECT * FROM `U`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle( hdb );
    DeleteFileA(msifile);
}