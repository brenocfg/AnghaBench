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
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseOpenViewA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiViewClose (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static UINT try_query_param( MSIHANDLE hdb, LPCSTR szQuery, MSIHANDLE hrec )
{
    MSIHANDLE htab = 0;
    UINT res;

    res = MsiDatabaseOpenViewA( hdb, szQuery, &htab );
    if( res == ERROR_SUCCESS )
    {
        UINT r;

        r = MsiViewExecute( htab, hrec );
        if( r != ERROR_SUCCESS )
        {
            res = r;
            fprintf(stderr,"MsiViewExecute failed %08x\n", res);
        }

        r = MsiViewClose( htab );
        if( r != ERROR_SUCCESS )
            res = r;

        r = MsiCloseHandle( htab );
        if( r != ERROR_SUCCESS )
            res = r;
    }
    return res;
}