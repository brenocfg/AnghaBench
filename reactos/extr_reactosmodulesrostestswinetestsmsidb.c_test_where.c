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
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiDatabaseOpenViewA (scalar_t__,char*,scalar_t__*) ; 
 int MsiRecordGetFieldCount (scalar_t__) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordGetStringA (scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  MsiViewClose (scalar_t__) ; 
 int MsiViewExecute (scalar_t__,scalar_t__) ; 
 int MsiViewFetch (scalar_t__,scalar_t__*) ; 
 int S_OK ; 
 int /*<<< orphan*/  check_record (scalar_t__,int,char*) ; 
 scalar_t__ create_db () ; 
 int do_query (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (scalar_t__,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_where(void)
{
    MSIHANDLE hdb = 0, rec, view;
    LPCSTR query;
    UINT r;
    DWORD size;
    CHAR buf[MAX_PATH];
    UINT count;

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    r = run_query( hdb, 0,
            "CREATE TABLE `Media` ("
            "`DiskId` SHORT NOT NULL, "
            "`LastSequence` LONG, "
            "`DiskPrompt` CHAR(64) LOCALIZABLE, "
            "`Cabinet` CHAR(255), "
            "`VolumeLabel` CHAR(32), "
            "`Source` CHAR(72) "
            "PRIMARY KEY `DiskId`)" );
    ok( r == S_OK, "cannot create Media table: %d\n", r );

    r = run_query( hdb, 0, "INSERT INTO `Media` "
            "( `DiskId`, `LastSequence`, `DiskPrompt`, `Cabinet`, `VolumeLabel`, `Source` ) "
            "VALUES ( 1, 0, '', 'zero.cab', '', '' )" );
    ok( r == S_OK, "cannot add file to the Media table: %d\n", r );

    r = run_query( hdb, 0, "INSERT INTO `Media` "
            "( `DiskId`, `LastSequence`, `DiskPrompt`, `Cabinet`, `VolumeLabel`, `Source` ) "
            "VALUES ( 2, 1, '', 'one.cab', '', '' )" );
    ok( r == S_OK, "cannot add file to the Media table: %d\n", r );

    r = run_query( hdb, 0, "INSERT INTO `Media` "
            "( `DiskId`, `LastSequence`, `DiskPrompt`, `Cabinet`, `VolumeLabel`, `Source` ) "
            "VALUES ( 3, 2, '', 'two.cab', '', '' )" );
    ok( r == S_OK, "cannot add file to the Media table: %d\n", r );

    query = "SELECT * FROM `Media`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed: %d\n", r);
    ok( check_record( rec, 4, "zero.cab"), "wrong cabinet\n");
    MsiCloseHandle( rec );

    query = "SELECT * FROM `Media` WHERE `LastSequence` >= 1";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed: %d\n", r);
    ok( check_record( rec, 4, "one.cab"), "wrong cabinet\n");

    r = MsiRecordGetInteger(rec, 1);
    ok( 2 == r, "field wrong\n");
    r = MsiRecordGetInteger(rec, 2);
    ok( 1 == r, "field wrong\n");
    MsiCloseHandle( rec );

    query = "SELECT `DiskId` FROM `Media` WHERE `LastSequence` >= 1 AND DiskId >= 0";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok( r == ERROR_SUCCESS, "failed to open view: %d\n", r );

    r = MsiViewExecute(view, 0);
    ok( r == ERROR_SUCCESS, "failed to execute view: %d\n", r );

    r = MsiViewFetch(view, &rec);
    ok( r == ERROR_SUCCESS, "failed to fetch view: %d\n", r );

    count = MsiRecordGetFieldCount( rec );
    ok( count == 1, "Expected 1 record fields, got %d\n", count );

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, buf, &size );
    ok( r == ERROR_SUCCESS, "failed to get record string: %d\n", r );
    ok( !lstrcmpA( buf, "2" ), "For (row %d, column 1) expected '%d', got %s\n", 0, 2, buf );
    MsiCloseHandle( rec );

    r = MsiViewFetch(view, &rec);
    ok( r == ERROR_SUCCESS, "failed to fetch view: %d\n", r );

    size = MAX_PATH;
    r = MsiRecordGetStringA( rec, 1, buf, &size );
    ok( r == ERROR_SUCCESS, "failed to get record string: %d\n", r );
    ok( !lstrcmpA( buf, "3" ), "For (row %d, column 1) expected '%d', got %s\n", 1, 3, buf );
    MsiCloseHandle( rec );

    r = MsiViewFetch(view, &rec);
    ok( r == ERROR_NO_MORE_ITEMS, "expected no more items: %d\n", r );

    MsiViewClose(view);
    MsiCloseHandle(view);

    MsiCloseHandle( rec );

    rec = 0;
    query = "SELECT * FROM `Media` WHERE `DiskPrompt` IS NULL";
    r = do_query(hdb, query, &rec);
    ok( r == ERROR_SUCCESS, "query failed: %d\n", r );
    MsiCloseHandle( rec );

    rec = 0;
    query = "SELECT * FROM `Media` WHERE `DiskPrompt` < 'Cabinet'";
    r = do_query(hdb, query, &rec);
    ok( r == ERROR_BAD_QUERY_SYNTAX, "query failed: %d\n", r );
    MsiCloseHandle( rec );

    rec = 0;
    query = "SELECT * FROM `Media` WHERE `DiskPrompt` > 'Cabinet'";
    r = do_query(hdb, query, &rec);
    ok( r == ERROR_BAD_QUERY_SYNTAX, "query failed: %d\n", r );
    MsiCloseHandle( rec );

    rec = 0;
    query = "SELECT * FROM `Media` WHERE `DiskPrompt` <> 'Cabinet'";
    r = do_query(hdb, query, &rec);
    ok( r == ERROR_SUCCESS, "query failed: %d\n", r );
    MsiCloseHandle( rec );

    rec = 0;
    query = "SELECT * FROM `Media` WHERE `DiskPrompt` = 'Cabinet'";
    r = do_query(hdb, query, &rec);
    ok( r == ERROR_NO_MORE_ITEMS, "query failed: %d\n", r );
    MsiCloseHandle( rec );

    rec = MsiCreateRecord(1);
    MsiRecordSetStringA(rec, 1, "");

    query = "SELECT * FROM `Media` WHERE `DiskPrompt` = ?";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    MsiCloseHandle( hdb );
    DeleteFileA(msifile);
}