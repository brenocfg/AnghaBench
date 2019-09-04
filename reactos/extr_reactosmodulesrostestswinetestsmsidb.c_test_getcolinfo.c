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
typedef  scalar_t__ MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int MSICOLINFO_NAMES ; 
 int MSICOLINFO_TYPES ; 
 scalar_t__ MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiDatabaseOpenViewA (scalar_t__,char*,scalar_t__*) ; 
 scalar_t__ MsiRecordGetStringA (scalar_t__,int,char*,int*) ; 
 scalar_t__ MsiViewClose (scalar_t__) ; 
 scalar_t__ MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewGetColumnInfo (scalar_t__,int,scalar_t__*) ; 
 scalar_t__ create_db () ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_getcolinfo(void)
{
    MSIHANDLE hdb, hview = 0, rec = 0;
    UINT r;
    DWORD sz;
    char buffer[0x20];

    /* create an empty db */
    hdb = create_db();
    ok( hdb, "failed to create db\n");

    /* tables should be present */
    r = MsiDatabaseOpenViewA(hdb, "select * from _Tables", &hview);
    ok( r == ERROR_SUCCESS, "failed to open query\n");

    r = MsiViewExecute(hview, 0);
    ok( r == ERROR_SUCCESS, "failed to execute query\n");

    /* check that NAMES works */
    rec = 0;
    r = MsiViewGetColumnInfo( hview, MSICOLINFO_NAMES, &rec );
    ok( r == ERROR_SUCCESS, "failed to get names\n");
    sz = sizeof buffer;
    r = MsiRecordGetStringA(rec, 1, buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get string\n");
    ok( !strcmp(buffer,"Name"), "_Tables has wrong column name\n");
    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS, "failed to close record handle\n");

    /* check that TYPES works */
    rec = 0;
    r = MsiViewGetColumnInfo( hview, MSICOLINFO_TYPES, &rec );
    ok( r == ERROR_SUCCESS, "failed to get names\n");
    sz = sizeof buffer;
    r = MsiRecordGetStringA(rec, 1, buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get string\n");
    ok( !strcmp(buffer,"s64"), "_Tables has wrong column type\n");
    r = MsiCloseHandle( rec );
    ok( r == ERROR_SUCCESS, "failed to close record handle\n");

    /* check that invalid values fail */
    rec = 0;
    r = MsiViewGetColumnInfo( hview, 100, &rec );
    ok( r == ERROR_INVALID_PARAMETER, "wrong error code\n");
    ok( rec == 0, "returned a record\n");

    r = MsiViewGetColumnInfo( hview, MSICOLINFO_TYPES, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong error code\n");

    r = MsiViewGetColumnInfo( 0, MSICOLINFO_TYPES, &rec );
    ok( r == ERROR_INVALID_HANDLE, "wrong error code\n");

    r = MsiViewClose(hview);
    ok( r == ERROR_SUCCESS, "failed to close view\n");
    r = MsiCloseHandle(hview);
    ok( r == ERROR_SUCCESS, "failed to close view handle\n");
    r = MsiCloseHandle(hdb);
    ok( r == ERROR_SUCCESS, "failed to close database\n");
}