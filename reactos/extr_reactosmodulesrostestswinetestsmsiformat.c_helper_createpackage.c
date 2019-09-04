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
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATEDIRECT ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSummaryInfoPersist (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiSummaryInfoSetPropertyA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  VT_LPSTR ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT helper_createpackage( const char *szName, MSIHANDLE *handle )
{
    MSIHANDLE hPackage, suminfo, hdb = 0;
    UINT res;
    WCHAR *nameW;
    int len;

    DeleteFileA(szName);

    len = MultiByteToWideChar( CP_ACP, 0, szName, -1, NULL, 0 );
    if (!(nameW = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) )))
        return ERROR_OUTOFMEMORY;
    MultiByteToWideChar( CP_ACP, 0, szName, -1, nameW, len );

    /* create an empty database */
    res = MsiOpenDatabaseW( nameW, MSIDBOPEN_CREATEDIRECT, &hdb );
    HeapFree( GetProcessHeap(), 0, nameW );
    ok( res == ERROR_SUCCESS , "Failed to create database %u\n", res );
    if (res != ERROR_SUCCESS)
        return res;

    res = MsiDatabaseCommit( hdb );
    ok( res == ERROR_SUCCESS , "Failed to commit database %u\n", res );

    /* build summary info */
    res = MsiGetSummaryInformationA(hdb, NULL, 7, &suminfo);
    ok( res == ERROR_SUCCESS , "Failed to open summaryinfo\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo,2, VT_LPSTR, 0,NULL,
                        "Installation Database");
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo,3, VT_LPSTR, 0,NULL,
                        "Installation Database");
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo,4, VT_LPSTR, 0,NULL,
                        "Wine Hackers");
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo,7, VT_LPSTR, 0,NULL,
                    ";1033");
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo,9, VT_LPSTR, 0,NULL,
                    "{913B8D18-FBB6-4CAC-A239-C74C11E3FA74}");
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo, 14, VT_I4, 100, NULL, NULL);
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoSetPropertyA(suminfo, 15, VT_I4, 0, NULL, NULL);
    ok( res == ERROR_SUCCESS , "Failed to set summary info\n" );

    res = MsiSummaryInfoPersist(suminfo);
    ok( res == ERROR_SUCCESS , "Failed to make summary info persist\n" );

    res = MsiCloseHandle( suminfo);
    ok( res == ERROR_SUCCESS , "Failed to close suminfo\n" );

    res = package_from_db( hdb, &hPackage );
    MsiCloseHandle(hdb);

    if (res != ERROR_SUCCESS)
        DeleteFileA( szName );
    else
        *handle = hPackage;

    return res;
}