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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MsiGetPropertyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_ccpsearch_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_drlocator_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_reglocator_entry (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  create_ccpsearch_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_drlocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  create_reglocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_signature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_ccpsearch(void)
{
    MSIHANDLE hdb, hpkg;
    CHAR prop[MAX_PATH];
    DWORD size = MAX_PATH;
    UINT r;

    hdb = create_package_db();
    ok(hdb, "failed to create package database\n");

    create_ccpsearch_table(hdb);
    add_ccpsearch_entry(hdb, "'CCP_random'");
    add_ccpsearch_entry(hdb, "'RMCCP_random'");

    create_reglocator_table(hdb);
    add_reglocator_entry(hdb, "CCP_random", 0, "htmlfile\\shell\\open\\nonexistent", "", 1);

    create_drlocator_table(hdb);
    add_drlocator_entry(hdb, "'RMCCP_random', '', 'C:\\', '0'");

    create_signature_table(hdb);

    r = package_from_db(hdb, &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok(r == ERROR_SUCCESS, "failed to create package %u\n", r);

    MsiCloseHandle(hdb);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA(hpkg, "CCPSearch");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiGetPropertyA(hpkg, "CCP_Success", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, "1"), "Expected 1, got %s\n", prop);

    MsiCloseHandle(hpkg);
    DeleteFileA(msifile);
}