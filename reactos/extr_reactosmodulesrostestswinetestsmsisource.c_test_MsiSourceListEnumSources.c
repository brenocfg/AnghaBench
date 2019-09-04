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
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PATCH ; 
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
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiSourceListEnumSourcesA (char*,char*,int /*<<< orphan*/ ,int,int,char*,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListEnumSources(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR value[MAX_PATH];
    LPSTR usersid;
    LONG res;
    UINT r;
    HKEY prodkey, userkey;
    HKEY url, net, source;
    DWORD size;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiSourceListEnumSourcesA)
    {
        win_skip("MsiSourceListEnumSourcesA is not available\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListEnumSourcesA tests\n");
        return;
    }

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* GetLastError is not set by the function */

    /* NULL szProductCodeOrPatchCode */
    size = 0xdeadbeef;
    r = pMsiSourceListEnumSourcesA(NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(size == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", size);

    /* empty szProductCodeOrPatchCode */
    size = 0xdeadbeef;
    r = pMsiSourceListEnumSourcesA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(size == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", size);

    /* garbage szProductCodeOrPatchCode */
    size = 0xdeadbeef;
    r = pMsiSourceListEnumSourcesA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(size == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", size);

    /* guid without brackets */
    size = 0xdeadbeef;
    r = pMsiSourceListEnumSourcesA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA",
                                   usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(size == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", size);

    /* guid with brackets */
    size = 0xdeadbeef;
    r = pMsiSourceListEnumSourcesA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                   usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(size == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", size);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyA(userkey, "SourceList", &source);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyA(source, "URL", &url);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* URL key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(url, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    res = RegSetValueExA(url, "2", 0, REG_SZ, (LPBYTE)"second", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    res = RegSetValueExA(url, "4", 0, REG_SZ, (LPBYTE)"fourth", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* try index 0 again */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* both szSource and pcchSource are NULL, index 0 */
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* both szSource and pcchSource are NULL, index 1 */
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 1, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* size is exactly 5 */
    size = 5;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* szSource is non-NULL while pcchSource is NULL */
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got %s\n", value);

    /* try index 1 after failure */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 1, value, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected \"aaa\", got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* reset the enumeration */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* try index 1 */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 1, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "second"), "Expected \"second\", got %s\n", value);
    ok(size == 6, "Expected 6, got %d\n", size);

    /* try index 1 again */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 1, value, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* try index 2 */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 2, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* try index < 0 */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, -1, value, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* NULL szUserSid */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* invalid dwOptions, must be one of MSICODE_ and MSISOURCETYPE_ */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* invalid dwOptions, must be one of MSICODE_ and MSISOURCETYPE_ */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PATCH, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* invalid dwOptions, must be one of MSICODE_ and MSISOURCETYPE_ */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSICODE_PATCH | MSISOURCETYPE_URL,
                                   0, value, &size);
    ok(r == ERROR_UNKNOWN_PATCH, "Expected ERROR_UNKNOWN_PATCH, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* invalid dwOptions, must be one of MSICODE_ and MSISOURCETYPE_ */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK | MSISOURCETYPE_URL,
                                   0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    RegDeleteValueA(url, "1");
    RegDeleteValueA(url, "2");
    RegDeleteValueA(url, "4");
    RegDeleteKeyA(url, "");
    RegCloseKey(url);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyA(source, "Net", &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Net key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(net, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    RegDeleteValueA(net, "1");
    RegDeleteKeyA(net, "");
    RegCloseKey(net);
    RegDeleteKeyA(source, "");
    RegCloseKey(source);
    RegDeleteKeyA(userkey, "");
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

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
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(userkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(source, "URL", 0, NULL, 0, access, NULL, &url, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* URL key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(url, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* NULL szUserSid */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    RegDeleteValueA(url, "1");
    delete_key(url, "", access);
    RegCloseKey(url);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(source, "Net", 0, NULL, 0, access, NULL, &net, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Net key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(net, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_USERMANAGED,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    RegDeleteValueA(net, "1");
    delete_key(net, "", access);
    RegCloseKey(net);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(userkey, "", access);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_MACHINE */

machine_tests:
    /* szUserSid is non-NULL */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, usersid,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    /* szUserSid is NULL */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        LocalFree(usersid);
        return;
    }

    /* user product key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(source, "URL", 0, NULL, 0, access, NULL, &url, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* URL key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(url, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    /* NULL szUserSid */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_URL, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    RegDeleteValueA(url, "1");
    delete_key(url, "", access);
    RegCloseKey(url);

    /* SourceList key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegCreateKeyExA(source, "Net", 0, NULL, 0, access, NULL, &net, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Net key exists */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(value, "aaa"), "Expected value to be unchanged, got %s\n", value);
    ok(size == MAX_PATH, "Expected MAX_PATH, got %d\n", size);

    res = RegSetValueExA(net, "1", 0, REG_SZ, (LPBYTE)"first", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* sources exist */
    size = MAX_PATH;
    lstrcpyA(value, "aaa");
    r = pMsiSourceListEnumSourcesA(prodcode, NULL,
                                   MSIINSTALLCONTEXT_MACHINE,
                                   MSICODE_PRODUCT | MSISOURCETYPE_NETWORK, 0, value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(value, "first"), "Expected \"first\", got %s\n", value);
    ok(size == 5, "Expected 5, got %d\n", size);

    RegDeleteValueA(net, "1");
    delete_key(net, "", access);
    RegCloseKey(net);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(prodkey, "", access);
    RegCloseKey(prodkey);
    LocalFree(usersid);
}