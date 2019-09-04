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
typedef  int REGSAM ;
typedef  char* LPSTR ;
typedef  int LONG ;
typedef  int INSTALLSTATE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_NO_TOKEN ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int INSTALLSTATE_ADVERTISED ; 
 int INSTALLSTATE_BADCONFIG ; 
 int INSTALLSTATE_INVALIDARG ; 
 int INSTALLSTATE_LOCAL ; 
 int INSTALLSTATE_SOURCE ; 
 int INSTALLSTATE_UNKNOWN ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MsiQueryFeatureStateA (char*,char*) ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  compose_base85_guid (char*,char*,char*) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiQueryFeatureState(void)
{
    HKEY userkey, localkey, compkey, compkey2;
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR component[MAX_PATH];
    CHAR comp_base85[MAX_PATH];
    CHAR comp_squashed[MAX_PATH], comp_squashed2[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    INSTALLSTATE state;
    LPSTR usersid;
    LONG res;
    REGSAM access = KEY_ALL_ACCESS;
    DWORD error;

    create_test_guid(prodcode, prod_squashed);
    compose_base85_guid(component, comp_base85, comp_squashed);
    compose_base85_guid(component, comp_base85 + 20, comp_squashed2);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* NULL prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(NULL, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* empty prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA("", "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* garbage prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA("garbage", "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* guid without brackets */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D", "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* guid with brackets */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA("{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}", "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_ALREADY_EXISTS) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    /* same length as guid, but random */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA("A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93", "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* NULL szFeature */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, NULL);
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* empty szFeature */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    /* feature key does not exist yet */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Features\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(userkey, "feature", 0, REG_SZ, (const BYTE *)"", 2);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature value exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\Features");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &localkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        RegDeleteKeyA(userkey, "");
        RegCloseKey(userkey);
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* userdata features key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaa", 20);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_BADCONFIG, "Expected INSTALLSTATE_BADCONFIG, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaa", 21);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaaa", 22);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)comp_base85, 41);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed2);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey2, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"", 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"apple", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey2, prod_squashed, 0, REG_SZ, (const BYTE *)"orange", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLSTATE_LOCAL */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"01\\", 4);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLSTATE_SOURCE */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_SOURCE, "Expected INSTALLSTATE_SOURCE, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"01", 3);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* bad INSTALLSTATE_SOURCE */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"01a", 4);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* INSTALLSTATE_SOURCE */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_SOURCE, "Expected INSTALLSTATE_SOURCE, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"01", 3);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* bad INSTALLSTATE_SOURCE */
    SetLastError(0xdeadbeef);
    state = MsiQueryFeatureStateA(prodcode, "feature");
    error = GetLastError();
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteValueA(compkey2, prod_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    delete_key(compkey2, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(localkey, "feature");
    RegDeleteValueA(userkey, "feature");
    RegDeleteKeyA(userkey, "");
    RegCloseKey(compkey);
    RegCloseKey(compkey2);
    RegCloseKey(localkey);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Features\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature key exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);

    res = RegSetValueExA(userkey, "feature", 0, REG_SZ, (const BYTE *)"", 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature value exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\Features");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &localkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* userdata features key exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaa", 20);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_BADCONFIG, "Expected INSTALLSTATE_BADCONFIG, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaa", 21);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaaa", 22);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)comp_base85, 41);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed2);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey2, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"", 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"apple", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey2, prod_squashed, 0, REG_SZ, (const BYTE *)"orange", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);

    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteValueA(compkey2, prod_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    delete_key(compkey2, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(localkey, "feature");
    RegDeleteValueA(userkey, "feature");
    delete_key(userkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);
    RegCloseKey(compkey2);
    RegCloseKey(localkey);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_MACHINE */

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Features\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature key exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);

    res = RegSetValueExA(userkey, "feature", 0, REG_SZ, (const BYTE *)"", 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* feature value exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, "S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\Features");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &localkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* userdata features key exists */
    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaa", 20);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_BADCONFIG, "Expected INSTALLSTATE_BADCONFIG, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaa", 21);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)"aaaaaaaaaaaaaaaaaaaaa", 22);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(localkey, "feature", 0, REG_SZ, (const BYTE *)comp_base85, 41);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, "S-1-5-18\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, "S-1-5-18\\Components\\");
    lstrcatA(keypath, comp_squashed2);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey2, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"", 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"apple", 6);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegSetValueExA(compkey2, prod_squashed, 0, REG_SZ, (const BYTE *)"orange", 7);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryFeatureStateA(prodcode, "feature");
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);

    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteValueA(compkey2, prod_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    delete_key(compkey2, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(localkey, "feature");
    RegDeleteValueA(userkey, "feature");
    delete_key(userkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);
    RegCloseKey(compkey2);
    RegCloseKey(localkey);
    RegCloseKey(userkey);
    LocalFree(usersid);
}