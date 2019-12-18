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
typedef  char* LPSTR ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_summary_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static MSIHANDLE create_package_db(LPSTR prodcode)
{
    MSIHANDLE hdb = 0;
    CHAR query[MAX_PATH];
    UINT res;

    DeleteFileA(msifile);

    /* create an empty database */
    res = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok( res == ERROR_SUCCESS , "Failed to create database\n" );
    if (res != ERROR_SUCCESS)
        return hdb;

    res = MsiDatabaseCommit(hdb);
    ok(res == ERROR_SUCCESS, "Failed to commit database\n");

    set_summary_info(hdb, prodcode);

    res = run_query(hdb,
            "CREATE TABLE `Directory` ( "
            "`Directory` CHAR(255) NOT NULL, "
            "`Directory_Parent` CHAR(255), "
            "`DefaultDir` CHAR(255) NOT NULL "
            "PRIMARY KEY `Directory`)");
    ok(res == ERROR_SUCCESS , "Failed to create directory table\n");

    res = run_query(hdb,
            "CREATE TABLE `Property` ( "
            "`Property` CHAR(72) NOT NULL, "
            "`Value` CHAR(255) "
            "PRIMARY KEY `Property`)");
    ok(res == ERROR_SUCCESS , "Failed to create directory table\n");

    sprintf(query, "INSERT INTO `Property` "
            "(`Property`, `Value`) "
            "VALUES( 'ProductCode', '%s' )", prodcode);
    res = run_query(hdb, query);
    ok(res == ERROR_SUCCESS , "Failed\n");

    res = MsiDatabaseCommit(hdb);
    ok(res == ERROR_SUCCESS, "Failed to commit database\n");

    return hdb;
}