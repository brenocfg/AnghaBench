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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_KEY_DELETED ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegFlushKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  setup_main_key () ; 

__attribute__((used)) static void test_deleted_key(void)
{
    HKEY hkey, hkey2;
    char value[20];
    DWORD val_count, type;
    LONG res;

    /* Open the test key, then delete it while it's open */
    RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\Test", &hkey );

    delete_key( hkey_main );

    val_count = sizeof(value);
    type = 0;
    res = RegEnumValueA( hkey, 0, value, &val_count, NULL, &type, 0, 0 );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);

    res = RegEnumKeyA( hkey, 0, value, sizeof(value) );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);

    val_count = sizeof(value);
    type = 0;
    res = RegQueryValueExA( hkey, "test", NULL, &type, (BYTE *)value, &val_count );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);

    res = RegSetValueExA( hkey, "test", 0, REG_SZ, (const BYTE*)"value", 6);
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);

    res = RegOpenKeyA( hkey, "test", &hkey2 );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);
    if (res == 0)
        RegCloseKey( hkey2 );

    res = RegCreateKeyA( hkey, "test", &hkey2 );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);
    if (res == 0)
        RegCloseKey( hkey2 );

    res = RegFlushKey( hkey );
    ok(res == ERROR_KEY_DELETED, "expect ERROR_KEY_DELETED, got %i\n", res);

    RegCloseKey( hkey );

    setup_main_key();
}