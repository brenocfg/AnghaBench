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
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int ERROR_ACCESS_DENIED ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int INSTALLSTATE_ABSENT ; 
 int INSTALLSTATE_INVALIDARG ; 
 int INSTALLSTATE_LOCAL ; 
 int INSTALLSTATE_MOREDATA ; 
 int INSTALLSTATE_UNKNOWN ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MsiGetComponentPathA (char*,char*,char*,int*) ; 
 int MsiLocateComponentA (char*,char*,int*) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  compose_base85_guid (char*,char*,char*) ; 
 int /*<<< orphan*/  create_file (char*,char*,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiGetComponentPath(void)
{
    HKEY compkey, prodkey, installprop;
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR component[MAX_PATH];
    CHAR comp_base85[MAX_PATH];
    CHAR comp_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH];
    CHAR path[MAX_PATH];
    INSTALLSTATE state;
    LPSTR usersid;
    DWORD size, val;
    REGSAM access = KEY_ALL_ACCESS;
    LONG res;

    create_test_guid(prodcode, prod_squashed);
    compose_base85_guid(component, comp_base85, comp_squashed);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* NULL szProduct */
    size = MAX_PATH;
    state = MsiGetComponentPathA(NULL, component, path, &size);
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* NULL szComponent */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, NULL, path, &size);
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(NULL, path, &size);
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* NULL lpPathBuf */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, NULL, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, NULL, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* NULL pcchBuf */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, NULL);
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, NULL);
    ok(state == INSTALLSTATE_INVALIDARG, "Expected INSTALLSTATE_INVALIDARG, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* all params valid */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local system component key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\InstallProperties");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &installprop, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    val = 1;
    res = RegSetValueExA(installprop, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&val, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* install properties key exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    create_file("C:\\imapath", "C:\\imapath", 11);

    /* file exists */
    path[0] = 'a';
    size = 0;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_MOREDATA, "Expected INSTALLSTATE_MOREDATA, got %d\n", state);
    ok(path[0] == 'a', "got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    size = 0;
    path[0] = 'a';
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_MOREDATA, "Expected INSTALLSTATE_MOREDATA, got %d\n", state);
    ok(path[0] == 'a', "got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(compkey, prod_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(installprop, "WindowsInstaller");
    delete_key(installprop, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);
    RegCloseKey(installprop);
    DeleteFileA("C:\\imapath");

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed component key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\InstallProperties");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &installprop, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    val = 1;
    res = RegSetValueExA(installprop, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&val, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* install properties key exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    create_file("C:\\imapath", "C:\\imapath", 11);

    /* file exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(compkey, prod_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(installprop, "WindowsInstaller");
    delete_key(installprop, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);
    RegCloseKey(installprop);
    DeleteFileA("C:\\imapath");

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed product key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed component key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);
    lstrcatA(keypath, "\\InstallProperties");

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &installprop, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    val = 1;
    res = RegSetValueExA(installprop, "WindowsInstaller", 0, REG_DWORD, (const BYTE *)&val, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* install properties key exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    create_file("C:\\imapath", "C:\\imapath", 11);

    /* file exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(compkey, prod_squashed);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegDeleteValueA(installprop, "WindowsInstaller");
    delete_key(installprop, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    RegCloseKey(compkey);
    RegCloseKey(installprop);
    DeleteFileA("C:\\imapath");

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &prodkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user unmanaged product key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user unmanaged component key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    create_file("C:\\imapath", "C:\\imapath", 11);

    /* file exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteKeyA(prodkey, "");
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    RegCloseKey(compkey);
    DeleteFileA("C:\\imapath");

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local classes product key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local user component key exists */
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_UNKNOWN, "Expected INSTALLSTATE_UNKNOWN, got %d\n", state);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_ABSENT, "Expected INSTALLSTATE_ABSENT, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    create_file("C:\\imapath", "C:\\imapath", 11);

    /* file exists */
    path[0] = 0;
    size = MAX_PATH;
    state = MsiGetComponentPathA(prodcode, component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    path[0] = 0;
    size = MAX_PATH;
    state = MsiLocateComponentA(component, path, &size);
    ok(state == INSTALLSTATE_LOCAL, "Expected INSTALLSTATE_LOCAL, got %d\n", state);
    ok(!lstrcmpA(path, "C:\\imapath"), "Expected C:\\imapath, got %s\n", path);
    ok(size == 10, "Expected 10, got %d\n", size);

    RegDeleteValueA(compkey, prod_squashed);
    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    RegCloseKey(compkey);
    DeleteFileA("C:\\imapath");
    LocalFree(usersid);
}