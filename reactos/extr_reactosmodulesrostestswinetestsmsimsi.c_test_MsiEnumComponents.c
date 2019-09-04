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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;
typedef  char BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 char FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 scalar_t__ MsiEnumComponentsA (scalar_t__,char*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char TRUE ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  ok (char,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_MsiEnumComponents(void)
{
    UINT r;
    BOOL found1, found2;
    DWORD index;
    char comp1[39], comp2[39], guid[39];
    char comp_squashed1[33], comp_squashed2[33];
    char keypath1[MAX_PATH], keypath2[MAX_PATH];
    REGSAM access = KEY_ALL_ACCESS;
    char *usersid = get_user_sid();
    HKEY key1 = NULL, key2 = NULL;

    create_test_guid( comp1, comp_squashed1 );
    create_test_guid( comp2, comp_squashed2 );

    if (is_wow64) access |= KEY_WOW64_64KEY;

    strcpy( keypath1, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\" );
    strcat( keypath1, "S-1-5-18\\Components\\" );
    strcat( keypath1, comp_squashed1 );

    r = RegCreateKeyExA( HKEY_LOCAL_MACHINE, keypath1, 0, NULL, 0, access, NULL, &key1, NULL );
    if (r == ERROR_ACCESS_DENIED)
    {
        skip( "insufficient rights\n" );
        goto done;
    }
    ok( r == ERROR_SUCCESS, "got %u\n", r );

    strcpy( keypath2, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\" );
    strcat( keypath2, usersid );
    strcat( keypath2, "\\Components\\" );
    strcat( keypath2, comp_squashed2 );

    r = RegCreateKeyExA( HKEY_LOCAL_MACHINE, keypath2, 0, NULL, 0, access, NULL, &key2, NULL );
    if (r == ERROR_ACCESS_DENIED)
    {
        skip( "insufficient rights\n" );
        goto done;
    }

    r = MsiEnumComponentsA( 0, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "got %u\n", r );

    index = 0;
    guid[0] = 0;
    found1 = found2 = FALSE;
    while (!MsiEnumComponentsA( index, guid ))
    {
        if (!strcmp( guid, comp1 )) found1 = TRUE;
        if (!strcmp( guid, comp2 )) found2 = TRUE;
        ok( guid[0], "empty guid\n" );
        guid[0] = 0;
        index++;
    }
    ok( found1, "comp1 not found\n" );
    ok( found2, "comp2 not found\n" );

done:
    delete_key( key1, "", access );
    delete_key( key2, "", access );
    RegCloseKey( key1 );
    RegCloseKey( key2 );
    LocalFree( usersid );
}