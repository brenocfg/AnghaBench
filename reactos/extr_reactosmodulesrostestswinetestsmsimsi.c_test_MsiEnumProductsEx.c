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
typedef  int /*<<< orphan*/  sid ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int MSIINSTALLCONTEXT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSIINSTALLCONTEXT_ALL ; 
 int MSIINSTALLCONTEXT_MACHINE ; 
 int MSIINSTALLCONTEXT_USERMANAGED ; 
 int MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiEnumProductsExA (char*,char*,int,int,char*,int*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiEnumProductsEx(void)
{
    UINT r;
    DWORD len, index;
    MSIINSTALLCONTEXT context;
    char product0[39], product1[39], product2[39], product3[39], guid[39], sid[128];
    char product_squashed1[33], product_squashed2[33], product_squashed3[33];
    char keypath1[MAX_PATH], keypath2[MAX_PATH], keypath3[MAX_PATH];
    HKEY key1 = NULL, key2 = NULL, key3 = NULL;
    REGSAM access = KEY_ALL_ACCESS;
    char *usersid = get_user_sid();

    if (!pMsiEnumProductsExA)
    {
        win_skip("MsiEnumProductsExA not implemented\n");
        return;
    }

    create_test_guid( product0, NULL );
    create_test_guid( product1, product_squashed1 );
    create_test_guid( product2, product_squashed2 );
    create_test_guid( product3, product_squashed3 );

    if (is_wow64) access |= KEY_WOW64_64KEY;

    strcpy( keypath2, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\" );
    strcat( keypath2, usersid );
    strcat( keypath2, "\\Installer\\Products\\" );
    strcat( keypath2, product_squashed2 );

    r = RegCreateKeyExA( HKEY_LOCAL_MACHINE, keypath2, 0, NULL, 0, access, NULL, &key2, NULL );
    if (r == ERROR_ACCESS_DENIED)
    {
        skip( "insufficient rights\n" );
        goto done;
    }
    ok( r == ERROR_SUCCESS, "got %u\n", r );

    strcpy( keypath1, "Software\\Classes\\Installer\\Products\\" );
    strcat( keypath1, product_squashed1 );

    r = RegCreateKeyExA( HKEY_LOCAL_MACHINE, keypath1, 0, NULL, 0, access, NULL, &key1, NULL );
    ok( r == ERROR_SUCCESS, "got %u\n", r );

    strcpy( keypath3, usersid );
    strcat( keypath3, "\\Software\\Microsoft\\Installer\\Products\\" );
    strcat( keypath3, product_squashed3 );

    r = RegCreateKeyExA( HKEY_USERS, keypath3, 0, NULL, 0, access, NULL, &key3, NULL );
    ok( r == ERROR_SUCCESS, "got %u\n", r );

    r = pMsiEnumProductsExA( NULL, NULL, 0, 0, NULL, NULL, NULL, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "got %u\n", r );

    len = sizeof(sid);
    r = pMsiEnumProductsExA( NULL, NULL, 0, 0, NULL, NULL, NULL, &len );
    ok( r == ERROR_INVALID_PARAMETER, "got %u\n", r );
    ok( len == sizeof(sid), "got %u\n", len );

    r = pMsiEnumProductsExA( NULL, NULL, MSIINSTALLCONTEXT_ALL, 0, NULL, NULL, NULL, NULL );
    ok( r == ERROR_SUCCESS, "got %u\n", r );

    sid[0] = 0;
    len = sizeof(sid);
    r = pMsiEnumProductsExA( product0, NULL, MSIINSTALLCONTEXT_ALL, 0, NULL, NULL, sid, &len );
    ok( r == ERROR_NO_MORE_ITEMS, "got %u\n", r );
    ok( len == sizeof(sid), "got %u\n", len );
    ok( !sid[0], "got %s\n", sid );

    sid[0] = 0;
    len = sizeof(sid);
    r = pMsiEnumProductsExA( product0, usersid, MSIINSTALLCONTEXT_ALL, 0, NULL, NULL, sid, &len );
    ok( r == ERROR_NO_MORE_ITEMS, "got %u\n", r );
    ok( len == sizeof(sid), "got %u\n", len );
    ok( !sid[0], "got %s\n", sid );

    sid[0] = 0;
    len = 0;
    r = pMsiEnumProductsExA( NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED, 0, NULL, NULL, sid, &len );
    ok( r == ERROR_MORE_DATA, "got %u\n", r );
    ok( len, "length unchanged\n" );
    ok( !sid[0], "got %s\n", sid );

    guid[0] = 0;
    context = 0xdeadbeef;
    sid[0] = 0;
    len = sizeof(sid);
    r = pMsiEnumProductsExA( NULL, NULL, MSIINSTALLCONTEXT_ALL, 0, guid, &context, sid, &len );
    ok( r == ERROR_SUCCESS, "got %u\n", r );
    ok( guid[0], "empty guid\n" );
    ok( context != 0xdeadbeef, "context unchanged\n" );
    ok( !len, "got %u\n", len );
    ok( !sid[0], "got %s\n", sid );

    guid[0] = 0;
    context = 0xdeadbeef;
    sid[0] = 0;
    len = sizeof(sid);
    r = pMsiEnumProductsExA( NULL, usersid, MSIINSTALLCONTEXT_ALL, 0, guid, &context, sid, &len );
    ok( r == ERROR_SUCCESS, "got %u\n", r );
    ok( guid[0], "empty guid\n" );
    ok( context != 0xdeadbeef, "context unchanged\n" );
    ok( !len, "got %u\n", len );
    ok( !sid[0], "got %s\n", sid );

    guid[0] = 0;
    context = 0xdeadbeef;
    sid[0] = 0;
    len = sizeof(sid);
    r = pMsiEnumProductsExA( NULL, "S-1-1-0", MSIINSTALLCONTEXT_ALL, 0, guid, &context, sid, &len );
    if (r == ERROR_ACCESS_DENIED)
    {
        skip( "insufficient rights\n" );
        goto done;
    }
    ok( r == ERROR_SUCCESS, "got %u\n", r );
    ok( guid[0], "empty guid\n" );
    ok( context != 0xdeadbeef, "context unchanged\n" );
    ok( !len, "got %u\n", len );
    ok( !sid[0], "got %s\n", sid );

    index = 0;
    guid[0] = 0;
    context = 0xdeadbeef;
    sid[0] = 0;
    len = sizeof(sid);
    while (!pMsiEnumProductsExA( NULL, "S-1-1-0", MSIINSTALLCONTEXT_ALL, index, guid, &context, sid, &len ))
    {
        if (!strcmp( product1, guid ))
        {
            ok( context == MSIINSTALLCONTEXT_MACHINE, "got %u\n", context );
            ok( !sid[0], "got \"%s\"\n", sid );
            ok( !len, "unexpected length %u\n", len );
        }
        if (!strcmp( product2, guid ))
        {
            ok( context == MSIINSTALLCONTEXT_USERMANAGED, "got %u\n", context );
            ok( sid[0], "empty sid\n" );
            ok( len == strlen(sid), "unexpected length %u\n", len );
        }
        if (!strcmp( product3, guid ))
        {
            ok( context == MSIINSTALLCONTEXT_USERUNMANAGED, "got %u\n", context );
            ok( sid[0], "empty sid\n" );
            ok( len == strlen(sid), "unexpected length %u\n", len );
        }
        index++;
        guid[0] = 0;
        context = 0xdeadbeef;
        sid[0] = 0;
        len = sizeof(sid);
    }

done:
    delete_key( key1, "", access );
    delete_key( key2, "", access );
    delete_key( key3, "", access );
    RegCloseKey( key1 );
    RegCloseKey( key2 );
    RegCloseKey( key3 );
    LocalFree( usersid );
}