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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiRecordGetStringA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiRecordSetInteger (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  create_db () ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_select_markers(void)
{
    MSIHANDLE hdb = 0, rec, view, res;
    LPCSTR query;
    UINT r;
    DWORD size;
    CHAR buf[MAX_PATH];

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    r = run_query(hdb, 0,
            "CREATE TABLE `Table` (`One` CHAR(72), `Two` CHAR(72), `Three` SHORT PRIMARY KEY `One`, `Two`, `Three`)");
    ok(r == S_OK, "cannot create table: %d\n", r);

    r = run_query(hdb, 0, "INSERT INTO `Table` "
            "( `One`, `Two`, `Three` ) VALUES ( 'apple', 'one', 1 )");
    ok(r == S_OK, "cannot add file to the Media table: %d\n", r);

    r = run_query(hdb, 0, "INSERT INTO `Table` "
            "( `One`, `Two`, `Three` ) VALUES ( 'apple', 'two', 1 )");
    ok(r == S_OK, "cannot add file to the Media table: %d\n", r);

    r = run_query(hdb, 0, "INSERT INTO `Table` "
            "( `One`, `Two`, `Three` ) VALUES ( 'apple', 'two', 2 )");
    ok(r == S_OK, "cannot add file to the Media table: %d\n", r);

    r = run_query(hdb, 0, "INSERT INTO `Table` "
            "( `One`, `Two`, `Three` ) VALUES ( 'banana', 'three', 3 )");
    ok(r == S_OK, "cannot add file to the Media table: %d\n", r);

    rec = MsiCreateRecord(2);
    MsiRecordSetStringA(rec, 1, "apple");
    MsiRecordSetStringA(rec, 2, "two");

    query = "SELECT * FROM `Table` WHERE `One`=? AND `Two`=? ORDER BY `Three`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewExecute(view, rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "apple"), "Expected apple, got %s\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "two"), "Expected two, got %s\n", buf);

    r = MsiRecordGetInteger(res, 3);
    ok(r == 1, "Expected 1, got %d\n", r);

    MsiCloseHandle(res);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "apple"), "Expected apple, got %s\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "two"), "Expected two, got %s\n", buf);

    r = MsiRecordGetInteger(res, 3);
    ok(r == 2, "Expected 2, got %d\n", r);

    MsiCloseHandle(res);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    rec = MsiCreateRecord(2);
    MsiRecordSetStringA(rec, 1, "one");
    MsiRecordSetInteger(rec, 2, 1);

    query = "SELECT * FROM `Table` WHERE `Two`<>? AND `Three`>? ORDER BY `Three`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "apple"), "Expected apple, got %s\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "two"), "Expected two, got %s\n", buf);

    r = MsiRecordGetInteger(res, 3);
    ok(r == 2, "Expected 2, got %d\n", r);

    MsiCloseHandle(res);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "banana"), "Expected banana, got %s\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(res, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "three"), "Expected three, got %s\n", buf);

    r = MsiRecordGetInteger(res, 3);
    ok(r == 3, "Expected 3, got %d\n", r);

    MsiCloseHandle(res);

    r = MsiViewFetch(view, &res);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);
    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}