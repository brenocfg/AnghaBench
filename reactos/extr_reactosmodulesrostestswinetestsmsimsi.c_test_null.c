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
typedef  int REGSAM ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ INSTALLSTATE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNKNOWN_PRODUCT ; 
 scalar_t__ ERROR_UNKNOWN_PROPERTY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSTALLSTATE_DEFAULT ; 
 scalar_t__ INSTALLSTATE_INVALIDARG ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 scalar_t__ MsiConfigureFeatureA (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiConfigureFeatureW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiEnumFeaturesW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiGetProductInfoA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiQueryProductStateW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ delete_key (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pMsiOpenPackageExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_null(void)
{
    MSIHANDLE hpkg;
    UINT r;
    HKEY hkey;
    DWORD dwType, cbData;
    LPBYTE lpData = NULL;
    INSTALLSTATE state;
    REGSAM access = KEY_ALL_ACCESS;

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    r = pMsiOpenPackageExW(NULL, 0, &hpkg);
    ok( r == ERROR_INVALID_PARAMETER,"wrong error\n");

    state = MsiQueryProductStateW(NULL);
    ok( state == INSTALLSTATE_INVALIDARG, "wrong return\n");

    r = MsiEnumFeaturesW(NULL,0,NULL,NULL);
    ok( r == ERROR_INVALID_PARAMETER,"wrong error\n");

    r = MsiConfigureFeatureW(NULL, NULL, 0);
    ok( r == ERROR_INVALID_PARAMETER, "wrong error\n");

    r = MsiConfigureFeatureA("{00000000-0000-0000-0000-000000000000}", NULL, 0);
    ok( r == ERROR_INVALID_PARAMETER, "wrong error\n");

    r = MsiConfigureFeatureA("{00000000-0000-0000-0000-000000000001}", "foo", 0);
    ok( r == ERROR_INVALID_PARAMETER, "wrong error %d\n", r);

    r = MsiConfigureFeatureA("{00000000-0000-0000-0000-000000000002}", "foo", INSTALLSTATE_DEFAULT);
    ok( r == ERROR_UNKNOWN_PRODUCT, "wrong error %d\n", r);

    /* make sure empty string to MsiGetProductInfo is not a handle to default registry value, saving and restoring the
     * necessary registry values */

    /* empty product string */
    r = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, access, &hkey);
    if (r == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        return;
    }
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    r = RegQueryValueExA(hkey, NULL, 0, &dwType, lpData, &cbData);
    ok ( r == ERROR_SUCCESS || r == ERROR_FILE_NOT_FOUND, "wrong error %d\n", r);
    if ( r == ERROR_SUCCESS )
    {
        lpData = HeapAlloc(GetProcessHeap(), 0, cbData);
        if (!lpData)
            skip("Out of memory\n");
        else
        {
            r = RegQueryValueExA(hkey, NULL, 0, &dwType, lpData, &cbData);
            ok ( r == ERROR_SUCCESS, "wrong error %d\n", r);
        }
    }

    r = RegSetValueA(hkey, NULL, REG_SZ, "test", strlen("test"));
    if (r == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        HeapFree(GetProcessHeap(), 0, lpData);
        RegCloseKey(hkey);
        return;
    }
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    r = MsiGetProductInfoA("", "", NULL, NULL);
    ok ( r == ERROR_INVALID_PARAMETER, "wrong error %d\n", r);

    if (lpData)
    {
        r = RegSetValueExA(hkey, NULL, 0, dwType, lpData, cbData);
        ok ( r == ERROR_SUCCESS, "wrong error %d\n", r);

        HeapFree(GetProcessHeap(), 0, lpData);
    }
    else
    {
        r = RegDeleteValueA(hkey, NULL);
        ok ( r == ERROR_SUCCESS, "wrong error %d\n", r);
    }

    r = RegCloseKey(hkey);
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    /* empty attribute */
    r = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{F1C3AF50-8B56-4A69-A00C-00773FE42F30}",
                        0, NULL, 0, access, NULL, &hkey, NULL);
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    r = RegSetValueA(hkey, NULL, REG_SZ, "test", strlen("test"));
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    r = MsiGetProductInfoA("{F1C3AF50-8B56-4A69-A00C-00773FE42F30}", "", NULL, NULL);
    ok ( r == ERROR_UNKNOWN_PROPERTY, "wrong error %d\n", r);

    r = RegCloseKey(hkey);
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);

    r = delete_key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{F1C3AF50-8B56-4A69-A00C-00773FE42F30}",
                   access & KEY_WOW64_64KEY);
    ok( r == ERROR_SUCCESS, "wrong error %d\n", r);
}