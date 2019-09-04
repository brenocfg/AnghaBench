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
typedef  scalar_t__ UINT ;
typedef  int MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 int check_record (int,int,char*) ; 
 int create_db () ; 
 int get_column_info (int,char*,int /*<<< orphan*/ ) ; 
 int get_columns_table_type (int,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ run_query (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_viewgetcolumninfo(void)
{
    MSIHANDLE hdb = 0, rec;
    UINT r;

    hdb = create_db();
    ok( hdb, "failed to create db\n");

    r = run_query( hdb, 0,
            "CREATE TABLE `Properties` "
            "( `Property` CHAR(255), "
            "  `Value` CHAR(1), "
            "  `Intvalue` INT, "
            "  `Integervalue` INTEGER, "
            "  `Shortvalue` SHORT, "
            "  `Longvalue` LONG, "
            "  `Longcharvalue` LONGCHAR, "
            "  `Charvalue` CHAR, "
            "  `Localizablevalue` CHAR LOCALIZABLE "
            "  PRIMARY KEY `Property`)" );
    ok( r == ERROR_SUCCESS , "Failed to create table\n" );

    /* check the column types */
    rec = get_column_info( hdb, "select * from `Properties`", MSICOLINFO_TYPES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "S255"), "wrong record type\n");
    ok( check_record( rec, 2, "S1"), "wrong record type\n");
    ok( check_record( rec, 3, "I2"), "wrong record type\n");
    ok( check_record( rec, 4, "I2"), "wrong record type\n");
    ok( check_record( rec, 5, "I2"), "wrong record type\n");
    ok( check_record( rec, 6, "I4"), "wrong record type\n");
    ok( check_record( rec, 7, "S0"), "wrong record type\n");
    ok( check_record( rec, 8, "S0"), "wrong record type\n");
    ok( check_record( rec, 9, "L0"), "wrong record type\n");

    MsiCloseHandle( rec );

    /* check the type in _Columns */
    ok( 0x3dff == get_columns_table_type(hdb, "Properties", 1 ), "_columns table wrong\n");
    ok( 0x1d01 == get_columns_table_type(hdb, "Properties", 2 ), "_columns table wrong\n");
    ok( 0x1502 == get_columns_table_type(hdb, "Properties", 3 ), "_columns table wrong\n");
    ok( 0x1502 == get_columns_table_type(hdb, "Properties", 4 ), "_columns table wrong\n");
    ok( 0x1502 == get_columns_table_type(hdb, "Properties", 5 ), "_columns table wrong\n");
    ok( 0x1104 == get_columns_table_type(hdb, "Properties", 6 ), "_columns table wrong\n");
    ok( 0x1d00 == get_columns_table_type(hdb, "Properties", 7 ), "_columns table wrong\n");
    ok( 0x1d00 == get_columns_table_type(hdb, "Properties", 8 ), "_columns table wrong\n");
    ok( 0x1f00 == get_columns_table_type(hdb, "Properties", 9 ), "_columns table wrong\n");

    /* now try the names */
    rec = get_column_info( hdb, "select * from `Properties`", MSICOLINFO_NAMES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "Property"), "wrong record type\n");
    ok( check_record( rec, 2, "Value"), "wrong record type\n");
    ok( check_record( rec, 3, "Intvalue"), "wrong record type\n");
    ok( check_record( rec, 4, "Integervalue"), "wrong record type\n");
    ok( check_record( rec, 5, "Shortvalue"), "wrong record type\n");
    ok( check_record( rec, 6, "Longvalue"), "wrong record type\n");
    ok( check_record( rec, 7, "Longcharvalue"), "wrong record type\n");
    ok( check_record( rec, 8, "Charvalue"), "wrong record type\n");
    ok( check_record( rec, 9, "Localizablevalue"), "wrong record type\n");

    MsiCloseHandle( rec );

    r = run_query( hdb, 0,
            "CREATE TABLE `Binary` "
            "( `Name` CHAR(255), `Data` OBJECT  PRIMARY KEY `Name`)" );
    ok( r == ERROR_SUCCESS , "Failed to create table\n" );

    /* check the column types */
    rec = get_column_info( hdb, "select * from `Binary`", MSICOLINFO_TYPES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "S255"), "wrong record type\n");
    ok( check_record( rec, 2, "V0"), "wrong record type\n");

    MsiCloseHandle( rec );

    /* check the type in _Columns */
    ok( 0x3dff == get_columns_table_type(hdb, "Binary", 1 ), "_columns table wrong\n");
    ok( 0x1900 == get_columns_table_type(hdb, "Binary", 2 ), "_columns table wrong\n");

    /* now try the names */
    rec = get_column_info( hdb, "select * from `Binary`", MSICOLINFO_NAMES );
    ok( rec, "failed to get column info record\n" );

    ok( check_record( rec, 1, "Name"), "wrong record type\n");
    ok( check_record( rec, 2, "Data"), "wrong record type\n");
    MsiCloseHandle( rec );

    r = run_query( hdb, 0,
            "CREATE TABLE `UIText` "
            "( `Key` CHAR(72) NOT NULL, `Text` CHAR(255) LOCALIZABLE PRIMARY KEY `Key`)" );
    ok( r == ERROR_SUCCESS , "Failed to create table\n" );

    ok( 0x2d48 == get_columns_table_type(hdb, "UIText", 1 ), "_columns table wrong\n");
    ok( 0x1fff == get_columns_table_type(hdb, "UIText", 2 ), "_columns table wrong\n");

    rec = get_column_info( hdb, "select * from `UIText`", MSICOLINFO_NAMES );
    ok( rec, "failed to get column info record\n" );
    ok( check_record( rec, 1, "Key"), "wrong record type\n");
    ok( check_record( rec, 2, "Text"), "wrong record type\n");
    MsiCloseHandle( rec );

    rec = get_column_info( hdb, "select * from `UIText`", MSICOLINFO_TYPES );
    ok( rec, "failed to get column info record\n" );
    ok( check_record( rec, 1, "s72"), "wrong record type\n");
    ok( check_record( rec, 2, "L255"), "wrong record type\n");
    MsiCloseHandle( rec );

    MsiCloseHandle( hdb );
}