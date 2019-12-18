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
typedef  int MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FUNCTION_NOT_CALLED ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 scalar_t__ MsiDoActionA (int,char*) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_doaction( void )
{
    MSIHANDLE hpkg;
    UINT r;

    r = MsiDoActionA( -1, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = package_from_db(create_package_db(), &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r);

    r = MsiDoActionA(hpkg, NULL);
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiDoActionA(0, "boo");
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiDoActionA(hpkg, "boo");
    ok( r == ERROR_FUNCTION_NOT_CALLED, "wrong return val\n");

    MsiCloseHandle( hpkg );
    DeleteFileA(msifile);
}