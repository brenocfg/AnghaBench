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
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MSI_NULL_INTEGER ; 
 int MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiRecordGetFieldCount (int /*<<< orphan*/ ) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewGetColumnInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int check_record (int /*<<< orphan*/ ,int,char*) ; 
 int do_query (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_integers(void)
{
    MSIHANDLE hdb = 0, view = 0, rec = 0;
    DWORD count, i;
    const char *query;
    UINT r;

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    /* create a table */
    query = "CREATE TABLE `integers` ( "
            "`one` SHORT, `two` INT, `three` INTEGER, `four` LONG, "
            "`five` SHORT NOT NULL, `six` INT NOT NULL, "
            "`seven` INTEGER NOT NULL, `eight` LONG NOT NULL "
            "PRIMARY KEY `one`)";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(view);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `integers`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 8, "Expected 8, got %d\n", count);
    ok(check_record(rec, 1, "one"), "Expected one\n");
    ok(check_record(rec, 2, "two"), "Expected two\n");
    ok(check_record(rec, 3, "three"), "Expected three\n");
    ok(check_record(rec, 4, "four"), "Expected four\n");
    ok(check_record(rec, 5, "five"), "Expected five\n");
    ok(check_record(rec, 6, "six"), "Expected six\n");
    ok(check_record(rec, 7, "seven"), "Expected seven\n");
    ok(check_record(rec, 8, "eight"), "Expected eight\n");
    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 8, "Expected 8, got %d\n", count);
    ok(check_record(rec, 1, "I2"), "Expected I2\n");
    ok(check_record(rec, 2, "I2"), "Expected I2\n");
    ok(check_record(rec, 3, "I2"), "Expected I2\n");
    ok(check_record(rec, 4, "I4"), "Expected I4\n");
    ok(check_record(rec, 5, "i2"), "Expected i2\n");
    ok(check_record(rec, 6, "i2"), "Expected i2\n");
    ok(check_record(rec, 7, "i2"), "Expected i2\n");
    ok(check_record(rec, 8, "i4"), "Expected i4\n");
    MsiCloseHandle(rec);

    MsiViewClose(view);
    MsiCloseHandle(view);

    /* insert values into it, NULL where NOT NULL is specified */
    query = "INSERT INTO `integers` ( `one`, `two`, `three`, `four`, `five`, `six`, `seven`, `eight` )"
        "VALUES('', '', '', '', '', '', '', '')";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_FUNCTION_FAILED, "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "SELECT * FROM `integers`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiRecordGetFieldCount(rec);
    ok(r == -1, "record count wrong: %d\n", r);

    MsiCloseHandle(rec);

    /* insert legitimate values into it */
    query = "INSERT INTO `integers` ( `one`, `two`, `three`, `four`, `five`, `six`, `seven`, `eight` )"
        "VALUES('', '2', '', '4', '5', '6', '7', '8')";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `integers`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetFieldCount(rec);
    ok(r == 8, "record count wrong: %d\n", r);

    i = MsiRecordGetInteger(rec, 1);
    ok(i == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", i);
    i = MsiRecordGetInteger(rec, 3);
    ok(i == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", i);
    i = MsiRecordGetInteger(rec, 2);
    ok(i == 2, "Expected 2, got %d\n", i);
    i = MsiRecordGetInteger(rec, 4);
    ok(i == 4, "Expected 4, got %d\n", i);
    i = MsiRecordGetInteger(rec, 5);
    ok(i == 5, "Expected 5, got %d\n", i);
    i = MsiRecordGetInteger(rec, 6);
    ok(i == 6, "Expected 6, got %d\n", i);
    i = MsiRecordGetInteger(rec, 7);
    ok(i == 7, "Expected 7, got %d\n", i);
    i = MsiRecordGetInteger(rec, 8);
    ok(i == 8, "Expected 8, got %d\n", i);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    r = MsiDatabaseCommit(hdb);
    ok(r == ERROR_SUCCESS, "MsiDatabaseCommit failed\n");

    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = DeleteFileA(msifile);
    ok(r == TRUE, "file didn't exist after commit\n");
}