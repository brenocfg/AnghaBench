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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  char* LPCSTR ;
typedef  int INT_PTR ;
typedef  int ATOM ;

/* Variables and functions */
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  FOOBARW ; 
 int GetLastError () ; 
 int GlobalAddAtomA (char*) ; 
 int GlobalAddAtomW (int /*<<< orphan*/ ) ; 
 int GlobalFindAtomA (char*) ; 
 int GlobalFindAtomW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _foobarW ; 
 int /*<<< orphan*/  foobarW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 
 scalar_t__ unicode_OS ; 

__attribute__((used)) static void test_add_atom(void)
{
    ATOM atom, w_atom;
    INT_PTR i;

    SetLastError( 0xdeadbeef );
    atom = GlobalAddAtomA( "foobar" );
    ok( atom >= 0xc000, "bad atom id %x\n", atom );
    ok( GetLastError() == 0xdeadbeef, "GlobalAddAtomA set last error\n" );

    /* Verify that it can be found (or not) appropriately */
    ok( GlobalFindAtomA( "foobar" ) == atom, "could not find atom foobar\n" );
    ok( GlobalFindAtomA( "FOOBAR" ) == atom, "could not find atom FOOBAR\n" );
    ok( !GlobalFindAtomA( "_foobar" ), "found _foobar\n" );

    /* Add the same atom, specifying string as unicode; should
     * find the first one, not add a new one */
    SetLastError( 0xdeadbeef );
    w_atom = GlobalAddAtomW( foobarW );
    if (w_atom && GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
        unicode_OS = TRUE;
    else
        trace("WARNING: Unicode atom APIs are not supported on this platform\n");

    if (unicode_OS)
    {
        ok( w_atom == atom, "Unicode atom does not match ASCII\n" );
        ok( GetLastError() == 0xdeadbeef, "GlobalAddAtomW set last error\n" );
    }

    /* Verify that it can be found (or not) appropriately via unicode name */
    if (unicode_OS)
    {
        ok( GlobalFindAtomW( foobarW ) == atom, "could not find atom foobar\n" );
        ok( GlobalFindAtomW( FOOBARW ) == atom, "could not find atom FOOBAR\n" );
        ok( !GlobalFindAtomW( _foobarW ), "found _foobar\n" );
    }

    /* Test integer atoms
     * (0x0001 .. 0xbfff) should be valid;
     * (0xc000 .. 0xffff) should be invalid */

    SetLastError( 0xdeadbeef );
    ok( GlobalAddAtomA(0) == 0 && GetLastError() == 0xdeadbeef, "succeeded to add atom 0\n" );
    if (unicode_OS)
    {
        SetLastError( 0xdeadbeef );
        ok( GlobalAddAtomW(0) == 0 && GetLastError() == 0xdeadbeef, "succeeded to add atom 0\n" );
    }

    SetLastError( 0xdeadbeef );
    for (i = 1; i <= 0xbfff; i++)
    {
        SetLastError( 0xdeadbeef );
        ok( GlobalAddAtomA((LPCSTR)i) == i && GetLastError() == 0xdeadbeef,
            "failed to add atom %lx\n", i );
        if (unicode_OS)
        {
            SetLastError( 0xdeadbeef );
            ok( GlobalAddAtomW((LPCWSTR)i) == i && GetLastError() == 0xdeadbeef,
                "failed to add atom %lx\n", i );
        }
    }

    for (i = 0xc000; i <= 0xffff; i++)
    {
        ok( !GlobalAddAtomA((LPCSTR)i), "succeeded adding %lx\n", i );
        if (unicode_OS)
            ok( !GlobalAddAtomW((LPCWSTR)i), "succeeded adding %lx\n", i );
    }
}