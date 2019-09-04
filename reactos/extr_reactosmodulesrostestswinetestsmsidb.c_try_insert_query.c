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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  try_query_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT try_insert_query( MSIHANDLE hdb, LPCSTR szQuery )
{
    MSIHANDLE hrec = 0;
    UINT r;

    hrec = MsiCreateRecord( 1 );
    MsiRecordSetStringA( hrec, 1, "Hello");

    r = try_query_param( hdb, szQuery, hrec );

    MsiCloseHandle( hrec );
    return r;
}