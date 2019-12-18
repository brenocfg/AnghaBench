#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cbSize; } ;
typedef  TYPE_1__ MENUITEMINFOA ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateMenu () ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_MENU_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetMenuItemInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL correct_behavior(void)
{
    HMENU hmenu;
    MENUITEMINFOA info;
    BOOL rc;

    hmenu = CreateMenu();

    memset(&info, 0, sizeof(MENUITEMINFOA));
    info.cbSize= sizeof(MENUITEMINFOA);
    SetLastError(0xdeadbeef);
    rc = GetMenuItemInfoA(hmenu, 0, TRUE, &info);
    /* Win9x  : 0xdeadbeef
     * NT4    : ERROR_INVALID_PARAMETER
     * >= W2K : ERROR_MENU_ITEM_NOT_FOUND
     */
    if (!rc && GetLastError() != ERROR_MENU_ITEM_NOT_FOUND)
    {
        win_skip("NT4 and below can't handle a bigger MENUITEMINFO struct\n");
        DestroyMenu(hmenu);
        return FALSE;
    }

    DestroyMenu(hmenu);
    return TRUE;
}