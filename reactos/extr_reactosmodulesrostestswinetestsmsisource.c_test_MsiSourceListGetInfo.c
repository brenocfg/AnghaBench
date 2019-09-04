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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  char* LPCSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PATCH ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int ERROR_UNKNOWN_PROPERTY ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 char* INSTALLPROPERTY_DISKPROMPTA ; 
 char* INSTALLPROPERTY_LASTUSEDSOURCEA ; 
 char* INSTALLPROPERTY_LASTUSEDTYPEA ; 
 char* INSTALLPROPERTY_MEDIAPACKAGEPATHA ; 
 char* INSTALLPROPERTY_PACKAGENAMEA ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MSICODE_PATCH ; 
 int MSICODE_PRODUCT ; 
 int MSIINSTALLCONTEXT_ALL ; 
 int MSIINSTALLCONTEXT_ALLUSERMANAGED ; 
 int MSIINSTALLCONTEXT_NONE ; 
 int MSIINSTALLCONTEXT_USERMANAGED ; 
 int MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  get_user_sid () ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 scalar_t__ lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiSourceListGetInfoA (char*,int /*<<< orphan*/ ,int,int,char*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListGetInfo(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR value[MAX_PATH];
    LPSTR usersid;
    LPCSTR data;
    LONG res;
    UINT r;
    HKEY userkey, hkey, media;
    DWORD size;

    if (!pMsiSourceListGetInfoA)
    {
        win_skip("Skipping MsiSourceListGetInfoA tests\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListGetInfoA tests\n");
        return;
    }

    /* NULL szProductCodeOrPatchCode */
    r = pMsiSourceListGetInfoA(NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szProductCodeOrPatchCode */
    r = pMsiSourceListGetInfoA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* garbage szProductCodeOrPatchCode */
    r = pMsiSourceListGetInfoA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid without brackets */
    r = pMsiSourceListGetInfoA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid with brackets */
    r = pMsiSourceListGetInfoA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* same length as guid, but random */
    r = pMsiSourceListGetInfoA("ADKD-2KSDFF2-DKK1KNFJASD9GLKWME-1I3KAD", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* invalid context */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_NONE,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* another invalid context */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_ALLUSERMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* yet another invalid context */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_ALL,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* mix two valid contexts */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED | MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* invalid option */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              4, INSTALLPROPERTY_PACKAGENAMEA, NULL, NULL);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* NULL property */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, NULL, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty property */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, "", NULL, NULL);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* value is non-NULL while size is NULL */
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, value, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* size is non-NULL while value is NULL */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT || r == ERROR_INVALID_PARAMETER,
      "Expected ERROR_UNKNOWN_PRODUCT or ERROR_INVALID_PARAMETER, got %d\n", r);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    res = RegCreateKeyA(userkey, "SourceList", &hkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == 0, "Expected 0, got %d\n", size);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);

    data = "msitest.msi";
    res = RegSetValueExA(hkey, "PackageName", 0, REG_SZ, (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* PackageName value exists */
    size = 0xdeadbeef;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, NULL, &size);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER,
	   "Expected ERROR_SUCCESS or ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(size == 11 || r != ERROR_SUCCESS, "Expected 11, got %d\n", size);

    /* read the value, don't change size */
	size = 11;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected 'aaa', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    /* read the value, fix size */
    size++;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "msitest.msi"), "Expected 'msitest.msi', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    /* empty property now that product key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, "", value, &size);
    ok(r == ERROR_UNKNOWN_PROPERTY, "Expected ERROR_UNKNOWN_PROPERTY, got %d\n", r);
    ok(size == MAX_PATH, "Expected %d, got %d\n", MAX_PATH, size);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    /* nonexistent property now that product key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, "nonexistent", value, &size);
    ok(r == ERROR_UNKNOWN_PROPERTY, "Expected ERROR_UNKNOWN_PROPERTY, got %d\n", r);
    ok(size == MAX_PATH, "Expected %d, got %d\n", MAX_PATH, size);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    data = "tester";
    res = RegSetValueExA(hkey, "nonexistent", 0, REG_SZ, (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* nonexistent property now that nonexistent value exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PRODUCT, "nonexistent", value, &size);
    ok(r == ERROR_UNKNOWN_PROPERTY, "Expected ERROR_UNKNOWN_PROPERTY, got %d\n", r);
    ok(size == MAX_PATH, "Expected %d, got %d\n", MAX_PATH, size);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    /* invalid option now that product key exists */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              4, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == 11, "Expected 11, got %d\n", size);

    /* INSTALLPROPERTY_MEDIAPACKAGEPATH, media key does not exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_MEDIAPACKAGEPATHA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);
    ok(size == 0, "Expected 0, got %d\n", size);

    res = RegCreateKeyA(hkey, "Media", &media);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    data = "path";
    res = RegSetValueExA(media, "MediaPackage", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_MEDIAPACKAGEPATH */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_MEDIAPACKAGEPATHA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "path"), "Expected \"path\", got \"%s\"\n", value);
    ok(size == 4, "Expected 4, got %d\n", size);

    /* INSTALLPROPERTY_DISKPROMPT */
    data = "prompt";
    res = RegSetValueExA(media, "DiskPrompt", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_DISKPROMPTA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "prompt"), "Expected \"prompt\", got \"%s\"\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    data = "";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDSOURCE, source is empty */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);
    ok(size == 0, "Expected 0, got %d\n", size);

    data = "source";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDSOURCE */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "source"), "Expected \"source\", got \"%s\"\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    /* INSTALLPROPERTY_LASTUSEDSOURCE, size is too short */
    size = 4;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got \"%s\"\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    /* INSTALLPROPERTY_LASTUSEDSOURCE, size is exactly 6 */
    size = 6;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got \"%s\"\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    data = "a;source";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDSOURCE, one semi-colon */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "source"), "Expected \"source\", got \"%s\"\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    data = "a:source";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDSOURCE, one colon */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDSOURCEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "a:source"), "Expected \"a:source\", got \"%s\"\n", value);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* INSTALLPROPERTY_LASTUSEDTYPE, invalid source format */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);
    ok(size == 0, "Expected 0, got %d\n", size);

    data = "x;y;z";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDTYPE, invalid source format */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);
    ok(size == 0, "Expected 0, got %d\n", size);

    data = "n;y;z";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDTYPE */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "n"), "Expected \"n\", got \"%s\"\n", value);
    ok(size == 1, "Expected 1, got %d\n", size);

    data = "negatory";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDTYPE */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "n"), "Expected \"n\", got \"%s\"\n", value);
    ok(size == 1, "Expected 1, got %d\n", size);

    data = "megatron";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDTYPE */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "m"), "Expected \"m\", got \"%s\"\n", value);
    ok(size == 1, "Expected 1, got %d\n", size);

    data = "useless";
    res = RegSetValueExA(hkey, "LastUsedSource", 0, REG_SZ,
                         (const BYTE *)data, lstrlenA(data) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLPROPERTY_LASTUSEDTYPE */
    size = MAX_PATH;
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                               MSICODE_PRODUCT, INSTALLPROPERTY_LASTUSEDTYPEA,
                               value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "u"), "Expected \"u\", got \"%s\"\n", value);
    ok(size == 1, "Expected 1, got %d\n", size);

    RegDeleteValueA(media, "MediaPackage");
    RegDeleteValueA(media, "DiskPrompt");
    RegDeleteKeyA(media, "");
    RegDeleteValueA(hkey, "LastUsedSource");
    RegDeleteValueA(hkey, "nonexistent");
    RegDeleteValueA(hkey, "PackageName");
    RegDeleteKeyA(hkey, "");
    RegDeleteKeyA(userkey, "");
    RegCloseKey(hkey);
    RegCloseKey(userkey);

    /* try a patch */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PATCH, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(size == MAX_PATH, "Expected %d, got %d\n", MAX_PATH, size);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Patches\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* patch key exists
     * NOTE: using prodcode guid, but it really doesn't matter
     */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PATCH, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(size == MAX_PATH, "Expected %d, got %d\n", MAX_PATH, size);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got \"%s\"\n", value);

    res = RegCreateKeyA(userkey, "SourceList", &hkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListGetInfoA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                              MSICODE_PATCH, INSTALLPROPERTY_PACKAGENAMEA, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, ""), "Expected \"\", got \"%s\"\n", value);
    ok(size == 0, "Expected 0, got %d\n", size);

    RegDeleteKeyA(hkey, "");
    RegDeleteKeyA(userkey, "");
    RegCloseKey(hkey);
    RegCloseKey(userkey);
    LocalFree(usersid);
}