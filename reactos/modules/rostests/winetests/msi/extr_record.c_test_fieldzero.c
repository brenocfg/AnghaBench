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
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_INVALID_TABLE ; 
 int ERROR_SUCCESS ; 
 int FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MSI_NULL_INTEGER ; 
 int MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiDatabaseGetPrimaryKeysA (scalar_t__,char*,scalar_t__*) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char*,scalar_t__*) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordGetStringA (scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int MsiRecordIsNull (scalar_t__,int /*<<< orphan*/ ) ; 
 int MsiRecordSetInteger (scalar_t__,int,int) ; 
 int MsiRecordSetStringA (scalar_t__,int,char*) ; 
 int MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_fieldzero(void)
{
    MSIHANDLE hdb, hview, rec;
    CHAR buf[MAX_PATH];
    LPCSTR query;
    DWORD sz;
    UINT r;

    rec = MsiCreateRecord(1);
    ok(rec != 0, "Expected a valid handle\n");

    r = MsiRecordGetInteger(rec, 0);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, ""), "Expected \"\", got \"%s\"\n", buf);
    ok(sz == 0, "Expected 0, got %d\n", sz);

    r = MsiRecordIsNull(rec, 0);
    ok(r == TRUE, "Expected TRUE, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    r = MsiRecordSetInteger(rec, 1, 42);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 0);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, ""), "Expected \"\", got \"%s\"\n", buf);
    ok(sz == 0, "Expected 0, got %d\n", sz);

    r = MsiRecordIsNull(rec, 0);
    ok(r == TRUE, "Expected TRUE, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == 42, "Expected 42, got %d\n", r);

    r = MsiRecordSetStringA(rec, 1, "bologna");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 0);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, ""), "Expected \"\", got \"%s\"\n", buf);
    ok(sz == 0, "Expected 0, got %d\n", sz);

    r = MsiRecordIsNull(rec, 0);
    ok(r == TRUE, "Expected TRUE, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "bologna"), "Expected \"bologna\", got \"%s\"\n", buf);
    ok(sz == 7, "Expected 7, got %d\n", sz);

    MsiCloseHandle(rec);

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `drone` ( "
           "`id` INT, `name` CHAR(32), `number` CHAR(32) "
           "PRIMARY KEY `id`)";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    query = "INSERT INTO `drone` ( `id`, `name`, `number` )"
           "VALUES('1', 'Abe', '8675309')";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiDatabaseGetPrimaryKeysA(hdb, "drone", &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 0);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "drone"), "Expected \"drone\", got \"%s\"\n", buf);
    ok(sz == 5, "Expected 5, got %d\n", sz);

    r = MsiRecordIsNull(rec, 0);
    ok(r == FALSE, "Expected FALSE, got %d\n", r);

    MsiCloseHandle(rec);

    r = MsiDatabaseGetPrimaryKeysA(hdb, "nosuchtable", &rec);
    ok(r == ERROR_INVALID_TABLE, "Expected ERROR_INVALID_TABLE, got %d\n", r);

    query = "SELECT * FROM `drone` WHERE `id` = 1";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewFetch(hview, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 0);
    ok(r != MSI_NULL_INTEGER && r != 0, "Expected non-NULL value, got %d\n", r);

    r = MsiRecordIsNull(rec, 0);
    ok(r == FALSE, "Expected FALSE, got %d\n", r);

    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");
    MsiCloseHandle(rec);
    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}