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
typedef  int UINT ;
typedef  int REGSAM ;
typedef  char* LPSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PATCH ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int ERROR_UNKNOWN_PROPERTY ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 char* INSTALLPROPERTY_DISPLAYNAMEA ; 
 char* INSTALLPROPERTY_INSTALLDATEA ; 
 char* INSTALLPROPERTY_LOCALPACKAGEA ; 
 char* INSTALLPROPERTY_MOREINFOURLA ; 
 char* INSTALLPROPERTY_PATCHSTATEA ; 
 char* INSTALLPROPERTY_TRANSFORMSA ; 
 char* INSTALLPROPERTY_UNINSTALLABLEA ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSIINSTALLCONTEXT_ALL ; 
 int MSIINSTALLCONTEXT_MACHINE ; 
 int MSIINSTALLCONTEXT_NONE ; 
 int MSIINSTALLCONTEXT_USERMANAGED ; 
 int MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiGetPatchInfoExA (char*,char*,char*,int,char*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiGetPatchInfoEx(void)
{
    CHAR keypath[MAX_PATH], val[MAX_PATH];
    CHAR patchcode[MAX_PATH], patch_squashed[MAX_PATH];
    CHAR prodcode[MAX_PATH], prod_squashed[MAX_PATH];
    HKEY prodkey, patches, udprod, props;
    HKEY hpatch, udpatch, prodpatches;
    LPSTR usersid;
    DWORD size;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiGetPatchInfoExA)
    {
        win_skip("MsiGetPatchInfoEx not implemented\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    create_test_guid(patchcode, patch_squashed);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* NULL szPatchCode */
    lstrcpyA(val, "apple");
    size = MAX_PATH;
    r = pMsiGetPatchInfoExA(NULL, prodcode, NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* empty szPatchCode */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA("", prodcode, NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* garbage szPatchCode */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA("garbage", prodcode, NULL,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid without brackets */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D", prodcode,
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid with brackets */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA("{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}", prodcode,
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* same length as guid, but random */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA("A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93", prodcode,
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* NULL szProductCode */
    lstrcpyA(val, "apple");
    size = MAX_PATH;
    r = pMsiGetPatchInfoExA(patchcode, NULL, NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* empty szProductCode */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, "", NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* garbage szProductCode */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, "garbage", NULL,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid without brackets */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, "6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D",
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid with brackets */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, "{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}",
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* same length as guid, but random */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, "A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93",
                            NULL, MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szUserSid cannot be S-1-5-18 for MSIINSTALLCONTEXT_USERMANAGED */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, "S-1-5-18",
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szUserSid cannot be S-1-5-18 for MSIINSTALLCONTEXT_USERUNMANAGED */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, "S-1-5-18",
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szUserSid cannot be S-1-5-18 for MSIINSTALLCONTEXT_MACHINE */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, "S-1-5-18",
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szUserSid must be NULL for MSIINSTALLCONTEXT_MACHINE */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is out of range */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_NONE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is out of range */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_ALL,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is invalid */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid, 3,
                           INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udprod, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* InstallProperties key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCHA, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(patches, patch_squashed, 0, NULL, 0, access, NULL, &hpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* managed product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "Patches", 0, NULL, 0, access, NULL, &prodpatches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(prodpatches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"transforms", 11);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* specific patch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Patches\\");
    lstrcatA(keypath, patch_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    res = RegSetValueExA(udpatch, "ManagedLocalPackage", 0, REG_SZ,
                         (const BYTE *)"pack", 5);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* ManagedLocalPatch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "transforms"), "Expected \"transforms\", got \"%s\"\n", val);
    ok(size == 10, "Expected 10, got %d\n", size);

    res = RegSetValueExA(hpatch, "Installed", 0, REG_SZ,
                         (const BYTE *)"mydate", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Installed value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_INSTALLDATEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "mydate"), "Expected \"mydate\", got \"%s\"\n", val);
    ok(size == 6, "Expected 6, got %d\n", size);

    res = RegSetValueExA(hpatch, "Uninstallable", 0, REG_SZ,
                         (const BYTE *)"yes", 4);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Uninstallable value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_UNINSTALLABLEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "yes"), "Expected \"yes\", got \"%s\"\n", val);
    ok(size == 3, "Expected 3, got %d\n", size);

    res = RegSetValueExA(hpatch, "State", 0, REG_SZ,
                         (const BYTE *)"good", 5);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* State value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_PATCHSTATEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "good"), "Expected \"good\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    size = 1;
    res = RegSetValueExA(hpatch, "State", 0, REG_DWORD,
                         (const BYTE *)&size, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* State value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_PATCHSTATEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "1"), "Expected \"1\", got \"%s\"\n", val);
    ok(size == 1, "Expected 1, got %d\n", size);

    size = 1;
    res = RegSetValueExA(hpatch, "Uninstallable", 0, REG_DWORD,
                         (const BYTE *)&size, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Uninstallable value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_UNINSTALLABLEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "1"), "Expected \"1\", got \"%s\"\n", val);
    ok(size == 1, "Expected 1, got %d\n", size);

    res = RegSetValueExA(hpatch, "DisplayName", 0, REG_SZ,
                         (const BYTE *)"display", 8);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* DisplayName value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_DISPLAYNAMEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "display"), "Expected \"display\", got \"%s\"\n", val);
    ok(size == 7, "Expected 7, got %d\n", size);

    res = RegSetValueExA(hpatch, "MoreInfoURL", 0, REG_SZ,
                         (const BYTE *)"moreinfo", 9);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* MoreInfoURL value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "moreinfo"), "Expected \"moreinfo\", got \"%s\"\n", val);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* szProperty is invalid */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            "IDontExist", val, &size);
    ok(r == ERROR_UNKNOWN_PROPERTY,
       "Expected ERROR_UNKNOWN_PROPERTY, got %d\n", r);
    ok(!lstrcmpA(val, "apple"), "Expected \"apple\", got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* lpValue is NULL, while pcchValue is non-NULL */
    size = MAX_PATH;
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, NULL, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == 16, "Expected 16, got %d\n", size);

    /* pcchValue is NULL, while lpValue is non-NULL */
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, val, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"), "Expected \"apple\", got \"%s\"\n", val);

    /* both lpValue and pcchValue are NULL */
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* pcchValue doesn't have enough room for NULL terminator */
    size = 8;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, val, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(val, "moreinf"),
       "Expected \"moreinf\", got \"%s\"\n", val);
    ok(size == 16, "Expected 16, got %d\n", size);

    /* pcchValue has exactly enough room for NULL terminator */
    size = 9;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "moreinfo"),
       "Expected \"moreinfo\", got \"%s\"\n", val);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* pcchValue is too small, lpValue is NULL */
    size = 0;
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_MOREINFOURLA, NULL, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == 16, "Expected 16, got %d\n", size);

    RegDeleteValueA(prodpatches, patch_squashed);
    delete_key(prodpatches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodpatches);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERMANAGED,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"), "Expected \"apple\", got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    RegDeleteValueA(hpatch, "MoreInfoURL");
    RegDeleteValueA(hpatch, "Display");
    RegDeleteValueA(hpatch, "State");
    RegDeleteValueA(hpatch, "Uninstallable");
    RegDeleteValueA(hpatch, "Installed");
    RegDeleteValueA(udpatch, "ManagedLocalPackage");
    delete_key(udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udpatch);
    delete_key(hpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hpatch);
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(udprod, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udprod);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udprod, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* InstallProperties key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(patches, patch_squashed, 0, NULL, 0, access, NULL, &hpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &prodkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* current user product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyA(prodkey, "Patches", &prodpatches);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(prodpatches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"transforms", 11);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* specific patch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Patches\\");
    lstrcatA(keypath, patch_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    res = RegSetValueExA(udpatch, "LocalPackage", 0, REG_SZ,
                         (const BYTE *)"pack", 5);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LocalPatch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "transforms"), "Expected \"transforms\", got \"%s\"\n", val);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(prodpatches, patch_squashed);
    delete_key(prodpatches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodpatches);
    RegDeleteKeyA(prodkey, "");
    RegCloseKey(prodkey);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, usersid,
                            MSIINSTALLCONTEXT_USERUNMANAGED,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"), "Expected \"apple\", got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    RegDeleteValueA(udpatch, "LocalPackage");
    delete_key(udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udpatch);
    delete_key(hpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hpatch);
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(udprod, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udprod);

    /* MSIINSTALLCONTEXT_MACHINE */

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer");
    lstrcatA(keypath, "\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udprod, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local UserData product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* InstallProperties key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(udprod, "Patches", 0, NULL, 0, access, NULL, &patches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(patches, patch_squashed, 0, NULL, 0, access, NULL, &hpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local product key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "Patches", 0, NULL, 0, access, NULL, &prodpatches, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(prodpatches, patch_squashed, 0, REG_SZ,
                         (const BYTE *)"transforms", 11);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* specific patch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer");
    lstrcatA(keypath, "\\UserData\\S-1-5-18\\Patches\\");
    lstrcatA(keypath, patch_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &udpatch, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* UserData Patches key exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    res = RegSetValueExA(udpatch, "LocalPackage", 0, REG_SZ,
                         (const BYTE *)"pack", 5);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LocalPatch value exists */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "transforms"), "Expected \"transforms\", got \"%s\"\n", val);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(prodpatches, patch_squashed);
    delete_key(prodpatches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodpatches);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_LOCALPACKAGEA, val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, "pack"), "Expected \"pack\", got \"%s\"\n", val);
    ok(size == 4, "Expected 4, got %d\n", size);

    /* UserData is sufficient for all properties
     * except INSTALLPROPERTY_TRANSFORMS
     */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = pMsiGetPatchInfoExA(patchcode, prodcode, NULL,
                            MSIINSTALLCONTEXT_MACHINE,
                            INSTALLPROPERTY_TRANSFORMSA, val, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(val, "apple"), "Expected \"apple\", got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    RegDeleteValueA(udpatch, "LocalPackage");
    delete_key(udpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udpatch);
    delete_key(hpatch, "", access & KEY_WOW64_64KEY);
    RegCloseKey(hpatch);
    delete_key(patches, "", access & KEY_WOW64_64KEY);
    RegCloseKey(patches);
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(udprod, "", access & KEY_WOW64_64KEY);
    RegCloseKey(udprod);
    LocalFree(usersid);
}