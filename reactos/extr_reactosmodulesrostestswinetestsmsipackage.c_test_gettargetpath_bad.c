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
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_DIRECTORY ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiGetTargetPathA (int /*<<< orphan*/ ,char*,char*,scalar_t__*) ; 
 scalar_t__ MsiGetTargetPathW (int /*<<< orphan*/ ,char const*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_gettargetpath_bad(void)
{
    static const WCHAR boo[] = {'b','o','o',0};
    static const WCHAR empty[] = {0};
    char buffer[0x80];
    WCHAR bufferW[0x80];
    MSIHANDLE hpkg;
    DWORD sz;
    UINT r;

    r = package_from_db(create_package_db(), &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r);

    r = MsiGetTargetPathA( 0, NULL, NULL, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiGetTargetPathA( 0, NULL, NULL, &sz );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiGetTargetPathA( 0, "boo", NULL, NULL );
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiGetTargetPathA( 0, "boo", NULL, NULL );
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiGetTargetPathA( hpkg, "boo", NULL, NULL );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    r = MsiGetTargetPathA( hpkg, "boo", buffer, NULL );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    sz = 0;
    r = MsiGetTargetPathA( hpkg, "", buffer, &sz );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    r = MsiGetTargetPathW( 0, NULL, NULL, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiGetTargetPathW( 0, NULL, NULL, &sz );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiGetTargetPathW( 0, boo, NULL, NULL );
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiGetTargetPathW( 0, boo, NULL, NULL );
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiGetTargetPathW( hpkg, boo, NULL, NULL );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    r = MsiGetTargetPathW( hpkg, boo, bufferW, NULL );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    sz = 0;
    r = MsiGetTargetPathW( hpkg, empty, bufferW, &sz );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    MsiCloseHandle( hpkg );
    DeleteFileA(msifile);
}