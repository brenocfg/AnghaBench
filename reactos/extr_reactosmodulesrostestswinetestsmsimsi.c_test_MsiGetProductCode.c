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
typedef  int /*<<< orphan*/  UINT ;
typedef  int REGSAM ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  ERROR_UNKNOWN_COMPONENT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiGetProductCodeA (char*,char*) ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  compose_base85_guid (char*,char*,char*) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_MsiGetProductCode(void)
{
    HKEY compkey, prodkey;
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR prodcode2[MAX_PATH];
    CHAR prod2_squashed[MAX_PATH];
    CHAR component[MAX_PATH];
    CHAR comp_base85[MAX_PATH];
    CHAR comp_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH];
    CHAR product[MAX_PATH];
    LPSTR usersid;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(prodcode, prod_squashed);
    create_test_guid(prodcode2, prod2_squashed);
    compose_base85_guid(component, comp_base85, comp_squashed);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* szComponent is NULL */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(NULL, product);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* szComponent is empty */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA("", product);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* garbage szComponent */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA("garbage", product);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* guid without brackets */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D", product);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* guid with brackets */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA("{6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D}", product);
    ok(r == ERROR_UNKNOWN_COMPONENT, "Expected ERROR_UNKNOWN_COMPONENT, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* same length as guid, but random */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA("A938G02JF-2NF3N93-VN3-2NNF-3KGKALDNF93", product);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    /* all params correct, szComponent not published */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_UNKNOWN_COMPONENT, "Expected ERROR_UNKNOWN_COMPONENT, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user unmanaged component key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_UNKNOWN_COMPONENT, "Expected ERROR_UNKNOWN_COMPONENT, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    res = RegSetValueExA(compkey, prod2_squashed, 0, REG_SZ, (const BYTE *)"C:\\another", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed product key of first product exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &prodkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user unmanaged product key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    RegDeleteKeyA(prodkey, "");
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local classes product key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod2_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed product key of second product exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode2), "Expected %s, got %s\n", prodcode2, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteValueA(compkey, prod2_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Components\\");
    lstrcatA(keypath, comp_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &compkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local user component key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_UNKNOWN_COMPONENT, "Expected ERROR_UNKNOWN_COMPONENT, got %d\n", r);
    ok(!lstrcmpA(product, "prod"), "Expected product to be unchanged, got %s\n", product);

    res = RegSetValueExA(compkey, prod_squashed, 0, REG_SZ, (const BYTE *)"C:\\imapath", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* product value exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    res = RegSetValueExA(compkey, prod2_squashed, 0, REG_SZ, (const BYTE *)"C:\\another", 10);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed product key of first product exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &prodkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user unmanaged product key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    RegDeleteKeyA(prodkey, "");
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* local classes product key exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode), "Expected %s, got %s\n", prodcode, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod2_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user managed product key of second product exists */
    lstrcpyA(product, "prod");
    r = MsiGetProductCodeA(component, product);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(product, prodcode2), "Expected %s, got %s\n", prodcode2, product);

    delete_key(prodkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(prodkey);
    RegDeleteValueA(compkey, prod_squashed);
    RegDeleteValueA(compkey, prod2_squashed);
    delete_key(compkey, "", access & KEY_WOW64_64KEY);
    RegCloseKey(compkey);
    LocalFree(usersid);
}