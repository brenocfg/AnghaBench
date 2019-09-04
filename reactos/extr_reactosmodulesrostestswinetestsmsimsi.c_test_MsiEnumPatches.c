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
typedef  int UINT ;
typedef  int REGSAM ;
typedef  char* LPSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int ERROR_ACCESS_DENIED ; 
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSIPATCHSTATE_APPLIED ; 
 int MsiEnumPatchesA (char*,int,char*,char*,int*) ; 
 int MsiEnumPatchesW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiEnumPatches(void)
{
    CHAR keypath[MAX_PATH], patch[MAX_PATH];
    CHAR patchcode[MAX_PATH], patch_squashed[MAX_PATH];
    CHAR prodcode[MAX_PATH], prod_squashed[MAX_PATH];
    CHAR transforms[MAX_PATH];
    WCHAR patchW[MAX_PATH], prodcodeW[MAX_PATH], transformsW[MAX_PATH];
    HKEY prodkey, patches, udprod;
    HKEY userkey, hpatch, udpatch;
    DWORD size, data;
    LPSTR usersid;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(prodcode, prod_squashed);
    create_test_guid(patchcode, patch_squashed);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* NULL szProduct */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(NULL, 0, patch, transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* empty szProduct */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA("", 0, patch, transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* garbage szProduct */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA("garbage", 0, patch, transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid without brackets */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D", 0, patch,
                        transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid with brackets */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA("{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}", 0, patch,
                        transforms, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* same length as guid, but random */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA("A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93", 0, patch,
                        transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* managed product key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patches key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not REG_MULTI_SZ */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION ||
       broken(r == ERROR_SUCCESS), /* Windows Installer < 3.0 */
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)"a\0b\0c\0\0", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not a squashed guid */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    patch_squashed[lstrlenA(patch_squashed) + 1] = '\0';
    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple") ||
       broken(!lstrcmpA(patch, patchcode)), /* Windows Installer < 3.0 */
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"whatever", 9);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patch squashed value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    /* lpPatchBuf is NULL */
    size = MAX_PATH;
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, NULL, transforms, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* lpTransformsBuf is NULL, pcchTransformsBuf is not */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    r = MsiEnumPatchesA(prodcode, 0, patch, NULL, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* pcchTransformsBuf is NULL, lpTransformsBuf is not */
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);

    /* pcchTransformsBuf is too small */
    size = 6;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whate") ||
       broken(!lstrcmpA(transforms, "banana")), /* Windows Installer < 3.0 */
       "Expected \"whate\", got \"%s\"\n", transforms);
    ok(size == 8 || size == 16, "Expected 8 or 16, got %d\n", size);

    /* increase the index */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 1, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* increase again */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 2, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    RegDeleteValueA(patches, "Patches");
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &prodkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* current user product key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyA(prodkey, "Patches", &patches);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not REG_MULTI_SZ */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION ||
       broken(r == ERROR_SUCCESS), /* Windows Installer < 3.0 */
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)"a\0b\0c\0\0", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not a squashed guid */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    patch_squashed[lstrlenA(patch_squashed) + 1] = '\0';
    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple") ||
       broken(!lstrcmpA(patch, patchcode)), /* Windows Installer < 3.0 */
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"whatever", 9);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patch code value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_SUCCESS), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple") ||
       broken(!lstrcmpA(patch, patchcode)), /* Windows Installer < 3.0 */
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana") ||
       broken(!lstrcmpA(transforms, "whatever")), /* Windows Installer < 3.0 */
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Patches\\");
    lstrcatA(keypath, patch_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* userdata patch key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    delete_key(userkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(userkey);
    RegDeleteValueA(patches, patch_squashed);
    RegDeleteValueA(patches, "Patches");
    RegDeleteKeyA(patches, "");
    RegCloseKey(patches);
    RegDeleteKeyA(prodkey, "");
    RegCloseKey(prodkey);

    /* MSIINSTALLCONTEXT_MACHINE */

    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local product key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not REG_MULTI_SZ */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION ||
       broken(r == ERROR_SUCCESS), /* Windows Installer < 3.0 */
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)"a\0b\0c\0\0", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not a squashed guid */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patch, "apple"),
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    patch_squashed[lstrlenA(patch_squashed) + 1] = '\0';
    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_FILE_NOT_FOUND), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple") ||
       broken(!lstrcmpA(patch, patchcode)), /* Windows Installer < 3.0 */
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana"),
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"whatever", 9);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patch code value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udprod, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData product key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(udprod, "Patches", 0, NULL, 0, access, NULL, &udpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData Patches key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(udpatch, patch_squashed, 0, NULL, 0, access, NULL, &hpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData Product patch key exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_NO_MORE_ITEMS ||
       broken(r == ERROR_SUCCESS), /* Windows Installer < 3.0 */
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patch, "apple") ||
       broken(!lstrcmpA(patch, patchcode)), /* Windows Installer < 3.0 */
       "Expected lpPatchBuf to be unchanged, got \"%s\"\n", patch);
    ok(!lstrcmpA(transforms, "banana") ||
       broken(!lstrcmpA(transforms, "whatever")), /* Windows Installer < 3.0 */
       "Expected lpTransformsBuf to be unchanged, got \"%s\"\n", transforms);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    data = MSIPATCHSTATE_APPLIED;
    res = RegSetValueExA(hpatch, "State", 0, REG_DWORD,
                         (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* State value exists */
    size = MAX_PATH;
    lstrcpyA(patch, "apple");
    lstrcpyA(transforms, "banana");
    r = MsiEnumPatchesA(prodcode, 0, patch, transforms, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    /* now duplicate some of the tests for the W version */

    /* pcchTransformsBuf is too small */
    size = 6;
    MultiByteToWideChar( CP_ACP, 0, prodcode, -1, prodcodeW, MAX_PATH );
    MultiByteToWideChar( CP_ACP, 0, "apple", -1, patchW, MAX_PATH );
    MultiByteToWideChar( CP_ACP, 0, "banana", -1, transformsW, MAX_PATH );
    r = MsiEnumPatchesW(prodcodeW, 0, patchW, transformsW, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    WideCharToMultiByte( CP_ACP, 0, patchW, -1, patch, MAX_PATH, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, transformsW, -1, transforms, MAX_PATH, NULL, NULL );
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whate") ||
       broken(!lstrcmpA(transforms, "banana")), /* Windows Installer < 3.0 */
       "Expected \"whate\", got \"%s\"\n", transforms);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* patch code value exists */
    size = MAX_PATH;
    MultiByteToWideChar( CP_ACP, 0, "apple", -1, patchW, MAX_PATH );
    MultiByteToWideChar( CP_ACP, 0, "banana", -1, transformsW, MAX_PATH );
    r = MsiEnumPatchesW(prodcodeW, 0, patchW, transformsW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    WideCharToMultiByte( CP_ACP, 0, patchW, -1, patch, MAX_PATH, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, transformsW, -1, transforms, MAX_PATH, NULL, NULL );
    ok(!lstrcmpA(patch, patchcode),
       "Expected \"%s\", got \"%s\"\n", patchcode, patch);
    ok(!lstrcmpA(transforms, "whatever"),
       "Expected \"whatever\", got \"%s\"\n", transforms);
    ok(size == 8 || size == MAX_PATH, "Expected 8 or MAX_PATH, got %d\n", size);

    RegDeleteValueA(patches, patch_squashed);
    RegDeleteValueA(patches, "Patches");
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    RegDeleteValueA(hpatch, "State");
    delete_key(hpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hpatch);
    delete_key(udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udpatch);
    delete_key(udprod, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udprod);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    LocalFree(usersid);
}