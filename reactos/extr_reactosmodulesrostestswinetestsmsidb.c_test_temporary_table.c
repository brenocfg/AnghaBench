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
typedef  int MSIHANDLE ;
typedef  scalar_t__ MSICONDITION ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 scalar_t__ MSICONDITION_ERROR ; 
 scalar_t__ MSICONDITION_FALSE ; 
 scalar_t__ MSICONDITION_NONE ; 
 scalar_t__ MSICONDITION_TRUE ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 scalar_t__ MsiDatabaseIsTablePersistentA (int,char*) ; 
 scalar_t__ MsiDatabaseOpenViewA (int,char const*,int*) ; 
 scalar_t__ MsiRecordGetStringA (int,int,char*,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int) ; 
 scalar_t__ MsiViewGetColumnInfo (int,int /*<<< orphan*/ ,int*) ; 
 int create_db () ; 
 scalar_t__ do_query (int,char*,int*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ run_query (int,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_temporary_table(void)
{
    MSICONDITION cond;
    MSIHANDLE hdb = 0, view = 0, rec;
    const char *query;
    UINT r;
    char buf[0x10];
    DWORD sz;

    cond = MsiDatabaseIsTablePersistentA(0, NULL);
    ok( cond == MSICONDITION_ERROR, "wrong return condition\n");

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, NULL);
    ok( cond == MSICONDITION_ERROR, "wrong return condition\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "_Tables");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "_Columns");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "_Storages");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "_Streams");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    query = "CREATE TABLE `P` ( `B` SHORT NOT NULL, `C` CHAR(255) PRIMARY KEY `C`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "P");
    ok( cond == MSICONDITION_TRUE, "wrong return condition\n");

    query = "CREATE TABLE `P2` ( `B` SHORT NOT NULL, `C` CHAR(255) PRIMARY KEY `C`) HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "P2");
    ok( cond == MSICONDITION_TRUE, "wrong return condition\n");

    query = "CREATE TABLE `T` ( `B` SHORT NOT NULL TEMPORARY, `C` CHAR(255) TEMPORARY PRIMARY KEY `C`) HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "T");
    ok( cond == MSICONDITION_FALSE, "wrong return condition\n");

    query = "CREATE TABLE `T2` ( `B` SHORT NOT NULL TEMPORARY, `C` CHAR(255) TEMPORARY PRIMARY KEY `C`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    query = "SELECT * FROM `T2`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    cond = MsiDatabaseIsTablePersistentA(hdb, "T2");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    query = "CREATE TABLE `T3` ( `B` SHORT NOT NULL TEMPORARY, `C` CHAR(255) PRIMARY KEY `C`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "T3");
    ok( cond == MSICONDITION_TRUE, "wrong return condition\n");

    query = "CREATE TABLE `T4` ( `B` SHORT NOT NULL, `C` CHAR(255) TEMPORARY PRIMARY KEY `C`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_FUNCTION_FAILED, "failed to add table\n");

    cond = MsiDatabaseIsTablePersistentA(hdb, "T4");
    ok( cond == MSICONDITION_NONE, "wrong return condition\n");

    query = "CREATE TABLE `T5` ( `B` SHORT NOT NULL TEMP, `C` CHAR(255) TEMP PRIMARY KEY `C`) HOLD";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "failed to add table\n");

    query = "select * from `T`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "failed to query table\n");
    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "failed to get column info\n");

    sz = sizeof buf;
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string\n");
    ok( 0 == strcmp("G255", buf), "wrong column type\n");

    sz = sizeof buf;
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string\n");
    ok( 0 == strcmp("j2", buf), "wrong column type\n");

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* query the table data */
    rec = 0;
    r = do_query(hdb, "select * from `_Tables` where `Name` = 'T'", &rec);
    ok( r == ERROR_SUCCESS, "temporary table exists in _Tables\n");
    MsiCloseHandle( rec );

    /* query the column data */
    rec = 0;
    r = do_query(hdb, "select * from `_Columns` where `Table` = 'T' AND `Name` = 'B'", &rec);
    ok( r == ERROR_NO_MORE_ITEMS, "temporary table exists in _Columns\n");
    if (rec) MsiCloseHandle( rec );

    r = do_query(hdb, "select * from `_Columns` where `Table` = 'T' AND `Name` = 'C'", &rec);
    ok( r == ERROR_NO_MORE_ITEMS, "temporary table exists in _Columns\n");
    if (rec) MsiCloseHandle( rec );

    MsiCloseHandle( hdb );
    DeleteFileA(msifile);
}