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
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseImportA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiRecordGetFieldCount (int /*<<< orphan*/ ) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiViewGetColumnInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int add_table_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_record (int /*<<< orphan*/ ,int,char*) ; 
 int do_query (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  endlines1 ; 
 int /*<<< orphan*/  endlines2 ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_data ; 
 int /*<<< orphan*/  two_primary ; 

__attribute__((used)) static void test_msiimport(void)
{
    MSIHANDLE hdb, view, rec;
    LPCSTR query;
    UINT r, count;
    signed int i;

    GetCurrentDirectoryA(MAX_PATH, CURR_DIR);

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiDatabaseImportA(hdb, CURR_DIR, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    r = MsiDatabaseImportA(hdb, CURR_DIR, "nonexistent");
    ok(r == ERROR_FUNCTION_FAILED, "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    r = add_table_to_db(hdb, test_data);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = add_table_to_db(hdb, two_primary);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = add_table_to_db(hdb, endlines1);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = add_table_to_db(hdb, endlines2);
    ok(r == ERROR_FUNCTION_FAILED, "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    query = "SELECT * FROM `TestTable`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 9, "Expected 9, got %d\n", count);
    ok(check_record(rec, 1, "FirstPrimaryColumn"), "Expected FirstPrimaryColumn\n");
    ok(check_record(rec, 2, "SecondPrimaryColumn"), "Expected SecondPrimaryColumn\n");
    ok(check_record(rec, 3, "ShortInt"), "Expected ShortInt\n");
    ok(check_record(rec, 4, "ShortIntNullable"), "Expected ShortIntNullalble\n");
    ok(check_record(rec, 5, "LongInt"), "Expected LongInt\n");
    ok(check_record(rec, 6, "LongIntNullable"), "Expected LongIntNullalble\n");
    ok(check_record(rec, 7, "String"), "Expected String\n");
    ok(check_record(rec, 8, "LocalizableString"), "Expected LocalizableString\n");
    ok(check_record(rec, 9, "LocalizableStringNullable"), "Expected LocalizableStringNullable\n");
    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 9, "Expected 9, got %d\n", count);
    ok(check_record(rec, 1, "s255"), "Expected s255\n");
    ok(check_record(rec, 2, "i2"), "Expected i2\n");
    ok(check_record(rec, 3, "i2"), "Expected i2\n");
    ok(check_record(rec, 4, "I2"), "Expected I2\n");
    ok(check_record(rec, 5, "i4"), "Expected i4\n");
    ok(check_record(rec, 6, "I4"), "Expected I4\n");
    ok(check_record(rec, 7, "S255"), "Expected S255\n");
    ok(check_record(rec, 8, "S0"), "Expected S0\n");
    ok(check_record(rec, 9, "s0"), "Expected s0\n");
    MsiCloseHandle(rec);

    query = "SELECT * FROM `TestTable`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(check_record(rec, 1, "stringage"), "Expected 'stringage'\n");
    ok(check_record(rec, 7, "another string"), "Expected 'another string'\n");
    ok(check_record(rec, 8, "localizable"), "Expected 'localizable'\n");
    ok(check_record(rec, 9, "duh"), "Expected 'duh'\n");

    i = MsiRecordGetInteger(rec, 2);
    ok(i == 5, "Expected 5, got %d\n", i);

    i = MsiRecordGetInteger(rec, 3);
    ok(i == 2, "Expected 2, got %d\n", i);

    i = MsiRecordGetInteger(rec, 4);
    ok(i == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", i);

    i = MsiRecordGetInteger(rec, 5);
    ok(i == 2147483640, "Expected 2147483640, got %d\n", i);

    i = MsiRecordGetInteger(rec, 6);
    ok(i == -2147483640, "Expected -2147483640, got %d\n", i);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "SELECT * FROM `TwoPrimary`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 2, "Expected 2, got %d\n", count);
    ok(check_record(rec, 1, "PrimaryOne"), "Expected PrimaryOne\n");
    ok(check_record(rec, 2, "PrimaryTwo"), "Expected PrimaryTwo\n");

    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 2, "Expected 2, got %d\n", count);
    ok(check_record(rec, 1, "s255"), "Expected s255\n");
    ok(check_record(rec, 2, "s255"), "Expected s255\n");
    MsiCloseHandle(rec);

    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    ok(check_record(rec, 1, "papaya"), "Expected 'papaya'\n");
    ok(check_record(rec, 2, "leaf"), "Expected 'leaf'\n");

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    ok(check_record(rec, 1, "papaya"), "Expected 'papaya'\n");
    ok(check_record(rec, 2, "flower"), "Expected 'flower'\n");

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    r = MsiViewClose(view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(view);

    query = "SELECT * FROM `Table`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 6, "Expected 6, got %d\n", count);
    ok(check_record(rec, 1, "A"), "Expected A\n");
    ok(check_record(rec, 2, "B"), "Expected B\n");
    ok(check_record(rec, 3, "C"), "Expected C\n");
    ok(check_record(rec, 4, "D"), "Expected D\n");
    ok(check_record(rec, 5, "E"), "Expected E\n");
    ok(check_record(rec, 6, "F"), "Expected F\n");
    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    count = MsiRecordGetFieldCount(rec);
    ok(count == 6, "Expected 6, got %d\n", count);
    ok(check_record(rec, 1, "s72"), "Expected s72\n");
    ok(check_record(rec, 2, "s72"), "Expected s72\n");
    ok(check_record(rec, 3, "s72"), "Expected s72\n");
    ok(check_record(rec, 4, "s72"), "Expected s72\n");
    ok(check_record(rec, 5, "s72"), "Expected s72\n");
    ok(check_record(rec, 6, "s72"), "Expected s72\n");
    MsiCloseHandle(rec);

    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "SELECT * FROM `Table`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(check_record(rec, 1, "a"), "Expected 'a'\n");
    ok(check_record(rec, 2, "b"), "Expected 'b'\n");
    ok(check_record(rec, 3, "c"), "Expected 'c'\n");
    ok(check_record(rec, 4, "d"), "Expected 'd'\n");
    ok(check_record(rec, 5, "e"), "Expected 'e'\n");
    ok(check_record(rec, 6, "f"), "Expected 'f'\n");

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(check_record(rec, 1, "g"), "Expected 'g'\n");
    ok(check_record(rec, 2, "h"), "Expected 'h'\n");
    ok(check_record(rec, 3, "i"), "Expected 'i'\n");
    ok(check_record(rec, 4, "j"), "Expected 'j'\n");
    ok(check_record(rec, 5, "k"), "Expected 'k'\n");
    ok(check_record(rec, 6, "l"), "Expected 'l'\n");

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);
    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}