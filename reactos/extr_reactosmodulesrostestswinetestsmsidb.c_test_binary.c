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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ MSIHANDLE ;
typedef  char* LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MSIDBOPEN_READONLY ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int /*<<< orphan*/  MsiDatabaseCommit (scalar_t__) ; 
 int /*<<< orphan*/  MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  MsiRecordGetStringA (scalar_t__,int,char*,int*) ; 
 int /*<<< orphan*/  MsiRecordReadStream (scalar_t__,int,char*,int*) ; 
 int /*<<< orphan*/  MsiRecordSetStreamA (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  create_file (char*) ; 
 int /*<<< orphan*/  do_query (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_query (scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static void test_binary(void)
{
    MSIHANDLE hdb = 0, rec;
    char file[MAX_PATH];
    char buf[MAX_PATH];
    DWORD size;
    LPCSTR query;
    UINT r;

    /* insert a file into the Binary table */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( r == ERROR_SUCCESS , "Failed to open database\n" );

    query = "CREATE TABLE `Binary` ( `Name` CHAR(72) NOT NULL, `ID` INT NOT NULL, `Data` OBJECT  PRIMARY KEY `Name`, `ID`)";
    r = run_query( hdb, 0, query );
    ok( r == ERROR_SUCCESS, "Cannot create Binary table: %d\n", r );

    create_file( "test.txt" );
    rec = MsiCreateRecord( 1 );
    r = MsiRecordSetStreamA( rec, 1, "test.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r);
    DeleteFileA( "test.txt" );

    /* try a name that exceeds maximum OLE stream name length */
    query = "INSERT INTO `Binary` ( `Name`, `ID`, `Data` ) VALUES ( 'encryption.dll.CB4E6205_F99A_4C51_ADD4_184506EFAB87', 10000, ? )";
    r = run_query( hdb, rec, query );
    ok( r == ERROR_SUCCESS, "Insert into Binary table failed: %d\n", r );

    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS , "Failed to close record handle\n" );

    r = MsiDatabaseCommit( hdb );
    ok( r == ERROR_FUNCTION_FAILED , "got %u\n", r );

    r = MsiCloseHandle( hdb );
    ok( r == ERROR_SUCCESS , "Failed to close database\n" );

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( r == ERROR_SUCCESS , "Failed to open database\n" );

    query = "CREATE TABLE `Binary` ( `Name` CHAR(72) NOT NULL, `ID` INT NOT NULL, `Data` OBJECT  PRIMARY KEY `Name`, `ID`)";
    r = run_query( hdb, 0, query );
    ok( r == ERROR_SUCCESS, "Cannot create Binary table: %d\n", r );

    create_file( "test.txt" );
    rec = MsiCreateRecord( 1 );
    r = MsiRecordSetStreamA( rec, 1, "test.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r );
    DeleteFileA( "test.txt" );

    query = "INSERT INTO `Binary` ( `Name`, `ID`, `Data` ) VALUES ( 'filename1', 1, ? )";
    r = run_query( hdb, rec, query );
    ok( r == ERROR_SUCCESS, "Insert into Binary table failed: %d\n", r );

    query = "INSERT INTO `Binary` ( `Name`, `ID`, `Data` ) VALUES ( 'filename1', 1, ? )";
    r = run_query( hdb, rec, query );
    ok( r == ERROR_FUNCTION_FAILED, "got %u\n", r );

    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS , "Failed to close record handle\n" );

    r = MsiDatabaseCommit( hdb );
    ok( r == ERROR_SUCCESS , "Failed to commit database\n" );

    r = MsiCloseHandle( hdb );
    ok( r == ERROR_SUCCESS , "Failed to close database\n" );

    /* read file from the Stream table */
    r = MsiOpenDatabaseW( msifileW, MSIDBOPEN_READONLY, &hdb );
    ok( r == ERROR_SUCCESS , "Failed to open database\n" );

    query = "SELECT * FROM `_Streams`";
    r = do_query( hdb, query, &rec );
    ok( r == ERROR_SUCCESS, "SELECT query failed: %d\n", r );

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, file, &size );
    ok( r == ERROR_SUCCESS, "Failed to get string: %d\n", r );
    ok( !lstrcmpA(file, "Binary.filename1.1"), "Expected 'Binary.filename1.1', got %s\n", file );

    size = MAX_PATH;
    memset( buf, 0, MAX_PATH );
    r = MsiRecordReadStream( rec, 2, buf, &size );
    ok( r == ERROR_SUCCESS, "Failed to get stream: %d\n", r );
    ok( !lstrcmpA(buf, "test.txt\n"), "Expected 'test.txt\\n', got %s\n", buf );

    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS , "Failed to close record handle\n" );

    /* read file from the Binary table */
    query = "SELECT * FROM `Binary`";
    r = do_query( hdb, query, &rec );
    ok( r == ERROR_SUCCESS, "SELECT query failed: %d\n", r );

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, file, &size );
    ok( r == ERROR_SUCCESS, "Failed to get string: %d\n", r );
    ok( !lstrcmpA(file, "filename1"), "Expected 'filename1', got %s\n", file );

    size = MAX_PATH;
    memset( buf, 0, MAX_PATH );
    r = MsiRecordReadStream( rec, 3, buf, &size );
    ok( r == ERROR_SUCCESS, "Failed to get stream: %d\n", r );
    ok( !lstrcmpA(buf, "test.txt\n"), "Expected 'test.txt\\n', got %s\n", buf );

    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS , "Failed to close record handle\n" );

    r = MsiCloseHandle( hdb );
    ok( r == ERROR_SUCCESS , "Failed to close database\n" );

    DeleteFileA( msifile );
}