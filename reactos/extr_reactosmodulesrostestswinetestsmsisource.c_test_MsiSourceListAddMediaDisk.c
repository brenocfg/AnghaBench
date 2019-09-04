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
typedef  int /*<<< orphan*/  REGSAM ;
typedef  char* LPSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_STR (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_BAD_CONFIGURATION ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSICODE_PRODUCT ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERMANAGED ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int MSISOURCETYPE_MEDIA ; 
 int MSISOURCETYPE_NETWORK ; 
 int MSISOURCETYPE_URL ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pMsiSourceListAddMediaDiskA (char*,char*,int /*<<< orphan*/ ,int,int,char*,char*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListAddMediaDisk(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    HKEY prodkey, userkey;
    HKEY media, source;
    LPSTR usersid;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiSourceListAddMediaDiskA)
    {
        win_skip("MsiSourceListAddMediaDiskA is not available\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListAddMediaDiskA tests\n");
        return;
    }

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* GetLastError is not set by the function */

    /* NULL szProductCodeOrPatchCode */
    r = pMsiSourceListAddMediaDiskA(NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szProductCodeOrPatchCode */
    r = pMsiSourceListAddMediaDiskA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* garbage szProductCodeOrPatchCode */
    r = pMsiSourceListAddMediaDiskA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid without brackets */
    r = pMsiSourceListAddMediaDiskA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA",
                                    usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid with brackets */
    r = pMsiSourceListAddMediaDiskA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                    usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* dwOptions has MSISOURCETYPE_NETWORK */
    r = pMsiSourceListAddMediaDiskA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                    usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT | MSISOURCETYPE_NETWORK,
                                    1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* dwOptions has MSISOURCETYPE_URL */
    r = pMsiSourceListAddMediaDiskA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                    usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT | MSISOURCETYPE_URL,
                                    1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* dwOptions has MSISOURCETYPE_MEDIA */
    r = pMsiSourceListAddMediaDiskA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                    usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT | MSISOURCETYPE_MEDIA,
                                    1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyA(userkey, "SourceList", &source);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Media subkey is created by MsiSourceListAddMediaDisk */
    res = RegOpenKeyA(source, "Media", &media);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(media, "1", "label;prompt");

    /* dwDiskId is random */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 42, "label42", "prompt42");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "1", "label;prompt");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* dwDiskId is 0 */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 0, "label0", "prompt0");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", "label;prompt");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* dwDiskId is < 0 */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, -1, "label-1", "prompt-1");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "-1", "label-1;prompt-1");
    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", "label;prompt");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* update dwDiskId 1 */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "newlabel", "newprompt");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "-1", "label-1;prompt-1");
    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", "newlabel;newprompt");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* update dwDiskId 1, szPrompt is NULL */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "etiqueta", NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "-1", "label-1;prompt-1");
    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", "etiqueta;");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* update dwDiskId 1, szPrompt is empty */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "etikett", "");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* update dwDiskId 1, szVolumeLabel is NULL */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, NULL, "provocar");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "-1", "label-1;prompt-1");
    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", ";provocar");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    /* update dwDiskId 1, szVolumeLabel is empty */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, "", "provoquer");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* szUserSid is NULL */
    r = pMsiSourceListAddMediaDiskA(prodcode, NULL,
                                    MSIINSTALLCONTEXT_USERUNMANAGED,
                                    MSICODE_PRODUCT, 1, NULL, "provoquer");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(media, "-1", "label-1;prompt-1");
    CHECK_REG_STR(media, "0", "label0;prompt0");
    CHECK_REG_STR(media, "1", ";provoquer");
    CHECK_REG_STR(media, "42", "label42;prompt42");

    RegDeleteValueA(media, "-1");
    RegDeleteValueA(media, "0");
    RegDeleteValueA(media, "1");
    RegDeleteValueA(media, "42");
    RegDeleteKeyA(media, "");
    RegCloseKey(media);
    RegDeleteKeyA(source, "");
    RegCloseKey(source);
    RegDeleteKeyA(userkey, "");
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        goto machine_tests;
    }

    /* user product key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(userkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_USERMANAGED,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Media subkey is created by MsiSourceListAddMediaDisk */
    res = RegOpenKeyExA(source, "Media", 0, access, &media);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(media, "1", "label;prompt");

    RegDeleteValueA(media, "1");
    delete_key(media, "", access);
    RegCloseKey(media);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(userkey, "", access);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_MACHINE */

machine_tests:
    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        LocalFree(usersid);
        return;
    }

    /* machine product key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, NULL,
                                    MSIINSTALLCONTEXT_MACHINE,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddMediaDiskA(prodcode, NULL,
                                    MSIINSTALLCONTEXT_MACHINE,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    if (r == ERROR_ACCESS_DENIED)
    {
        skip("MsiSourceListAddMediaDisk (insufficient privileges)\n");
        goto done;
    }
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Media subkey is created by MsiSourceListAddMediaDisk */
    res = RegOpenKeyExA(source, "Media", 0, access, &media);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(media, "1", "label;prompt");

    /* szUserSid is non-NULL */
    r = pMsiSourceListAddMediaDiskA(prodcode, usersid,
                                    MSIINSTALLCONTEXT_MACHINE,
                                    MSICODE_PRODUCT, 1, "label", "prompt");
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    RegDeleteValueA(media, "1");
    delete_key(media, "", access);
    RegCloseKey(media);

done:
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(prodkey, "", access);
    RegCloseKey(prodkey);
    LocalFree(usersid);
}