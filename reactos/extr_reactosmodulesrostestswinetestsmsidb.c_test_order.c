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
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiRecordGetStringA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_db () ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_order(void)
{
    MSIHANDLE hdb, hview, hrec;
    CHAR buffer[MAX_PATH];
    LPCSTR query;
    UINT r, sz;
    int val;

    hdb = create_db();
    ok(hdb, "failed to create db\n");

    query = "CREATE TABLE `Empty` ( `A` SHORT NOT NULL PRIMARY KEY `A`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `Mesa` ( `A` SHORT NOT NULL, `B` SHORT, `C` SHORT PRIMARY KEY `A`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Mesa` ( `A`, `B`, `C` ) VALUES ( 1, 2, 9 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Mesa` ( `A`, `B`, `C` ) VALUES ( 3, 4, 7 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Mesa` ( `A`, `B`, `C` ) VALUES ( 5, 6, 8 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `Sideboard` ( `D` SHORT NOT NULL, `E` SHORT, `F` SHORT PRIMARY KEY `D`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Sideboard` ( `D`, `E`, `F` ) VALUES ( 10, 11, 18 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Sideboard` ( `D`, `E`, `F` ) VALUES ( 12, 13, 16 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Sideboard` ( `D`, `E`, `F` ) VALUES ( 14, 15, 17 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT `A`, `B` FROM `Mesa` ORDER BY `C`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 3, "Expected 3, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 4, "Expected 3, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 5, "Expected 5, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 6, "Expected 6, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 1, "Expected 1, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 2, "Expected 2, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT `A`, `D` FROM `Mesa`, `Sideboard` ORDER BY `F`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 1, "Expected 1, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 12, "Expected 12, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 3, "Expected 3, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 12, "Expected 12, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 5, "Expected 5, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 12, "Expected 12, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 1, "Expected 1, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 14, "Expected 14, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 3, "Expected 3, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 14, "Expected 14, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 5, "Expected 5, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 14, "Expected 14, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 1, "Expected 1, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 10, "Expected 10, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 3, "Expected 3, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 10, "Expected 10, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(hrec, 1);
    ok(val == 5, "Expected 5, got %d\n", val);

    val = MsiRecordGetInteger(hrec, 2);
    ok(val == 10, "Expected 10, got %d\n", val);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "SELECT * FROM `Empty` ORDER BY `A`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "CREATE TABLE `Buffet` ( `One` CHAR(72), `Two` SHORT PRIMARY KEY `One`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Buffet` ( `One`, `Two` ) VALUES ( 'uno',  2)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Buffet` ( `One`, `Two` ) VALUES ( 'dos',  3)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `Buffet` ( `One`, `Two` ) VALUES ( 'tres',  1)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `Buffet` WHERE `One` = 'dos' ORDER BY `Two`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "dos"), "Expected \"dos\", got \"%s\"\n", buffer);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 3, "Expected 3, got %d\n", r);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);
    MsiCloseHandle(hdb);
}