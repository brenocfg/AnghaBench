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

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSTALL_FAILURE ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSetPropertyA (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  add_launchcondition_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_launchcondition_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_launchconditions(void)
{
    MSIHANDLE hpkg;
    MSIHANDLE hdb;
    UINT r;

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    hdb = create_package_db();
    ok( hdb, "failed to create package database\n" );

    create_launchcondition_table( hdb );

    add_launchcondition_entry( hdb, "'X = \"1\"', 'one'" );

    /* invalid condition */
    add_launchcondition_entry( hdb, "'X != \"1\"', 'one'" );

    r = package_from_db( hdb, &hpkg );
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r );

    MsiCloseHandle( hdb );

    r = MsiSetPropertyA( hpkg, "X", "1" );
    ok( r == ERROR_SUCCESS, "failed to set property\n" );

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    /* invalid conditions are ignored */
    r = MsiDoActionA( hpkg, "LaunchConditions" );
    ok( r == ERROR_SUCCESS, "cost init failed\n" );

    /* verify LaunchConditions still does some verification */
    r = MsiSetPropertyA( hpkg, "X", "2" );
    ok( r == ERROR_SUCCESS, "failed to set property\n" );

    r = MsiDoActionA( hpkg, "LaunchConditions" );
    ok( r == ERROR_INSTALL_FAILURE, "Expected ERROR_INSTALL_FAILURE, got %d\n", r );

    MsiCloseHandle( hpkg );
    DeleteFileA( msifile );
}