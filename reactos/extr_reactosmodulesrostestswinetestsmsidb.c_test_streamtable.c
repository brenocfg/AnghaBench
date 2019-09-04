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
typedef  char* UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 char* ERROR_FUNCTION_FAILED ; 
 char* ERROR_NO_MORE_ITEMS ; 
 char* ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MSIDBOPEN_TRANSACT ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 char* MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 char* MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* MsiRecordGetStringA (int /*<<< orphan*/ ,int,char*,int*) ; 
 char* MsiRecordReadStream (int /*<<< orphan*/ ,int,char*,int*) ; 
 char* MsiRecordSetStreamA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (int /*<<< orphan*/ ,int,char*) ; 
 char* MsiSummaryInfoPersist (int /*<<< orphan*/ ) ; 
 char* MsiSummaryInfoSetPropertyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 char* MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PID_SECURITY ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  check_record (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  create_db () ; 
 int /*<<< orphan*/  create_file (char*) ; 
 int /*<<< orphan*/  get_column_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_streamtable(void)
{
    MSIHANDLE hdb = 0, rec, view, hsi;
    char file[MAX_PATH];
    char buf[MAX_PATH];
    DWORD size;
    UINT r;

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    r = run_query( hdb, 0,
            "CREATE TABLE `Properties` "
            "( `Property` CHAR(255), `Value` CHAR(1)  PRIMARY KEY `Property`)" );
    ok( r == ERROR_SUCCESS , "Failed to create table\n" );

    r = run_query( hdb, 0,
            "INSERT INTO `Properties` "
            "( `Value`, `Property` ) VALUES ( 'Prop', 'value' )" );
    ok( r == ERROR_SUCCESS, "Failed to add to table\n" );

    r = MsiDatabaseCommit( hdb );
    ok( r == ERROR_SUCCESS , "Failed to commit database\n" );

    MsiCloseHandle( hdb );

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_TRANSACT, &hdb );
    ok( r == ERROR_SUCCESS , "Failed to open database\n" );

    /* check the column types */
    rec = get_column_info( hdb, "select * from `_Streams`", MSICOLINFO_TYPES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "s62"), "wrong record type\n");
    ok( check_record( rec, 2, "V0"), "wrong record type\n");

    MsiCloseHandle( rec );

    /* now try the names */
    rec = get_column_info( hdb, "select * from `_Streams`", MSICOLINFO_NAMES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "Name"), "wrong record type\n");
    ok( check_record( rec, 2, "Data"), "wrong record type\n");

    MsiCloseHandle( rec );

    r = MsiDatabaseOpenViewA( hdb,
            "SELECT * FROM `_Streams` WHERE `Name` = '\5SummaryInformation'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %u\n", r );

    r = MsiViewExecute( view, 0 );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %u\n", r );

    r = MsiViewFetch( view, &rec );
    ok( r == ERROR_NO_MORE_ITEMS, "Unexpected result: %u\n", r );

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* create a summary information stream */
    r = MsiGetSummaryInformationA( hdb, NULL, 1, &hsi );
    ok( r == ERROR_SUCCESS, "Failed to get summary information handle: %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, PID_SECURITY, VT_I4, 2, NULL, NULL );
    ok( r == ERROR_SUCCESS, "Failed to set property: %u\n", r );

    r = MsiSummaryInfoPersist( hsi );
    ok( r == ERROR_SUCCESS, "Failed to save summary information: %u\n", r );

    MsiCloseHandle( hsi );

    r = MsiDatabaseOpenViewA( hdb,
            "SELECT * FROM `_Streams` WHERE `Name` = '\5SummaryInformation'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %u\n", r );

    r = MsiViewExecute( view, 0 );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %u\n", r );

    r = MsiViewFetch( view, &rec );
    ok( r == ERROR_SUCCESS, "Unexpected result: %u\n", r );

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* insert a file into the _Streams table */
    create_file( "test.txt" );

    rec = MsiCreateRecord( 2 );
    MsiRecordSetStringA( rec, 1, "data" );

    r = MsiRecordSetStreamA( rec, 2, "test.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r);

    DeleteFileA("test.txt");

    r = MsiDatabaseOpenViewA( hdb,
            "INSERT INTO `_Streams` ( `Name`, `Data` ) VALUES ( ?, ? )", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, rec );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* insert another one */
    create_file( "test1.txt" );

    rec = MsiCreateRecord( 2 );
    MsiRecordSetStringA( rec, 1, "data1" );

    r = MsiRecordSetStreamA( rec, 2, "test1.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r);

    DeleteFileA("test1.txt");

    r = MsiDatabaseOpenViewA( hdb,
            "INSERT INTO `_Streams` ( `Name`, `Data` ) VALUES ( ?, ? )", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, rec );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* try again */
    create_file( "test1.txt" );

    rec = MsiCreateRecord( 2 );
    MsiRecordSetStringA( rec, 1, "data1" );

    r = MsiRecordSetStreamA( rec, 2, "test1.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r );

    DeleteFileA( "test1.txt" );

    r = MsiDatabaseOpenViewA( hdb,
            "INSERT INTO `_Streams` ( `Name`, `Data` ) VALUES ( ?, ? )", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r );

    r = MsiViewExecute( view, rec );
    ok( r == ERROR_FUNCTION_FAILED, "got %u\n", r );

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    r = MsiDatabaseOpenViewA( hdb,
            "SELECT `Name`, `Data` FROM `_Streams` WHERE `Name` = 'data'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, 0 );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    r = MsiViewFetch( view, &rec );
    ok( r == ERROR_SUCCESS, "Failed to fetch record: %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, file, &size );
    ok( r == ERROR_SUCCESS, "Failed to get string: %d\n", r);
    ok( !lstrcmpA(file, "data"), "Expected 'data', got %s\n", file);

    size = MAX_PATH;
    memset(buf, 0, MAX_PATH);
    r = MsiRecordReadStream( rec, 2, buf, &size );
    ok( r == ERROR_SUCCESS, "Failed to get stream: %d\n", r);
    ok( !lstrcmpA(buf, "test.txt\n"), "Expected 'test.txt\\n', got %s\n", buf);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    r = MsiDatabaseOpenViewA( hdb,
            "SELECT `Name`, `Data` FROM `_Streams` WHERE `Name` = 'data1'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, 0 );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    r = MsiViewFetch( view, &rec );
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, file, &size );
    ok( r == ERROR_SUCCESS, "Failed to get string: %d\n", r);
    ok( !lstrcmpA(file, "data1"), "Expected 'data1', got %s\n", file);

    size = MAX_PATH;
    memset(buf, 0, MAX_PATH);
    r = MsiRecordReadStream( rec, 2, buf, &size );
    ok( r == ERROR_SUCCESS, "Failed to get stream: %d\n", r);
    ok( !lstrcmpA(buf, "test1.txt\n"), "Expected 'test1.txt\\n', got %s\n", buf);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    /* perform an update */
    create_file( "test2.txt" );
    rec = MsiCreateRecord( 1 );

    r = MsiRecordSetStreamA( rec, 1, "test2.txt" );
    ok( r == ERROR_SUCCESS, "Failed to add stream data to the record: %d\n", r);

    DeleteFileA("test2.txt");

    r = MsiDatabaseOpenViewA( hdb,
            "UPDATE `_Streams` SET `Data` = ? WHERE `Name` = 'data1'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, rec );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );

    r = MsiDatabaseOpenViewA( hdb,
            "SELECT `Name`, `Data` FROM `_Streams` WHERE `Name` = 'data1'", &view );
    ok( r == ERROR_SUCCESS, "Failed to open database view: %d\n", r);

    r = MsiViewExecute( view, 0 );
    ok( r == ERROR_SUCCESS, "Failed to execute view: %d\n", r);

    r = MsiViewFetch( view, &rec );
    ok( r == ERROR_SUCCESS, "Failed to fetch record: %d\n", r);

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, file, &size );
    ok( r == ERROR_SUCCESS, "Failed to get string: %d\n", r);
    ok( !lstrcmpA(file, "data1"), "Expected 'data1', got %s\n", file);

    size = MAX_PATH;
    memset(buf, 0, MAX_PATH);
    r = MsiRecordReadStream( rec, 2, buf, &size );
    ok( r == ERROR_SUCCESS, "Failed to get stream: %d\n", r);
    ok( !lstrcmpA(buf, "test2.txt\n"), "Expected 'test2.txt\\n', got %s\n", buf);

    MsiCloseHandle( rec );
    MsiViewClose( view );
    MsiCloseHandle( view );
    MsiCloseHandle( hdb );
    DeleteFileA(msifile);
}