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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 scalar_t__ MsiFormatRecordA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiRecordSetStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void query_file_path(MSIHANDLE hpkg, LPCSTR file, LPSTR buff)
{
    UINT r;
    DWORD size;
    MSIHANDLE rec;

    rec = MsiCreateRecord( 1 );
    ok(rec, "MsiCreate record failed\n");

    r = MsiRecordSetStringA( rec, 0, file );
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r );

    size = MAX_PATH;
    r = MsiFormatRecordA( hpkg, rec, buff, &size );
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r );

    MsiCloseHandle( rec );
}