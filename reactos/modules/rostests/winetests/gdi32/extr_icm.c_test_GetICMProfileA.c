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
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int GetICMProfileA (int /*<<< orphan*/ *,scalar_t__*,char*) ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetICMProfileA( HDC dc )
{
    BOOL ret;
    DWORD size, error;
    char filename[MAX_PATH];

    SetLastError( 0xdeadbeef );
    ret = GetICMProfileA( NULL, NULL, NULL );
    if ( !ret && ( GetLastError() == ERROR_CALL_NOT_IMPLEMENTED ) )
    {
        win_skip( "GetICMProfileA is not implemented\n" );
        return;
    }
    ok( !ret, "GetICMProfileA succeeded\n" );

    ret = GetICMProfileA( dc, NULL, NULL );
    ok( !ret, "GetICMProfileA succeeded\n" );

    size = MAX_PATH;
    ret = GetICMProfileA( dc, &size, NULL );
    ok( !ret, "GetICMProfileA succeeded\n" );
    ok( size > 0, "got %u\n", size );

    size = 0;
    ret = GetICMProfileA( dc, &size, NULL );
    ok( !ret, "GetICMProfileA succeeded\n" );
    ok( size > 0, "got %u\n", size );

    size = MAX_PATH;
    ret = GetICMProfileA( NULL, &size, filename );
    ok( !ret, "GetICMProfileA succeeded\n" );

    size = 0;
    filename[0] = 0;
    SetLastError(0xdeadbeef);
    ret = GetICMProfileA( dc, &size, filename );
    error = GetLastError();
    ok( !ret, "GetICMProfileA succeeded\n" );
    ok( size, "expected size > 0\n" );
    ok( filename[0] == 0, "Expected filename to be empty\n" );
    ok( error == ERROR_INSUFFICIENT_BUFFER, "got %d, expected ERROR_INSUFFICIENT_BUFFER\n", error );

    ret = GetICMProfileA( dc, NULL, filename );
    ok( !ret, "GetICMProfileA succeeded\n" );

    size = MAX_PATH;
    ret = GetICMProfileA( dc, &size, filename );
    ok( ret, "GetICMProfileA failed %d\n", GetLastError() );

    trace( "%s\n", filename );
}