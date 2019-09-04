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
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,char const*,char const*) ; 

__attribute__((used)) static UINT find_entry( MSIHANDLE hdb, const char *table, const char *entry )
{
    static const char fmt[] = "SELECT * FROM `%s` WHERE `Name` = '%s'";
    char query[0x100];
    UINT r;
    MSIHANDLE hview, hrec;

    sprintf( query, fmt, table, entry );
    r = MsiDatabaseOpenViewA( hdb, query, &hview );
    ok( r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r );

    r = MsiViewExecute( hview, 0 );
    ok( r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r );

    r = MsiViewFetch( hview, &hrec );
    MsiViewClose( hview );
    MsiCloseHandle( hview );
    MsiCloseHandle( hrec );
    return r;
}