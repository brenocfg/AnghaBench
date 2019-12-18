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
typedef  char* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_select_with_tablenames(void)
{
    MSIHANDLE hdb, view, rec;
    LPCSTR query;
    UINT r;
    int i;

    int vals[4][2] = {
        {1,12},
        {4,12},
        {1,15},
        {4,15}};

    hdb = create_db();
    ok(hdb, "failed to create db\n");

    /* Build a pair of tables with the same column names, but unique data */
    query = "CREATE TABLE `T1` ( `A` SHORT, `B` SHORT PRIMARY KEY `A`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `T1` ( `A`, `B` ) VALUES ( 1, 2 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `T1` ( `A`, `B` ) VALUES ( 4, 5 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `T2` ( `A` SHORT, `B` SHORT PRIMARY KEY `A`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `T2` ( `A`, `B` ) VALUES ( 11, 12 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `T2` ( `A`, `B` ) VALUES ( 14, 15 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);


    /* Test that selection based on prefixing the column with the table
     * actually selects the right data */

    query = "SELECT T1.A, T2.B FROM T1,T2";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    for (i = 0; i < 4; i++)
    {
        r = MsiViewFetch(view, &rec);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

        r = MsiRecordGetInteger(rec, 1);
        ok(r == vals[i][0], "Expected %d, got %d\n", vals[i][0], r);

        r = MsiRecordGetInteger(rec, 2);
        ok(r == vals[i][1], "Expected %d, got %d\n", vals[i][1], r);

        MsiCloseHandle(rec);
    }

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);
    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}