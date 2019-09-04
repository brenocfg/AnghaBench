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
typedef  int /*<<< orphan*/  MSICOLINFO ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiDatabaseOpenViewA (scalar_t__,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  MsiViewClose (scalar_t__) ; 
 scalar_t__ MsiViewExecute (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiViewGetColumnInfo (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static MSIHANDLE get_column_info(MSIHANDLE hdb, const char *query, MSICOLINFO type)
{
    MSIHANDLE hview = 0, rec = 0;
    UINT r;

    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    if( r != ERROR_SUCCESS )
        return r;

    r = MsiViewExecute(hview, 0);
    if( r == ERROR_SUCCESS )
    {
        MsiViewGetColumnInfo( hview, type, &rec );
    }
    MsiViewClose(hview);
    MsiCloseHandle(hview);
    return rec;
}