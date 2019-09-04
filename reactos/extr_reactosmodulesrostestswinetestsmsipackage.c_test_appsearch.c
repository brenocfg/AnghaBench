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
typedef  int /*<<< orphan*/  prop ;
typedef  scalar_t__ UINT ;
typedef  int MSIHANDLE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 scalar_t__ MsiDoActionA (int,char*) ; 
 scalar_t__ MsiGetPropertyA (int,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  add_appsearch_entry (int,char*) ; 
 int /*<<< orphan*/  add_drlocator_entry (int,char*) ; 
 int /*<<< orphan*/  add_reglocator_entry (int,char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  add_signature_entry (int,char*) ; 
 int /*<<< orphan*/  create_appsearch_table (int) ; 
 int /*<<< orphan*/  create_drlocator_table (int) ; 
 int create_package_db () ; 
 int /*<<< orphan*/  create_reglocator_table (int) ; 
 int /*<<< orphan*/  create_signature_table (int) ; 
 scalar_t__ lstrlenA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void test_appsearch(void)
{
    MSIHANDLE hpkg;
    UINT r;
    MSIHANDLE hdb;
    CHAR prop[MAX_PATH];
    DWORD size;
    HKEY hkey;
    const char reg_expand_value[] = "%systemroot%\\system32\\notepad.exe";

    hdb = create_package_db();
    ok ( hdb, "failed to create package database\n" );

    create_appsearch_table( hdb );
    add_appsearch_entry( hdb, "'WEBBROWSERPROG', 'NewSignature1'" );
    add_appsearch_entry( hdb, "'NOTEPAD', 'NewSignature2'" );
    add_appsearch_entry( hdb, "'REGEXPANDVAL', 'NewSignature3'" );

    create_reglocator_table( hdb );
    add_reglocator_entry( hdb, "NewSignature1", 0, "htmlfile\\shell\\open\\command", "", 1 );

    r = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Winetest_msi", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey, NULL);
    ok( r == ERROR_SUCCESS, "Could not create key: %d.\n", r );
    r = RegSetValueExA(hkey, NULL, 0, REG_EXPAND_SZ, (const BYTE*)reg_expand_value, strlen(reg_expand_value) + 1);
    ok( r == ERROR_SUCCESS, "Could not set key value: %d.\n", r);
    RegCloseKey(hkey);
    add_reglocator_entry( hdb, "NewSignature3", 1, "Software\\Winetest_msi", "", 1 );

    create_drlocator_table( hdb );
    add_drlocator_entry( hdb, "'NewSignature2', 0, 'c:\\windows\\system32', 0" );

    create_signature_table( hdb );
    add_signature_entry( hdb, "'NewSignature1', 'FileName', '', '', '', '', '', '', ''" );
    add_signature_entry( hdb, "'NewSignature2', 'NOTEPAD.EXE|notepad.exe', '', '', '', '', '', '', ''" );
    add_signature_entry( hdb, "'NewSignature3', 'NOTEPAD.EXE|notepad.exe', '', '', '', '', '', '', ''" );

    r = package_from_db( hdb, &hpkg );
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r );
    MsiCloseHandle( hdb );
    if (r != ERROR_SUCCESS)
        goto done;

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA( hpkg, "AppSearch" );
    ok( r == ERROR_SUCCESS, "AppSearch failed: %d\n", r);

    size = sizeof(prop);
    r = MsiGetPropertyA( hpkg, "WEBBROWSERPROG", prop, &size );
    ok( r == ERROR_SUCCESS, "get property failed: %d\n", r);
    ok( lstrlenA(prop) != 0, "Expected non-zero length\n");

    size = sizeof(prop);
    r = MsiGetPropertyA( hpkg, "NOTEPAD", prop, &size );
    ok( r == ERROR_SUCCESS, "get property failed: %d\n", r);

    size = sizeof(prop);
    r = MsiGetPropertyA( hpkg, "REGEXPANDVAL", prop, &size );
    ok( r == ERROR_SUCCESS, "get property failed: %d\n", r);
    ok( lstrlenA(prop) != 0, "Expected non-zero length\n");

done:
    MsiCloseHandle( hpkg );
    DeleteFileA(msifile);
    RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Winetest_msi");
}