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
 int ERROR_NO_TOKEN ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int INSTALLSTATE_ABSENT ; 
 int INSTALLSTATE_ADVERTISED ; 
 int INSTALLSTATE_DEFAULT ; 
 int INSTALLSTATE_INVALIDARG ; 
 int INSTALLSTATE_UNKNOWN ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MsiQueryProductStateA (char*) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiQueryProductState(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    LPSTR usersid;
    INSTALLSTATE state;
    LONG res;
    HKEY userkey, localkey, props;
    HKEY prodkey;
    DWORD data, error;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(prodcode, prod_squashed);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* NULL prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(NULL);
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* empty prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA("");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* garbage prodcode */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA("garbage");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* guid without brackets */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D");
    error = GetLastError();
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* guid with brackets */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA("{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    /* same length as guid, but random */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA("A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93");
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == 0xdeadbeef, "expected 0xdeadbeef, got %u\n", error);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\");
    lstrcatA(keypath, prodcode);

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

    /* local uninstall key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    data = 1;
    res = RegSetValueExA(localkey, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* WindowsInstaller value exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    RegDeleteValueA(localkey, "WindowsInstaller");
    delete_key(localkey, "", access & KEY_WOW64_64KEY);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);

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

    /* local product key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    res = RegCreateKeyExA(localkey, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* install properties key exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    data = 1;
    res = RegSetValueExA(props, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* WindowsInstaller value exists */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_DEFAULT, "Expected INSTALLSTATE_DEFAULT, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    data = 2;
    res = RegSetValueExA(props, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* WindowsInstaller value is not 1 */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_DEFAULT, "Expected INSTALLSTATE_DEFAULT, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    RegDeleteKeyA(userkey, "");

    /* user product key does not exist */
    SetLastError(0xdeadbeef);
    state = MsiQueryProductStateA(prodcode);
    error = GetLastError();
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(error == ERROR_SUCCESS || broken(error == ERROR_NO_TOKEN) /* win2k */,
       "expected ERROR_SUCCESS, got %u\n", error);

    RegDeleteValueA(props, "WindowsInstaller");
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(localkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(localkey);
    RegDeleteKeyA(userkey, "");
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED,
       "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &localkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED,
       "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegCreateKeyExA(localkey, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED,
       "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    data = 1;
    res = RegSetValueExA(props, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* WindowsInstaller value exists */
    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_DEFAULT, "Expected INSTALLSTATE_DEFAULT, got %d\n", state);

    RegDeleteValueA(props, "WindowsInstaller");
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(localkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(localkey);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    /* MSIINSTALLCONTEXT_MACHINE */

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED, "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\");
    lstrcatA(keypath, "S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &localkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED,
       "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    res = RegCreateKeyExA(localkey, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_ADVERTISED,
       "Expected INSTALLSTATE_ADVERTISED, got %d\n", state);

    data = 1;
    res = RegSetValueExA(props, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&data, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* WindowsInstaller value exists */
    state = MsiQueryProductStateA(prodcode);
    ok(state == INSTALLSTATE_DEFAULT, "Expected INSTALLSTATE_DEFAULT, got %d\n", state);

    RegDeleteValueA(props, "WindowsInstaller");
    delete_key(props, "", access & KEY_WOW64_64KEY);
    RegCloseKey(props);
    delete_key(localkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(localkey);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    LocalFree(usersid);
}