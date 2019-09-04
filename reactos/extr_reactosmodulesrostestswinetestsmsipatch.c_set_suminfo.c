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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_DIRECT ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSummaryInfoPersist (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiSummaryInfoSetPropertyA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  VT_LPSTR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void set_suminfo( const WCHAR *filename )
{
    UINT r;
    MSIHANDLE hsi, hdb;

    r = MsiOpenDatabaseW( filename, MSIDBOPEN_DIRECT, &hdb );
    ok( r == ERROR_SUCCESS, "failed to open database %u\n", r );

    r = MsiGetSummaryInformationA( hdb, NULL, 7, &hsi );
    ok( r == ERROR_SUCCESS, "failed to open summaryinfo %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 2, VT_LPSTR, 0, NULL, "Installation Database" );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 3, VT_LPSTR, 0, NULL, "Installation Database" );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 4, VT_LPSTR, 0, NULL, "WineHQ" );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 7, VT_LPSTR, 0, NULL, ";1033" );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 9, VT_LPSTR, 0, NULL, "{E528DDD6-4801-4BEC-BBB6-C5EE0FD097E9}" );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 14, VT_I4, 100, NULL, NULL );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoSetPropertyA( hsi, 15, VT_I4, 0, NULL, NULL );
    ok( r == ERROR_SUCCESS, "failed to set summary info %u\n", r );

    r = MsiSummaryInfoPersist( hsi );
    ok( r == ERROR_SUCCESS, "failed to persist suminfo %u\n", r );

    r = MsiCloseHandle( hsi );
    ok( r == ERROR_SUCCESS, "failed to close suminfo %u\n", r );

    r = MsiCloseHandle( hdb );
    ok( r == ERROR_SUCCESS, "failed to close database %u\n", r );
}