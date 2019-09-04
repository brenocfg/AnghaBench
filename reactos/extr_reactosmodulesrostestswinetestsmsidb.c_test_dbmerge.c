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
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  DeleteFileW (char const*) ; 
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_DATATYPE_MISMATCH ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_TABLE ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 int MsiDatabaseImportA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int MsiDatabaseMergeA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiRecordGetStringA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int MsiRecordReadStream (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiRecordSetStreamA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiViewGetColumnInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_file (char*) ; 
 int /*<<< orphan*/  create_file_data (char*,char*,int /*<<< orphan*/ ) ; 
 int do_query (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 char* msifile ; 
 char const* msifileW ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_dbmerge(void)
{
    static const WCHAR refdbW[] = {'r','e','f','d','b','.','m','s','i',0};
    MSIHANDLE hdb, href, hview, hrec;
    CHAR buf[MAX_PATH];
    LPCSTR query;
    DWORD size;
    UINT r;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiOpenDatabaseW(refdbW, MSIDBOPEN_CREATE, &href);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* hDatabase is invalid */
    r = MsiDatabaseMergeA(0, href, "MergeErrors");
    ok(r == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", r);

    /* hDatabaseMerge is invalid */
    r = MsiDatabaseMergeA(hdb, 0, "MergeErrors");
    ok(r == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", r);

    /* szTableName is NULL */
    r = MsiDatabaseMergeA(hdb, href, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* szTableName is empty */
    r = MsiDatabaseMergeA(hdb, href, "");
    ok(r == ERROR_INVALID_TABLE, "Expected ERROR_INVALID_TABLE, got %d\n", r);

    /* both DBs empty, szTableName is valid */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` CHAR(72) PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* column types don't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_DATATYPE_MISMATCH,
       "Expected ERROR_DATATYPE_MISMATCH, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
        "`A` CHAR(72), "
        "`B` CHAR(56), "
        "`C` CHAR(64) LOCALIZABLE, "
        "`D` LONGCHAR, "
        "`E` CHAR(72) NOT NULL, "
        "`F` CHAR(56) NOT NULL, "
        "`G` CHAR(64) NOT NULL LOCALIZABLE, "
        "`H` LONGCHAR NOT NULL "
        "PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
        "`A` CHAR(64), "
        "`B` CHAR(64), "
        "`C` CHAR(64), "
        "`D` CHAR(64), "
        "`E` CHAR(64) NOT NULL, "
        "`F` CHAR(64) NOT NULL, "
        "`G` CHAR(64) NOT NULL, "
        "`H` CHAR(64) NOT NULL "
        "PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* column string types don't match exactly */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS,
       "Expected ERROR_SUCCESS, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `C` INT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* column names don't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_DATATYPE_MISMATCH,
       "Expected ERROR_DATATYPE_MISMATCH, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `B` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* primary keys don't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_DATATYPE_MISMATCH,
       "Expected ERROR_DATATYPE_MISMATCH, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A`, `B` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* number of primary keys doesn't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_DATATYPE_MISMATCH,
       "Expected ERROR_DATATYPE_MISMATCH, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT, `C` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 2 )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* number of columns doesn't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 3);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT, `C` INT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B`, `C` ) VALUES ( 1, 2, 3 )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* number of columns doesn't match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 3);
    ok(r == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", r);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 1 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 2, 2 )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` INT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 2 )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 2, 3 )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* primary keys match, rows do not */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_FUNCTION_FAILED,
       "Expected ERROR_FUNCTION_FAILED, got %d\n", r);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "One"), "Expected \"One\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    MsiCloseHandle(hrec);

    r = MsiDatabaseOpenViewA(hdb, "SELECT * FROM `MergeErrors`", &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(hview, MSICOLINFO_NAMES, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "Table"), "Expected \"Table\", got \"%s\"\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "NumRowMergeConflicts"),
       "Expected \"NumRowMergeConflicts\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewGetColumnInfo(hview, MSICOLINFO_TYPES, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "s255"), "Expected \"s255\", got \"%s\"\n", buf);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "i2"), "Expected \"i2\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);
    MsiViewClose(hview);
    MsiCloseHandle(hview);

    query = "DROP TABLE `MergeErrors`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` CHAR(72) PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 'hi' )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* table from merged database is not in target database */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "hi"), "Expected \"hi\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
            "`A` CHAR(72), `B` INT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
            "`A` CHAR(72), `B` INT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 'hi', 1 )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* primary key is string */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 1, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "hi"), "Expected \"hi\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(hrec, 2);
    ok(r == 1, "Expected 1, got %d\n", r);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    create_file_data("codepage.idt", "\r\n\r\n850\t_ForceCodepage\r\n", 0);

    GetCurrentDirectoryA(MAX_PATH, buf);
    r = MsiDatabaseImportA(hdb, buf, "codepage.idt");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
            "`A` INT, `B` CHAR(72) LOCALIZABLE PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( "
            "`A` INT, `B` CHAR(72) LOCALIZABLE PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 'hi' )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* code page does not match */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "hi"), "Expected \"hi\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` OBJECT PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` OBJECT PRIMARY KEY `A` )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    create_file("binary.dat");
    hrec = MsiCreateRecord(1);
    MsiRecordSetStreamA(hrec, 1, "binary.dat");

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, ? )";
    r = run_query(href, hrec, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(hrec);

    /* binary data to merge */
    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    ZeroMemory(buf, MAX_PATH);
    r = MsiRecordReadStream(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "binary.dat\n"),
       "Expected \"binary.dat\\n\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    /* nothing in MergeErrors */
    query = "SELECT * FROM `MergeErrors`";
    r = do_query(hdb, query, &hrec);
    ok(r == ERROR_BAD_QUERY_SYNTAX,
       "Expected ERROR_BAD_QUERY_SYNTAX, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "DROP TABLE `One`";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "CREATE TABLE `One` ( `A` INT, `B` CHAR(72) PRIMARY KEY `A` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 1, 'foo' )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "INSERT INTO `One` ( `A`, `B` ) VALUES ( 2, 'bar' )";
    r = run_query(href, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiDatabaseMergeA(hdb, href, "MergeErrors");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `One`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 1, "Expected 1, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "foo"), "Expected \"foo\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(hrec, 1);
    ok(r == 2, "Expected 2, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA(hrec, 2, buf, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "bar"), "Expected \"bar\", got \"%s\"\n", buf);

    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(hview);
    MsiCloseHandle(hview);

    MsiCloseHandle(hdb);
    MsiCloseHandle(href);
    DeleteFileA(msifile);
    DeleteFileW(refdbW);
    DeleteFileA("codepage.idt");
    DeleteFileA("binary.dat");
}