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
typedef  int REGSAM ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ALL_ACCESS ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 scalar_t__ MsiEnumProductsA (int,char*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_MsiEnumProducts(void)
{
    UINT r;
    BOOL found1, found2, found3;
    DWORD index;
    char product1[39], product2[39], product3[39], guid[39];
    char product_squashed1[33], product_squashed2[33], product_squashed3[33];
    char keypath1[MAX_PATH], keypath2[MAX_PATH], keypath3[MAX_PATH];
    char *usersid;
    HKEY key1, key2, key3;
    REGSAM access = KEY_ALL_ACCESS;

    create_test_guid(product1, product_squashed1);
    create_test_guid(product2, product_squashed2);
    create_test_guid(product3, product_squashed3);
    usersid = get_user_sid();

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    strcpy(keypath2, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    strcat(keypath2, usersid);
    strcat(keypath2, "\\Installer\\Products\\");
    strcat(keypath2, product_squashed2);

    r = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath2, 0, NULL, 0, access, NULL, &key2, NULL);
    if (r == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        LocalFree(usersid);
        return;
    }
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    strcpy(keypath1, "Software\\Classes\\Installer\\Products\\");
    strcat(keypath1, product_squashed1);

    r = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath1, 0, NULL, 0, access, NULL, &key1, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    strcpy(keypath3, "Software\\Microsoft\\Installer\\Products\\");
    strcat(keypath3, product_squashed3);

    r = RegCreateKeyA(HKEY_CURRENT_USER, keypath3, &key3);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    index = 0;
    r = MsiEnumProductsA(index, guid);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    r = MsiEnumProductsA(index, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %u\n", r);

    index = 2;
    r = MsiEnumProductsA(index, guid);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %u\n", r);

    index = 0;
    r = MsiEnumProductsA(index, guid);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    found1 = found2 = found3 = FALSE;
    while ((r = MsiEnumProductsA(index, guid)) == ERROR_SUCCESS)
    {
        if (!strcmp(product1, guid)) found1 = TRUE;
        if (!strcmp(product2, guid)) found2 = TRUE;
        if (!strcmp(product3, guid)) found3 = TRUE;
        index++;
    }
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %u\n", r);
    ok(found1, "product1 not found\n");
    ok(found2, "product2 not found\n");
    ok(found3, "product3 not found\n");

    delete_key(key1, "", access & KEY_WOW64_64KEY);
    delete_key(key2, "", access & KEY_WOW64_64KEY);
    RegDeleteKeyA(key3, "");
    RegCloseKey(key1);
    RegCloseKey(key2);
    RegCloseKey(key3);
    LocalFree(usersid);
}