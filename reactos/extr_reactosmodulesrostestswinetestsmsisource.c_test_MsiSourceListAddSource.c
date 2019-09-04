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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_STR (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_BAD_CONFIGURATION ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  GetComputerNameA (char*,int*) ; 
 int /*<<< orphan*/  GetUserNameA (char*,int*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NameSamCompatible ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pGetUserNameExA (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ pMsiSourceListAddSourceA (char*,char*,int,char*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListAddSource(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR username[MAX_PATH];
    LPSTR usersid, ptr;
    LONG res;
    UINT r;
    HKEY prodkey, userkey, net, source;
    DWORD size;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiSourceListAddSourceA)
    {
        win_skip("Skipping MsiSourceListAddSourceA tests\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListAddSourceA tests\n");
        return;
    }

    /* MACHINENAME\username */
    size = MAX_PATH;
    if (pGetUserNameExA != NULL)
        pGetUserNameExA(NameSamCompatible, username, &size);
    else
    {
        GetComputerNameA(username, &size);
        lstrcatA(username, "\\");
        ptr = username + lstrlenA(username);
        size = MAX_PATH - (ptr - username);
        GetUserNameA(ptr, &size);
    }
    trace("username: %s\n", username);

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* GetLastError is not set by the function */

    /* NULL szProduct */
    r = pMsiSourceListAddSourceA(NULL, username, 0, "source");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szProduct */
    r = pMsiSourceListAddSourceA("", username, 0, "source");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* garbage szProduct */
    r = pMsiSourceListAddSourceA("garbage", username, 0, "source");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid without brackets */
    r = pMsiSourceListAddSourceA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA", username, 0, "source");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid with brackets */
    r = pMsiSourceListAddSourceA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}", username, 0, "source");
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* dwReserved is not 0 */
    r = pMsiSourceListAddSourceA(prodcode, username, 42, "source");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* szSource is NULL */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* szSource is empty */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "");
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        goto userunmanaged_tests;
    }

    /* user product key exists */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(userkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Net key is created */
    res = RegOpenKeyExA(source, "Net", 0, access, &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LastUsedSource does not exist and it is not created */
    res = RegQueryValueExA(source, "LastUsedSource", 0, NULL, NULL, NULL);
    ok(res == ERROR_FILE_NOT_FOUND, "Expected ERROR_FILE_NOT_FOUND, got %d\n", res);

    CHECK_REG_STR(net, "1", "source\\");

    RegDeleteValueA(net, "1");
    delete_key(net, "", access);
    RegCloseKey(net);

    res = RegSetValueExA(source, "LastUsedSource", 0, REG_SZ, (LPBYTE)"blah", 5);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LastUsedSource value exists */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Net key is created */
    res = RegOpenKeyExA(source, "Net", 0, access, &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(source, "LastUsedSource", "blah");
    CHECK_REG_STR(net, "1", "source\\");

    RegDeleteValueA(net, "1");
    delete_key(net, "", access);
    RegCloseKey(net);

    res = RegSetValueExA(source, "LastUsedSource", 0, REG_SZ, (LPBYTE)"5", 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LastUsedSource is an integer */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Net key is created */
    res = RegOpenKeyExA(source, "Net", 0, access, &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(source, "LastUsedSource", "5");
    CHECK_REG_STR(net, "1", "source\\");

    /* Add a second source, has trailing backslash */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "another\\");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(source, "LastUsedSource", "5");
    CHECK_REG_STR(net, "1", "source\\");
    CHECK_REG_STR(net, "2", "another\\");

    res = RegSetValueExA(source, "LastUsedSource", 0, REG_SZ, (LPBYTE)"2", 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* LastUsedSource is in the source list */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "third/");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(source, "LastUsedSource", "2");
    CHECK_REG_STR(net, "1", "source\\");
    CHECK_REG_STR(net, "2", "another\\");
    CHECK_REG_STR(net, "3", "third/\\");

    RegDeleteValueA(net, "1");
    RegDeleteValueA(net, "2");
    RegDeleteValueA(net, "3");
    delete_key(net, "", access);
    RegCloseKey(net);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(userkey, "", access);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

userunmanaged_tests:
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_UNKNOWN_PRODUCT, "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        goto machine_tests;
    }

    /* user product key exists */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyA(userkey, "SourceList", &source);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddSourceA(prodcode, username, 0, "source");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Net key is created */
    res = RegOpenKeyA(source, "Net", &net);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(net, "1", "source\\");

    RegDeleteValueA(net, "1");
    RegDeleteKeyA(net, "");
    RegCloseKey(net);
    RegDeleteKeyA(source, "");
    RegCloseKey(source);
    RegDeleteKeyA(userkey, "");
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_MACHINE */

machine_tests:
    r = pMsiSourceListAddSourceA(prodcode, NULL, 0, "source");
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

    /* machine product key exists */
    r = pMsiSourceListAddSourceA(prodcode, NULL, 0, "source");
    ok(r == ERROR_BAD_CONFIGURATION, "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    r = pMsiSourceListAddSourceA(prodcode, NULL, 0, "source");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* Net key is created */
    res = RegOpenKeyExA(source, "Net", 0, access, &net);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("MsiSourceListAddSource (insufficient privileges)\n");
        goto done;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    CHECK_REG_STR(net, "1", "source\\");

    /* empty szUserName */
    r = pMsiSourceListAddSourceA(prodcode, "", 0, "another");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    CHECK_REG_STR(net, "1", "source\\");
    CHECK_REG_STR(net, "2", "another\\");

    RegDeleteValueA(net, "2");
    RegDeleteValueA(net, "1");
    delete_key(net, "", access);
    RegCloseKey(net);

done:
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(prodkey, "", access);
    RegCloseKey(prodkey);
    LocalFree(usersid);
}