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
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int GetICMProfileW (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetICMProfileW( HDC dc )
{
    BOOL ret;
    DWORD size, error;
    WCHAR filename[MAX_PATH];

    SetLastError( 0xdeadbeef );
    ret = GetICMProfileW( NULL, NULL, NULL );
    if ( !ret && ( GetLastError() == ERROR_CALL_NOT_IMPLEMENTED ) )
    {
        win_skip( "GetICMProfileW is not implemented\n" );
        return;
    }
    ok( !ret, "GetICMProfileW succeeded\n" );

    ret = GetICMProfileW( dc, NULL, NULL );
    ok( !ret, "GetICMProfileW succeeded\n" );

    if (0)
    {
        /* Vista crashes */
        size = MAX_PATH;
        ret = GetICMProfileW( dc, &size, NULL );
        ok( ret, "GetICMProfileW failed %d\n", GetLastError() );
    }

    ret = GetICMProfileW( dc, NULL, filename );
    ok( !ret, "GetICMProfileW succeeded\n" );

    size = MAX_PATH;
    ret = GetICMProfileW( NULL, &size, filename );
    ok( !ret, "GetICMProfileW succeeded\n" );

    size = 0;
    ret = GetICMProfileW( dc, &size, NULL );
    ok( !ret, "GetICMProfileW succeeded\n" );
    ok( size > 0, "got %u\n", size );

    size = 0;
    SetLastError(0xdeadbeef);
    ret = GetICMProfileW( dc, &size, filename );
    error = GetLastError();
    ok( !ret, "GetICMProfileW succeeded\n" );
    ok( size, "expected size > 0\n" );
    ok( error == ERROR_INSUFFICIENT_BUFFER, "got %d, expected ERROR_INSUFFICIENT_BUFFER\n", error );

    size = MAX_PATH;
    ret = GetICMProfileW( dc, &size, filename );
    ok( ret, "GetICMProfileW failed %d\n", GetLastError() );
}