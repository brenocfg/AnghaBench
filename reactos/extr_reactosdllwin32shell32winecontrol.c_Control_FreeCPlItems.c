#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int total_subprogs; } ;
struct TYPE_5__ {int cbSize; scalar_t__ dwItemData; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_2__ CPanel ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenuItemInfoW (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int IDM_CPANEL_APPLET_BASE ; 
 int /*<<< orphan*/  MIIM_DATA ; 

__attribute__((used)) static void Control_FreeCPlItems(HWND hWnd, CPanel *panel)
{
    HMENU hMenu, hSubMenu;
    MENUITEMINFOW mii;
    unsigned int i;

    /* get the File menu */
    hMenu = GetMenu(hWnd);

    if (!hMenu)
        return;

    hSubMenu = GetSubMenu(hMenu, 0);

    if (!hSubMenu)
        return;

    /* loop and free the item data */
    for (i = IDM_CPANEL_APPLET_BASE; i <= IDM_CPANEL_APPLET_BASE + panel->total_subprogs; i++)
    {
        mii.cbSize = sizeof(MENUITEMINFOW);
        mii.fMask = MIIM_DATA;

        if (!GetMenuItemInfoW(hSubMenu, i, FALSE, &mii))
            continue;

        HeapFree(GetProcessHeap(), 0, (LPVOID) mii.dwItemData);
    }
}