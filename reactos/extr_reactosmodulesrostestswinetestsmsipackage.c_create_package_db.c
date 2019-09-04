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
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ set_summary_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSIHANDLE create_package_db(void)
{
    MSIHANDLE hdb = 0;
    UINT res;

    DeleteFileA(msifile);

    /* create an empty database */
    res = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb );
    ok( res == ERROR_SUCCESS , "Failed to create database %u\n", res );
    if( res != ERROR_SUCCESS )
        return hdb;

    res = MsiDatabaseCommit( hdb );
    ok( res == ERROR_SUCCESS , "Failed to commit database\n" );

    res = set_summary_info(hdb);
    ok( res == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", res);

    res = run_query( hdb,
            "CREATE TABLE `Directory` ( "
            "`Directory` CHAR(255) NOT NULL, "
            "`Directory_Parent` CHAR(255), "
            "`DefaultDir` CHAR(255) NOT NULL "
            "PRIMARY KEY `Directory`)" );
    ok( res == ERROR_SUCCESS , "Failed to create directory table\n" );

    return hdb;
}