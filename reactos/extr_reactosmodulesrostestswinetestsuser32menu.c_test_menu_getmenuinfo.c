#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MENUINFO ;
typedef  int /*<<< orphan*/ * HMENU ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateMenu () ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ *) ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetMenuInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_menu_getmenuinfo(void)
{
    HMENU hmenu;
    MENUINFO mi = {0};
    BOOL ret;
    DWORD gle;

    if (!pGetMenuInfo)
    {
        win_skip("GetMenuInfo is not available\n");
        return;
    }

    /* create a menu */
    hmenu = CreateMenu();
    assert( hmenu);
    /* test some parameter errors */
    SetLastError(0xdeadbeef);
    ret = pGetMenuInfo( hmenu, NULL);
    gle= GetLastError();
    ok( !ret, "GetMenuInfo() should have failed\n");
    ok( gle == ERROR_INVALID_PARAMETER ||
        broken(gle == 0xdeadbeef), /* Win98, WinME */
        "GetMenuInfo() error got %u expected %u\n", gle, ERROR_INVALID_PARAMETER);
    SetLastError(0xdeadbeef);
    mi.cbSize = 0;
    ret = pGetMenuInfo( hmenu, &mi);
    gle= GetLastError();
    ok( !ret, "GetMenuInfo() should have failed\n");
    ok( gle == ERROR_INVALID_PARAMETER ||
        broken(gle == 0xdeadbeef), /* Win98, WinME */
        "GetMenuInfo() error got %u expected %u\n", gle, ERROR_INVALID_PARAMETER);
    SetLastError(0xdeadbeef);
    mi.cbSize = sizeof( MENUINFO);
    ret = pGetMenuInfo( hmenu, &mi);
    gle= GetLastError();
    ok( ret, "GetMenuInfo() should have succeeded\n");
    ok( gle == 0xdeadbeef, "GetMenuInfo() error got %u\n", gle);
    SetLastError(0xdeadbeef);
    mi.cbSize = 0;
    ret = pGetMenuInfo( NULL, &mi);
    gle= GetLastError();
    ok( !ret, "GetMenuInfo() should have failed\n");
    ok( gle == ERROR_INVALID_PARAMETER ||
        broken(gle == 0xdeadbeef), /* Win98, WinME */
        "GetMenuInfo() error got %u expected %u\n", gle, ERROR_INVALID_PARAMETER);
    /* clean up */
    DestroyMenu( hmenu);
    return;
}