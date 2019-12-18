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

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MSIMODIFY_INSERT_TEMPORARY ; 
 int /*<<< orphan*/  MSIMODIFY_REFRESH ; 
 int /*<<< orphan*/  MSIMODIFY_UPDATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MsiRecordSetInteger (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiViewModify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_where_viewmodify(void)
{
    MSIHANDLE hdb, hview, hrec;
    const char *query;
    UINT r;

    DeleteFileA(msifile);

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `Table` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Table` ( `A`, `B` ) VALUES ( 1, 2 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Table` ( `A`, `B` ) VALUES ( 3, 4 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Table` ( `A`, `B` ) VALUES ( 5, 6 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* `B` = 3 doesn't match, but the view shouldn't be executed */
    query = "SELECT * FROM `Table` WHERE `B` = 3";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    hrec = MsiCreateRecord(2);
    MsiRecordSetInteger(hrec, 1, 7);
    MsiRecordSetInteger(hrec, 2, 8);

    r = MsiViewModify(hview, MSIMODIFY_INSERT_TEMPORARY, hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `Table` WHERE `A` = 7";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 7, "Expected 7, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 8, "Expected 8, got %d\n", r);

    MsiRecordSetInteger(hrec, 2, 9);

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `Table` WHERE `A` = 7";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 7, "Expected 7, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 9, "Expected 9, got %d\n", r);

    query = "UPDATE `Table` SET `B` = 10 WHERE `A` = 7";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewModify(hview, MSIMODIFY_REFRESH, hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 7, "Expected 7, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 10, "Expected 10, got %d\n", r);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);
    MsiCloseHandle(hdb);
}