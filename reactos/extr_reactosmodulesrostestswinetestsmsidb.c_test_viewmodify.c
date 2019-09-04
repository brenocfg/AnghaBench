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
typedef  int UINT ;
typedef  scalar_t__ MSIHANDLE ;
typedef  scalar_t__ MSIDBERROR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_DATA ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_SUCCESS ; 
 scalar_t__ MSIDBERROR_DUPLICATEKEY ; 
 scalar_t__ MSIDBERROR_INVALIDARG ; 
 scalar_t__ MSIDBERROR_MOREDATA ; 
 scalar_t__ MSIDBERROR_NOERROR ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MSIMODIFY_INSERT ; 
 int MSIMODIFY_INSERT_TEMPORARY ; 
 int MSIMODIFY_MERGE ; 
 int MSIMODIFY_UPDATE ; 
 int MSIMODIFY_VALIDATE_NEW ; 
 int MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char const*,scalar_t__*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordGetStringA (scalar_t__,int,char*,int*) ; 
 int MsiRecordSetInteger (scalar_t__,int,int) ; 
 int MsiRecordSetStringA (scalar_t__,int,char*) ; 
 int MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 scalar_t__ MsiViewGetErrorA (scalar_t__,char*,int*) ; 
 int MsiViewModify (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_viewmodify(void)
{
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT r;
    MSIDBERROR err;
    const char *query;
    char buffer[0x100];
    DWORD sz;

    DeleteFileA(msifile);

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `phone` ( "
            "`id` INT, `name` CHAR(32), `number` CHAR(32) "
            "PRIMARY KEY `id`)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "CREATE TABLE `_Validation` ( "
            "`Table` CHAR(32) NOT NULL, `Column` CHAR(32) NOT NULL, "
            "`Nullable` CHAR(4) NOT NULL, `MinValue` INT, `MaxValue` INT, "
            "`KeyTable` CHAR(255), `KeyColumn` SHORT, `Category` CHAR(32), "
            "`Set` CHAR(255), `Description` CHAR(255) PRIMARY KEY `Table`, `Column`)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "INSERT INTO `_Validation` ( `Table`, `Column`, `Nullable` ) "
            "VALUES('phone', 'id', 'N')";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    /* check what the error function reports without doing anything */
    sz = 0;
    /* passing NULL as the 3rd param make function to crash on older platforms */
    err = MsiViewGetErrorA( 0, NULL, &sz );
    ok(err == MSIDBERROR_INVALIDARG, "MsiViewGetError return\n");

    /* open a view */
    query = "SELECT * FROM `phone`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");

    /* see what happens with a good hview and bad args */
    err = MsiViewGetErrorA( hview, NULL, NULL );
    ok(err == MSIDBERROR_INVALIDARG || err == MSIDBERROR_NOERROR,
       "MsiViewGetError returns %u (expected -3)\n", err);
    err = MsiViewGetErrorA( hview, buffer, NULL );
    ok(err == MSIDBERROR_INVALIDARG, "MsiViewGetError return\n");

    /* see what happens with a zero length buffer */
    sz = 0;
    buffer[0] = 'x';
    err = MsiViewGetErrorA( hview, buffer, &sz );
    ok(err == MSIDBERROR_MOREDATA, "MsiViewGetError return\n");
    ok(buffer[0] == 'x', "buffer cleared\n");
    ok(sz == 0, "size not zero\n");

    /* ok this one is strange */
    sz = 0;
    err = MsiViewGetErrorA( hview, NULL, &sz );
    ok(err == MSIDBERROR_NOERROR, "MsiViewGetError return\n");
    ok(sz == 0, "size not zero\n");

    /* see if it really has an error */
    sz = sizeof buffer;
    buffer[0] = 'x';
    err = MsiViewGetErrorA( hview, buffer, &sz );
    ok(err == MSIDBERROR_NOERROR, "MsiViewGetError return\n");
    ok(buffer[0] == 0, "buffer not cleared\n");
    ok(sz == 0, "size not zero\n");

    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    /* try some invalid records */
    r = MsiViewModify(hview, MSIMODIFY_INSERT, 0 );
    ok(r == ERROR_INVALID_HANDLE, "MsiViewModify failed\n");
    r = MsiViewModify(hview, -1, 0 );
    ok(r == ERROR_INVALID_HANDLE, "MsiViewModify failed\n");

    /* try an small record */
    hrec = MsiCreateRecord(1);
    r = MsiViewModify(hview, -1, hrec );
    ok(r == ERROR_INVALID_DATA, "MsiViewModify failed\n");

    sz = sizeof buffer;
    buffer[0] = 'x';
    err = MsiViewGetErrorA( hview, buffer, &sz );
    ok(err == MSIDBERROR_NOERROR, "MsiViewGetError return\n");
    ok(buffer[0] == 0, "buffer not cleared\n");
    ok(sz == 0, "size not zero\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    /* insert a valid record */
    hrec = MsiCreateRecord(3);

    r = MsiRecordSetInteger(hrec, 1, 1);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "bob");
    ok(r == ERROR_SUCCESS, "failed to set string\n");
    r = MsiRecordSetStringA(hrec, 3, "7654321");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewModify(hview, MSIMODIFY_INSERT_TEMPORARY, hrec );
    ok(r == ERROR_SUCCESS, "MsiViewModify failed\n");

    /* validate it */
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewModify(hview, MSIMODIFY_VALIDATE_NEW, hrec );
    ok(r == ERROR_INVALID_DATA, "MsiViewModify failed %u\n", r);

    sz = sizeof buffer;
    buffer[0] = 'x';
    err = MsiViewGetErrorA( hview, buffer, &sz );
    ok(err == MSIDBERROR_DUPLICATEKEY, "MsiViewGetError returned %u\n", err);
    ok(!strcmp(buffer, "id"), "expected \"id\" c, got \"%s\"\n", buffer);
    ok(sz == 2, "size not 2\n");

    /* insert the same thing again */
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    /* should fail ... */
    r = MsiViewModify(hview, MSIMODIFY_INSERT_TEMPORARY, hrec );
    ok(r == ERROR_FUNCTION_FAILED, "MsiViewModify failed\n");

    /* try to merge the same record */
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewModify(hview, MSIMODIFY_MERGE, hrec );
    ok(r == ERROR_SUCCESS, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    /* try merging a new record */
    hrec = MsiCreateRecord(3);

    r = MsiRecordSetInteger(hrec, 1, 10);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "pepe");
    ok(r == ERROR_SUCCESS, "failed to set string\n");
    r = MsiRecordSetStringA(hrec, 3, "7654321");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewModify(hview, MSIMODIFY_MERGE, hrec );
    ok(r == ERROR_SUCCESS, "MsiViewModify failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `phone`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");

    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "MsiRecordGetString failed\n");
    ok(!lstrcmpA(buffer, "bob"), "Expected bob, got %s\n", buffer);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "MsiRecordGetString failed\n");
    ok(!lstrcmpA(buffer, "7654321"), "Expected 7654321, got %s\n", buffer);

    /* update the view, non-primary key */
    r = MsiRecordSetStringA(hrec, 3, "3141592");
    ok(r == ERROR_SUCCESS, "MsiRecordSetString failed\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_SUCCESS, "MsiViewModify failed\n");

    /* do it again */
    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_SUCCESS, "MsiViewModify failed: %d\n", r);

    /* update the view, primary key */
    r = MsiRecordSetInteger(hrec, 1, 5);
    ok(r == ERROR_SUCCESS, "MsiRecordSetInteger failed\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_FUNCTION_FAILED, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `phone`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");

    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "MsiRecordGetString failed\n");
    ok(!lstrcmpA(buffer, "bob"), "Expected bob, got %s\n", buffer);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "MsiRecordGetString failed\n");
    ok(!lstrcmpA(buffer, "3141592"), "Expected 3141592, got %s\n", buffer);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    /* use a record that doesn't come from a view fetch */
    hrec = MsiCreateRecord(3);
    ok(hrec != 0, "MsiCreateRecord failed\n");

    r = MsiRecordSetInteger(hrec, 1, 3);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "jane");
    ok(r == ERROR_SUCCESS, "failed to set string\n");
    r = MsiRecordSetStringA(hrec, 3, "112358");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_FUNCTION_FAILED, "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    /* use a record that doesn't come from a view fetch, primary key matches */
    hrec = MsiCreateRecord(3);
    ok(hrec != 0, "MsiCreateRecord failed\n");

    r = MsiRecordSetInteger(hrec, 1, 1);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "jane");
    ok(r == ERROR_SUCCESS, "failed to set string\n");
    r = MsiRecordSetStringA(hrec, 3, "112358");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_FUNCTION_FAILED, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    hrec = MsiCreateRecord(3);

    r = MsiRecordSetInteger(hrec, 1, 2);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "nick");
    ok(r == ERROR_SUCCESS, "failed to set string\n");
    r = MsiRecordSetStringA(hrec, 3, "141421");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewModify(hview, MSIMODIFY_INSERT_TEMPORARY, hrec );
    ok(r == ERROR_SUCCESS, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `phone` WHERE `id` = 1";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    /* change the id to match the second row */
    r = MsiRecordSetInteger(hrec, 1, 2);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "jerry");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_FUNCTION_FAILED, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* broader search */
    query = "SELECT * FROM `phone` ORDER BY `id`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    /* change the id to match the second row */
    r = MsiRecordSetInteger(hrec, 1, 2);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");
    r = MsiRecordSetStringA(hrec, 2, "jerry");
    ok(r == ERROR_SUCCESS, "failed to set string\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_FUNCTION_FAILED, "MsiViewModify failed\n");

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiCloseHandle( hdb );
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase close failed\n");
}