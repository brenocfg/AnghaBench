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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ uID; scalar_t__ uCmdID; struct TYPE_3__* SubMenu; } ;
typedef  TYPE_1__ VDM_MENUITEM ;
typedef  scalar_t__ UINT_PTR ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/ * HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AppendMenuW (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreatePopupMenu () ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MF_POPUP ; 
 int MF_SEPARATOR ; 
 int MF_STRING ; 

__attribute__((used)) static VOID
AppendMenuItems(HMENU hMenu,
                const VDM_MENUITEM *Items)
{
    UINT i = 0;
    WCHAR szMenuString[256];
    HMENU hSubMenu;

    do
    {
        if (Items[i].uID != (UINT)-1)
        {
            if (LoadStringW(GetModuleHandle(NULL),
                            Items[i].uID,
                            szMenuString,
                            ARRAYSIZE(szMenuString)) > 0)
            {
                if (Items[i].SubMenu != NULL)
                {
                    hSubMenu = CreatePopupMenu();
                    if (hSubMenu != NULL)
                    {
                        AppendMenuItems(hSubMenu, Items[i].SubMenu);

                        if (!AppendMenuW(hMenu,
                                         MF_STRING | MF_POPUP,
                                         (UINT_PTR)hSubMenu,
                                         szMenuString))
                        {
                            DestroyMenu(hSubMenu);
                        }
                    }
                }
                else
                {
                    AppendMenuW(hMenu,
                                MF_STRING,
                                Items[i].uCmdID,
                                szMenuString);
                }
            }
        }
        else
        {
            AppendMenuW(hMenu,
                        MF_SEPARATOR,
                        0,
                        NULL);
        }
        i++;
    } while (!(Items[i].uID == 0 && Items[i].SubMenu == NULL && Items[i].uCmdID == 0));
}