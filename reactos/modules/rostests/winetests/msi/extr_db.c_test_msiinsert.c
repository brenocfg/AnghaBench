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
typedef  int MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MsiCloseHandle (int) ; 
 int MsiCreateRecord (int) ; 
 int MsiDatabaseCommit (int) ; 
 int MsiDatabaseOpenViewA (int,char const*,int*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int MsiRecordGetFieldCount (int) ; 
 int MsiRecordGetInteger (int,int) ; 
 int MsiRecordGetStringA (int,int,char*,int*) ; 
 int MsiRecordIsNull (int,int /*<<< orphan*/ ) ; 
 int MsiRecordSetInteger (int,int,int) ; 
 int MsiRecordSetStringA (int,int,char*) ; 
 int MsiViewClose (int) ; 
 int MsiViewExecute (int,int) ; 
 int MsiViewFetch (int,int*) ; 
 int TRUE ; 
 int do_query (int,char const*,int*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_msiinsert(void)
{
    MSIHANDLE hdb = 0, hview = 0, hview2 = 0, hrec = 0;
    UINT r;
    const char *query;
    char buf[80];
    DWORD sz;

    DeleteFileA(msifile);

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    /* create a table */
    query = "CREATE TABLE `phone` ( "
            "`id` INT, `name` CHAR(32), `number` CHAR(32) "
            "PRIMARY KEY `id`)";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM phone WHERE number = '8675309'";
    r = MsiDatabaseOpenViewA(hdb, query, &hview2);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview2, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview2, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch produced items\n");

    /* insert a value into it */
    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES('1', 'Abe', '8675309')";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiViewFetch(hview2, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch produced items\n");
    r = MsiViewExecute(hview2, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview2, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed: %u\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");
    r = MsiViewClose(hview2);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview2);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `phone` WHERE `id` = 1";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    /* check the record contains what we put in it */
    r = MsiRecordGetFieldCount(hrec);
    ok(r == 3, "record count wrong\n");

    r = MsiRecordIsNull(hrec, 0);
    ok(r == FALSE, "field 0 not null\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "field 1 contents wrong\n");
    sz = sizeof buf;
    r = MsiRecordGetStringA(hrec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "field 2 content fetch failed\n");
    ok(!strcmp(buf,"Abe"), "field 2 content incorrect\n");
    sz = sizeof buf;
    r = MsiRecordGetStringA(hrec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "field 3 content fetch failed\n");
    ok(!strcmp(buf,"8675309"), "field 3 content incorrect\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* open a select query */
    hrec = 100;
    query = "SELECT * FROM `phone` WHERE `id` >= 10";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");
    ok(hrec == 0, "hrec should be null\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `phone` WHERE `id` < 0";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");

    query = "SELECT * FROM `phone` WHERE `id` <= 0";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");

    query = "SELECT * FROM `phone` WHERE `id` <> 1";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");

    query = "SELECT * FROM `phone` WHERE `id` > 10";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");

    /* now try a few bad INSERT xqueries */
    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES(?, ?)";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "MsiDatabaseOpenView failed\n");

    /* construct a record to insert */
    hrec = MsiCreateRecord(4);
    r = MsiRecordSetInteger(hrec, 1, 2);
    ok(r == ERROR_SUCCESS, "MsiRecordSetInteger failed\n");
    r = MsiRecordSetStringA(hrec, 2, "Adam");
    ok(r == ERROR_SUCCESS, "MsiRecordSetString failed\n");
    r = MsiRecordSetStringA(hrec, 3, "96905305");
    ok(r == ERROR_SUCCESS, "MsiRecordSetString failed\n");

    /* insert another value, using a record and wildcards */
    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES(?, ?, ?)";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");

    if (r == ERROR_SUCCESS)
    {
        r = MsiViewExecute(hview, hrec);
        ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
        r = MsiViewClose(hview);
        ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
        r = MsiCloseHandle(hview);
        ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");
    }
    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiViewFetch(0, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "MsiViewFetch failed\n");

    r = MsiDatabaseCommit(hdb);
    ok(r == ERROR_SUCCESS, "MsiDatabaseCommit failed\n");

    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = DeleteFileA(msifile);
    ok(r == TRUE, "file didn't exist after commit\n");
}