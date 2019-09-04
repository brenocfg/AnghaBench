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
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 scalar_t__ DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_OPEN_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributesA (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MSIDBOPEN_DIRECT ; 
 int /*<<< orphan*/  MSIDBOPEN_READONLY ; 
 int /*<<< orphan*/  MSIDBOPEN_TRANSACT ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifile2 ; 
 int /*<<< orphan*/  msifile2W ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_msidatabase(void)
{
    MSIHANDLE hdb = 0, hdb2 = 0;
    UINT res;

    DeleteFileW(msifileW);

    res = MsiOpenDatabaseW( msifileW, msifile2W, &hdb );
    ok( res == ERROR_OPEN_FAILED, "expected failure\n");

    res = MsiOpenDatabaseW( msifileW, (LPWSTR)0xff, &hdb );
    ok( res == ERROR_INVALID_PARAMETER, "expected failure\n");

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    /* create an empty database */
    res = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to create database\n" );

    res = MsiDatabaseCommit( hdb );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    ok( GetFileAttributesA( msifile ) != INVALID_FILE_ATTRIBUTES, "database should exist\n");

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );
    res = MsiOpenDatabaseW( msifileW, msifile2W, &hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    ok( GetFileAttributesA( msifile2 ) != INVALID_FILE_ATTRIBUTES, "database should exist\n");

    res = MsiDatabaseCommit( hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    res = MsiCloseHandle( hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    res = MsiOpenDatabaseW( msifileW, msifile2W, &hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    res = MsiCloseHandle( hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    ok( GetFileAttributesA( msifile2 ) == INVALID_FILE_ATTRIBUTES, "uncommitted database should not exist\n");

    res = MsiOpenDatabaseW( msifileW, msifile2W, &hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    res = MsiDatabaseCommit( hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    res = MsiCloseHandle( hdb2 );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    ok( GetFileAttributesA( msifile2 ) != INVALID_FILE_ATTRIBUTES, "committed database should exist\n");

    res = MsiOpenDatabaseW( msifileW, MSIDBOPEN_READONLY, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    res = MsiDatabaseCommit( hdb );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    res = MsiOpenDatabaseW( msifileW, MSIDBOPEN_DIRECT, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    res = MsiOpenDatabaseW( msifileW, MSIDBOPEN_TRANSACT, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );
    ok( GetFileAttributesA( msifile ) != INVALID_FILE_ATTRIBUTES, "database should exist\n");

    /* MSIDBOPEN_CREATE deletes the database if MsiCommitDatabase isn't called */
    res = MsiOpenDatabaseW( msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    ok( GetFileAttributesA( msifile ) != INVALID_FILE_ATTRIBUTES, "database should exist\n");

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    ok( GetFileAttributesA( msifile ) == INVALID_FILE_ATTRIBUTES, "database should exist\n");

    res = MsiOpenDatabaseW( msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to open database\n" );

    res = MsiDatabaseCommit( hdb );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    ok( GetFileAttributesA( msifile ) != INVALID_FILE_ATTRIBUTES, "database should exist\n");

    res = MsiCloseHandle( hdb );
    ok( res == ERROR_SUCCESS , "Failed to close database\n" );

    res = DeleteFileA( msifile2 );
    ok( res == TRUE, "Failed to delete database\n" );

    res = DeleteFileA( msifile );
    ok( res == TRUE, "Failed to delete database\n" );
}