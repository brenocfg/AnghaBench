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
typedef  scalar_t__ MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MSIMODIFY_UPDATE ; 
 int MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char const*,scalar_t__*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordSetInteger (scalar_t__,int,int) ; 
 int MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,scalar_t__) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 int MsiViewModify (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (scalar_t__,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_viewmodify_update(void)
{
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT i, test_max, offset, count;
    const char *query;
    UINT r;

    DeleteFileA(msifile);

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `table` (`A` INT, `B` INT PRIMARY KEY `A`)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "INSERT INTO `table` (`A`, `B`) VALUES (1, 2)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "INSERT INTO `table` (`A`, `B`) VALUES (3, 4)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "INSERT INTO `table` (`A`, `B`) VALUES (5, 6)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "SELECT `B` FROM `table`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordSetInteger(hrec, 1, 0);
    ok(r == ERROR_SUCCESS, "failed to set integer\n");

    r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
    ok(r == ERROR_SUCCESS, "MsiViewModify failed: %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `table`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 0, "Expected 0, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 3, "Expected 3, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 4, "Expected 4, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 5, "Expected 5, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 6, "Expected 6, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* loop through all elements */
    query = "SELECT `B` FROM `table`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    while (TRUE)
    {
        r = MsiViewFetch(hview, &hrec);
        if (r != ERROR_SUCCESS)
            break;

        r = MsiRecordSetInteger(hrec, 1, 0);
        ok(r == ERROR_SUCCESS, "failed to set integer\n");

        r = MsiViewModify(hview, MSIMODIFY_UPDATE, hrec);
        ok(r == ERROR_SUCCESS, "MsiViewModify failed: %d\n", r);

        r = MsiCloseHandle(hrec);
        ok(r == ERROR_SUCCESS, "failed to close record\n");
    }

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "SELECT * FROM `table`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 0, "Expected 0, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 3, "Expected 3, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 0, "Expected 0, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 5, "Expected 5, got %d\n", r);
    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 0, "Expected 0, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "failed to close record\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "CREATE TABLE `table2` (`A` INT, `B` INT PRIMARY KEY `A`)";
    r = run_query( hdb, 0, query );
    ok(r == ERROR_SUCCESS, "query failed\n");

    query = "INSERT INTO `table2` (`A`, `B`) VALUES (?, ?)";
    r = MsiDatabaseOpenViewA( hdb, query, &hview );
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");

    test_max = 100;
    offset = 1234;
    for(i = 0; i < test_max; i++)
    {

        hrec = MsiCreateRecord( 2 );
        MsiRecordSetInteger( hrec, 1, test_max - i );
        MsiRecordSetInteger( hrec, 2, i );

        r = MsiViewExecute( hview, hrec );
        ok(r == ERROR_SUCCESS, "Got %d\n", r);

        r = MsiCloseHandle( hrec );
        ok(r == ERROR_SUCCESS, "Got %d\n", r);
    }

    r = MsiViewClose( hview );
    ok(r == ERROR_SUCCESS, "Got %d\n", r);
    r = MsiCloseHandle( hview );
    ok(r == ERROR_SUCCESS, "Got %d\n", r);

    /* Update. */
    query = "SELECT * FROM `table2` ORDER BY `B`";
    r = MsiDatabaseOpenViewA( hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute( hview, 0 );
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    count = 0;
    while (MsiViewFetch( hview, &hrec ) == ERROR_SUCCESS)
    {
        UINT b = MsiRecordGetInteger( hrec, 2 );

        r = MsiRecordSetInteger( hrec, 2, b + offset);
        ok(r == ERROR_SUCCESS, "Got %d\n", r);

        r = MsiViewModify( hview, MSIMODIFY_UPDATE, hrec );
        ok(r == ERROR_SUCCESS, "Got %d\n", r);

        r = MsiCloseHandle(hrec);
        ok(r == ERROR_SUCCESS, "failed to close record\n");
        count++;
    }
    ok(count == test_max, "Got count %d\n", count);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* Recheck. */
    query = "SELECT * FROM `table2` ORDER BY `B`";
    r = MsiDatabaseOpenViewA( hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute( hview, 0 );
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    count = 0;
    while (MsiViewFetch( hview, &hrec ) == ERROR_SUCCESS)
    {
        UINT a = MsiRecordGetInteger( hrec, 1 );
        UINT b = MsiRecordGetInteger( hrec, 2 );
        ok( ( test_max - a + offset) == b, "Got (%d, %d), expected (%d, %d)\n",
            a, b, test_max - a + offset, b);

        r = MsiCloseHandle(hrec);
        ok(r == ERROR_SUCCESS, "failed to close record\n");
        count++;
    }
    ok(count == test_max, "Got count %d\n", count);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiCloseHandle( hdb );
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase close failed\n");
}