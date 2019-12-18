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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BeginUpdateResourceA (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FILE_INVALID ; 
 scalar_t__ EndUpdateResourceA (scalar_t__,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void update_empty_exe( void )
{
    HANDLE file, res, test;
    BOOL r;

    file = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok (file != INVALID_HANDLE_VALUE, "failed to create file\n");

    CloseHandle( file );

    res = BeginUpdateResourceA( filename, TRUE );
    if ( res != NULL || GetLastError() != ERROR_FILE_INVALID )
    {
        ok( res != NULL, "BeginUpdateResource failed\n");

        /* check if it's possible to open the file now */
        test = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
        ok (test != INVALID_HANDLE_VALUE, "failed to create file\n");

        CloseHandle( test );

        r = EndUpdateResourceA( res, FALSE );
        ok( r == FALSE, "EndUpdateResource failed\n");
    }
    else
        skip( "Can't update resource in empty file\n" );

    res = BeginUpdateResourceA( filename, FALSE );
    ok( res == NULL, "BeginUpdateResource failed\n");
}