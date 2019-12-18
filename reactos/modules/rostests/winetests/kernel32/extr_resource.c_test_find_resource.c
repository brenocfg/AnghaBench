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
typedef  scalar_t__ HRSRC ;

/* Variables and functions */
 scalar_t__ ERROR_RESOURCE_LANG_NOT_FOUND ; 
 scalar_t__ ERROR_RESOURCE_NAME_NOT_FOUND ; 
 scalar_t__ ERROR_RESOURCE_TYPE_NOT_FOUND ; 
 scalar_t__ FindResourceExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_FRENCH ; 
 int /*<<< orphan*/  LANG_GERMAN ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RT_DIALOG ; 
 scalar_t__ RT_MENU ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_find_resource(void)
{
    HRSRC rsrc;

    rsrc = FindResourceW( GetModuleHandleW(NULL), MAKEINTRESOURCEW(1), (LPCWSTR)RT_MENU );
    ok( rsrc != 0, "resource not found\n" );
    rsrc = FindResourceExW( GetModuleHandleW(NULL), (LPCWSTR)RT_MENU, MAKEINTRESOURCEW(1),
                            MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL ));
    ok( rsrc != 0, "resource not found\n" );
    rsrc = FindResourceExW( GetModuleHandleW(NULL), (LPCWSTR)RT_MENU, MAKEINTRESOURCEW(1),
                            MAKELANGID( LANG_GERMAN, SUBLANG_DEFAULT ));
    ok( rsrc != 0, "resource not found\n" );

    SetLastError( 0xdeadbeef );
    rsrc = FindResourceW( GetModuleHandleW(NULL), MAKEINTRESOURCEW(1), (LPCWSTR)RT_DIALOG );
    ok( !rsrc, "resource found\n" );
    ok( GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    rsrc = FindResourceW( GetModuleHandleW(NULL), MAKEINTRESOURCEW(2), (LPCWSTR)RT_MENU );
    ok( !rsrc, "resource found\n" );
    ok( GetLastError() == ERROR_RESOURCE_NAME_NOT_FOUND, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    rsrc = FindResourceExW( GetModuleHandleW(NULL), (LPCWSTR)RT_MENU, MAKEINTRESOURCEW(1),
                            MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT ) );
    ok( !rsrc, "resource found\n" );
    ok( GetLastError() == ERROR_RESOURCE_LANG_NOT_FOUND, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    rsrc = FindResourceExW( GetModuleHandleW(NULL), (LPCWSTR)RT_MENU, MAKEINTRESOURCEW(1),
                            MAKELANGID( LANG_FRENCH, SUBLANG_DEFAULT ) );
    ok( !rsrc, "resource found\n" );
    ok( GetLastError() == ERROR_RESOURCE_LANG_NOT_FOUND, "wrong error %u\n", GetLastError() );
}