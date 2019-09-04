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
typedef  int /*<<< orphan*/  REGSAM ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSICODE_PATCH ; 
 int MSICODE_PRODUCT ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERMANAGED ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int MSISOURCETYPE_NETWORK ; 
 int MSISOURCETYPE_URL ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiSourceListAddSourceExA (char*,char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListAddSourceEx(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR value[MAX_PATH];
    LPSTR usersid;
    LONG res;
    UINT r;
    HKEY prodkey, userkey, hkey, url, net;
    DWORD size;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiSourceListAddSourceExA)
    {
        win_skip("Skipping MsiSourceListAddSourceExA tests\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListAddSourceExA tests\n");
        return;
    }

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* GetLastError is not set by the function */

    /* NULL szProductCodeOrPatchCode */
    r = pMsiSourceListAddSourceExA(NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szProductCodeOrPatchCode */
    r = pMsiSourceListAddSourceExA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* garbage szProductCodeOrPatchCode */
    r = pMsiSourceListAddSourceExA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid without brackets */
    r = pMsiSourceListAddSourceExA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA", usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid with brackets */
    r = pMsiSourceListAddSourceExA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}", usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyA(userkey, "SourceList", &url);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    RegCloseKey(url);

    /* SourceList key exists */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    res = RegOpenKeyA(userkey, "SourceList\\URL", &url);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    /* add another source, index 0 */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "another", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "another/"), "Expected 'another/', got %s\n", value);
    ok(size == 9, "Expected 9, got %d\n", size);

    /* add another source, index 1 */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "third/", 1);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "third/"), "Expected 'third/', got %s\n", value);
    ok(size == 7, "Expected 7, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "3", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "another/"), "Expected 'another/', got %s\n", value);
    ok(size == 9, "Expected 9, got %d\n", size);

    /* add another source, index > N */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "last/", 5);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "third/"), "Expected 'third/', got %s\n", value);
    ok(size == 7, "Expected 7, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "3", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "another/"), "Expected 'another/', got %s\n", value);
    ok(size == 9, "Expected 9, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "4", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "last/"), "Expected 'last/', got %s\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    /* just MSISOURCETYPE_NETWORK */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSISOURCETYPE_NETWORK, "source", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    res = RegOpenKeyA(userkey, "SourceList\\Net", &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    size = MAX_PATH;
    res = RegQueryValueExA(net, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "source\\"), "Expected 'source\\', got %s\n", value);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* just MSISOURCETYPE_URL */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSISOURCETYPE_URL, "source", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "third/"), "Expected 'third/', got %s\n", value);
    ok(size == 7, "Expected 7, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "3", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "another/"), "Expected 'another/', got %s\n", value);
    ok(size == 9, "Expected 9, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "4", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "last/"), "Expected 'last/', got %s\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "5", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "source/"), "Expected 'source/', got %s\n", value);
    ok(size == 8, "Expected 8, got %d\n", size);

    /* NULL szUserSid */
    r = pMsiSourceListAddSourceExA(prodcode, NULL,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSISOURCETYPE_NETWORK, "nousersid", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    res = RegQueryValueExA(net, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "source\\"), "Expected 'source\\', got %s\n", value);
    ok(size == 8, "Expected 8, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(net, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "nousersid\\"), "Expected 'nousersid\\', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    /* invalid options, must have source type */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PRODUCT, "source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSICODE_PATCH, "source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* NULL szSource */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSISOURCETYPE_URL, NULL, 1);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szSource */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERUNMANAGED,
                                  MSISOURCETYPE_URL, "", 1);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* MSIINSTALLCONTEXT_USERMANAGED, non-NULL szUserSid */

    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        goto machine_tests;
    }

    /* product key exists */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &hkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    RegCloseKey(hkey);

    /* SourceList exists */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_USERMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    res = RegOpenKeyExA(prodkey, "SourceList\\URL", 0, access, &url);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    RegCloseKey(url);

    /* MSIINSTALLCONTEXT_USERMANAGED, NULL szUserSid */

    r = pMsiSourceListAddSourceExA(prodcode, NULL,
                                  MSIINSTALLCONTEXT_USERMANAGED,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "another", 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    res = RegOpenKeyExA(prodkey, "SourceList\\URL", 0, access, &url);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
    ok(size == 11, "Expected 11, got %d\n", size);

    size = MAX_PATH;
    res = RegQueryValueExA(url, "2", NULL, NULL, (LPBYTE)value, &size);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    ok(!lstrcmpA(value, "another/"), "Expected 'another/', got %s\n", value);
    ok(size == 9, "Expected 9, got %d\n", size);

    RegCloseKey(url);
    RegCloseKey(prodkey);

    /* MSIINSTALLCONTEXT_MACHINE */

machine_tests:
    /* szUserSid must be NULL for MSIINSTALLCONTEXT_MACHINE */
    r = pMsiSourceListAddSourceExA(prodcode, usersid,
                                  MSIINSTALLCONTEXT_MACHINE,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    r = pMsiSourceListAddSourceExA(prodcode, NULL,
                                  MSIINSTALLCONTEXT_MACHINE,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        LocalFree(usersid);
        return;
    }

    /* product key exists */
    r = pMsiSourceListAddSourceExA(prodcode, NULL,
                                  MSIINSTALLCONTEXT_MACHINE,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &hkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
    RegCloseKey(hkey);

    /* SourceList exists */
    r = pMsiSourceListAddSourceExA(prodcode, NULL,
                                  MSIINSTALLCONTEXT_MACHINE,
                                  MSICODE_PRODUCT | MSISOURCETYPE_URL, "C:\\source", 0);
    if (r == ERROR_ACCESS_DENIED)
        skip("MsiSourceListAddSourceEx (insufficient privileges)\n");
    else
    {
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

        res = RegOpenKeyExA(prodkey, "SourceList\\URL", 0, access, &url);
        ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

        size = MAX_PATH;
        res = RegQueryValueExA(url, "1", NULL, NULL, (LPBYTE)value, &size);
        ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);
        ok(!lstrcmpA(value, "C:\\source/"), "Expected 'C:\\source/', got %s\n", value);
        ok(size == 11, "Expected 11, got %d\n", size);

        RegCloseKey(url);
        RegCloseKey(prodkey);
    }
    LocalFree(usersid);
}