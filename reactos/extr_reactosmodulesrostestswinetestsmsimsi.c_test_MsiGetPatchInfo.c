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
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int REGSAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int ERROR_UNKNOWN_PROPERTY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 char* INSTALLPROPERTY_LOCALPACKAGEA ; 
 int /*<<< orphan*/  INSTALLPROPERTY_LOCALPACKAGEW ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int MAX_PATH ; 
 int MsiGetPatchInfoA (char*,char*,char*,int*) ; 
 int MsiGetPatchInfoW (int*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiGetPatchInfo(void)
{
    UINT r;
    char prod_code[MAX_PATH], prod_squashed[MAX_PATH], val[MAX_PATH];
    char patch_code[MAX_PATH], patch_squashed[MAX_PATH], keypath[MAX_PATH];
    WCHAR valW[MAX_PATH], patch_codeW[MAX_PATH];
    HKEY hkey_product, hkey_patch, hkey_patches, hkey_udprops, hkey_udproduct;
    HKEY hkey_udpatch, hkey_udpatches, hkey_udproductpatches, hkey_udproductpatch;
    DWORD size;
    LONG res;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(patch_code, patch_squashed);
    create_test_guid(prod_code, prod_squashed);
    MultiByteToWideChar(CP_ACP, 0, patch_code, -1, patch_codeW, MAX_PATH);

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    r = MsiGetPatchInfoA(NULL, NULL, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", r);

    r = MsiGetPatchInfoA(patch_code, NULL, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", r);

    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, NULL, NULL);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT, got %u\n", r);

    size = 0;
    r = MsiGetPatchInfoA(patch_code, NULL, NULL, &size);
    ok(r == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", r);

    r = MsiGetPatchInfoA(patch_code, "", NULL, &size);
    ok(r == ERROR_UNKNOWN_PROPERTY, "expected ERROR_UNKNOWN_PROPERTY, got %u\n", r);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &hkey_product, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        return;
    }
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    res = RegCreateKeyExA(hkey_product, "Patches", 0, NULL, 0, access, NULL, &hkey_patches, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    res = RegCreateKeyExA(hkey_patches, patch_squashed, 0, NULL, 0, access, NULL, &hkey_patch, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* patch key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer");
    lstrcatA(keypath, "\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &hkey_udproduct, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        goto done;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", res);

    /* UserData product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    res = RegCreateKeyExA(hkey_udproduct, "InstallProperties", 0, NULL, 0, access, NULL, &hkey_udprops, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* InstallProperties key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    res = RegCreateKeyExA(hkey_udproduct, "Patches", 0, NULL, 0, access, NULL, &hkey_udpatches, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* UserData Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    res = RegCreateKeyExA(hkey_udproduct, "Patches", 0, NULL, 0, access, NULL, &hkey_udproductpatches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    res = RegCreateKeyExA(hkey_udproductpatches, patch_squashed, 0, NULL, 0, access, NULL, &hkey_udproductpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData product patch key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "expected ERROR_UNKNOWN_PRODUCT got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected val to be unchanged got \"%s\"\n", val);
    ok(size == MAX_PATH, "expected size to be unchanged got %u\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer");
    lstrcatA(keypath, "\\UserData\\S-1-5-18\\Patches\\");
    lstrcatA(keypath, patch_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &hkey_udpatch, NULL);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    res = RegSetValueExA(hkey_udpatch, "LocalPackage", 0, REG_SZ, (const BYTE *)"c:\\test.msp", 12);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS got %d\n", res);

    /* UserData Patch key exists */
    size = 0;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_MORE_DATA, "expected ERROR_MORE_DATA got %u\n", r);
    ok(!lstrcmpA(val, "apple"), "expected \"apple\", got \"%s\"\n", val);
    ok(size == 11, "expected 11 got %u\n", size);

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetPatchInfoA(patch_code, INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "expected ERROR_SUCCESS got %u\n", r);
    ok(!lstrcmpA(val, "c:\\test.msp"), "expected \"c:\\test.msp\", got \"%s\"\n", val);
    ok(size == 11, "expected 11 got %u\n", size);

    size = 0;
    valW[0] = 0;
    r = MsiGetPatchInfoW(patch_codeW, INSTALLPROPERTY_LOCALPACKAGEW, valW, &size);
    ok(r == ERROR_MORE_DATA, "expected ERROR_MORE_DATA got %u\n", r);
    ok(!valW[0], "expected 0 got %u\n", valW[0]);
    ok(size == 11, "expected 11 got %u\n", size);

    size = MAX_PATH;
    valW[0] = 0;
    r = MsiGetPatchInfoW(patch_codeW, INSTALLPROPERTY_LOCALPACKAGEW, valW, &size);
    ok(r == ERROR_SUCCESS, "expected ERROR_SUCCESS got %u\n", r);
    ok(valW[0], "expected > 0 got %u\n", valW[0]);
    ok(size == 11, "expected 11 got %u\n", size);

    delete_key(hkey_udproductpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udproductpatch);
    delete_key(hkey_udproductpatches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udproductpatches);
    delete_key(hkey_udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udpatch);
    delete_key(hkey_udpatches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udpatches);
    delete_key(hkey_udprops, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udprops);
    delete_key(hkey_udproduct, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_udproduct);

done:
    delete_key(hkey_patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_patches);
    delete_key(hkey_product, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_product);
    delete_key(hkey_patch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hkey_patch);
}