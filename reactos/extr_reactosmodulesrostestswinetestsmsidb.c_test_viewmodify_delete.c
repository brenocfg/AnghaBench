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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MSIMODIFY_DELETE ; 
 int MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiRecordGetStringA (int /*<<< orphan*/ ,int,char*,int*) ; 
 int MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiViewModify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_viewmodify_delete(void)
{
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT r;
    const char *query;
    char buffer[0x100];
    DWORD sz;

    DeleteFileA(msifile);

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `phone` ( "
            "`id` INT, `name` CHAR(32), `number` CHAR(32) "
            "PRIMARY KEY `id`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES('1', 'Alan', '5030581')";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES('2', 'Barry', '928440')";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES('3', 'Cindy', '2937550')";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `phone` WHERE `id` <= 2";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* delete 1 */
    r = MsiViewModify(hview, MSIMODIFY_DELETE, hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* delete 2 */
    r = MsiViewModify(hview, MSIMODIFY_DELETE, hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `phone`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 3, "Expected 3, got %d\n", r);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "Cindy"), "Expected Cindy, got %s\n", buffer);

    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 3, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "2937550"), "Expected 2937550, got %s\n", buffer);

    r = MsiCloseHandle(hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
}