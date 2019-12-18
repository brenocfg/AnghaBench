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
typedef  int INT ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static INT get_integer( MSIHANDLE hdb, UINT field, const char *query)
{
    UINT r;
    INT ret = -1;
    MSIHANDLE hview, hrec;

    r = MsiDatabaseOpenViewA( hdb, query, &hview );
    ok( r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r );

    r = MsiViewExecute( hview, 0 );
    ok( r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r );

    r = MsiViewFetch( hview, &hrec );
    ok( r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r );
    if (r == ERROR_SUCCESS)
    {
        UINT r_tmp;
        ret = MsiRecordGetInteger( hrec, field );
        MsiCloseHandle( hrec );

        r_tmp = MsiViewFetch( hview, &hrec );
        ok( r_tmp == ERROR_NO_MORE_ITEMS, "expected ERROR_NO_MORE_ITEMS, got %u\n", r);
    }

    MsiViewClose( hview );
    MsiCloseHandle( hview );
    return ret;
}