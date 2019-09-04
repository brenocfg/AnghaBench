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
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_REJECTED ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetPropertyA (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_getproperty(void)
{
    MSIHANDLE hPackage = 0;
    char prop[100];
    static CHAR empty[] = "";
    DWORD size;
    UINT r;

    r = package_from_db(create_package_db(), &hPackage);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "Failed to create package %u\n", r );

    /* set the property */
    r = MsiSetPropertyA(hPackage, "Name", "Value");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* retrieve the size, NULL pointer */
    size = 0;
    r = MsiGetPropertyA(hPackage, "Name", NULL, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok( size == 5, "Expected 5, got %d\n", size);

    /* retrieve the size, empty string */
    size = 0;
    r = MsiGetPropertyA(hPackage, "Name", empty, &size);
    ok( r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok( size == 5, "Expected 5, got %d\n", size);

    /* don't change size */
    r = MsiGetPropertyA(hPackage, "Name", prop, &size);
    ok( r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok( size == 5, "Expected 5, got %d\n", size);
    ok( !lstrcmpA(prop, "Valu"), "Expected Valu, got %s\n", prop);

    /* increase the size by 1 */
    size++;
    r = MsiGetPropertyA(hPackage, "Name", prop, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok( size == 5, "Expected 5, got %d\n", size);
    ok( !lstrcmpA(prop, "Value"), "Expected Value, got %s\n", prop);

    r = MsiCloseHandle( hPackage);
    ok( r == ERROR_SUCCESS , "Failed to close package\n" );
    DeleteFileA(msifile);
}