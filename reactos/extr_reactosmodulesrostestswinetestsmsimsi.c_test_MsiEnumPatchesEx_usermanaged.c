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
typedef  int MSIINSTALLCONTEXT ;
typedef  char* LPCSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int MAX_PATH ; 
 int MSIINSTALLCONTEXT_USERMANAGED ; 
 int MSIPATCHSTATE_ALL ; 
 int MSIPATCHSTATE_APPLIED ; 
 int MSIPATCHSTATE_OBSOLETED ; 
 int MSIPATCHSTATE_SUPERSEDED ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiEnumPatchesExA (char*,char*,int,int,int,char*,char*,int*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void test_MsiEnumPatchesEx_usermanaged(LPCSTR usersid, LPCSTR expectedsid)
{
    MSIINSTALLCONTEXT context;
    CHAR keypath[MAX_PATH], patch[MAX_PATH];
    CHAR patch_squashed[MAX_PATH], patchcode[MAX_PATH];
    CHAR targetsid[MAX_PATH], targetprod[MAX_PATH];
    CHAR prodcode[MAX_PATH], prod_squashed[MAX_PATH];
    HKEY prodkey, patches, udprod, udpatch, hpatch;
    DWORD size, data;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(prodcode, prod_squashed);
    create_test_guid(patch, patch_squashed);

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* MSIPATCHSTATE_APPLIED */

    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    if (r == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        return;
    }
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, expectedsid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* managed product key exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patches key exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not REG_MULTI_SZ */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)"a\0b\0c\0\0", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists, is not a squashed guid */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    patch_squashed[lstrlenA(patch_squashed) + 1] = '\0';
    res = RegSetValueExA(patches, "Patches", 0, REG_MULTI_SZ,
                         (const BYTE *)patch_squashed,
                         lstrlenA(patch_squashed) + 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches value exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(patches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"whatever", 9);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patch squashed value exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* increase the index */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 1, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* increase again */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 2, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szPatchCode is NULL */
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, NULL, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* szTargetProductCode is NULL */
    lstrcpyA(patchcode, "apple");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, NULL,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* pdwTargetProductContext is NULL */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           NULL, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* szTargetUserSid is NULL */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, NULL, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(size == lstrlenA(expectedsid) * sizeof(WCHAR),
       "Expected %d*sizeof(WCHAR), got %d\n", lstrlenA(expectedsid), size);

    /* pcchTargetUserSid is exactly the length of szTargetUserSid */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = lstrlenA(expectedsid);
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!strncmp(targetsid, expectedsid, lstrlenA(expectedsid) - 1),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid) * sizeof(WCHAR),
       "Expected %d*sizeof(WCHAR), got %d\n", lstrlenA(expectedsid), size);

    /* pcchTargetUserSid has enough room for NULL terminator */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = lstrlenA(expectedsid) + 1;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* both szTargetuserSid and pcchTargetUserSid are NULL */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_APPLIED, 0, patchcode, targetprod,
                           &context, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);

    /* MSIPATCHSTATE_SUPERSEDED */

    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_SUPERSEDED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, expectedsid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udprod, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData product key exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_SUPERSEDED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "Patches", 0, NULL, 0, access, NULL, &udpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData patches key exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_SUPERSEDED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udpatch, patch_squashed, 0, NULL, 0, access, NULL, &hpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* specific UserData patch key exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_SUPERSEDED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    data = MSIPATCHSTATE_SUPERSEDED;
    res = RegSetValueExA(hpatch, "State", 0, REG_DWORD,
                         (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* State value exists */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_SUPERSEDED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* MSIPATCHSTATE_OBSOLETED */

    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_OBSOLETED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    data = MSIPATCHSTATE_OBSOLETED;
    res = RegSetValueExA(hpatch, "State", 0, REG_DWORD,
                         (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* State value is obsoleted */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_OBSOLETED, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* MSIPATCHSTATE_REGISTERED */
    /* FIXME */

    /* MSIPATCHSTATE_ALL */

    /* 1st */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(patchcode, patch),
       "Expected \"%s\", got \"%s\"\n", patch, patchcode);
    ok(!lstrcmpA(targetprod, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, targetprod);
    ok(context == MSIINSTALLCONTEXT_USERMANAGED,
       "Expected MSIINSTALLCONTEXT_USERMANAGED, got %d\n", context);
    ok(!lstrcmpA(targetsid, expectedsid),
       "Expected \"%s\", got \"%s\"\n", expectedsid, targetsid);
    ok(size == lstrlenA(expectedsid),
       "Expected %d, got %d\n", lstrlenA(expectedsid), size);

    /* same patch in multiple places, only one is enumerated */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                           MSIPATCHSTATE_ALL, 1, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    RegDeleteValueA(hpatch, "State");
    delete_key(hpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hpatch);
    delete_key(udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udpatch);
    delete_key(udprod, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udprod);
    RegDeleteValueA(patches, "Patches");
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
}