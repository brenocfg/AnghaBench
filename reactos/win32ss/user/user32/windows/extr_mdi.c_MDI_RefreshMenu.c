#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mii ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_7__ {int nActiveChildren; scalar_t__ idFirstChild; scalar_t__* child; scalar_t__ hwndActiveChild; int /*<<< orphan*/  hFrameMenu; int /*<<< orphan*/  hWindowMenu; } ;
struct TYPE_6__ {int cbSize; int fType; scalar_t__ wID; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  TYPE_2__ MDICLIENTINFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AppendMenuW (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetMenuItemCount (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMenuItemInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_MDI_MOREWINDOWS ; 
 int /*<<< orphan*/  InternalGetWindowText (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  IsMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MDI_MAXTITLELENGTH ; 
 int MDI_MOREWINDOWSLIMIT ; 
 int /*<<< orphan*/  MF_BYPOSITION ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 int MF_SEPARATOR ; 
 int MF_STRING ; 
 int /*<<< orphan*/  MIIM_ID ; 
 int /*<<< orphan*/  MIIM_TYPE ; 
 scalar_t__ RemoveMenu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  User32Instance ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT MDI_RefreshMenu(MDICLIENTINFO *ci)
{
    UINT i, count, visible, id;
    WCHAR buf[MDI_MAXTITLELENGTH];

    TRACE("children %u, window menu %p\n", ci->nActiveChildren, ci->hWindowMenu);

    if (!ci->hWindowMenu)
        return 0;

    if (!IsMenu(ci->hWindowMenu))
    {
        WARN("Window menu handle %p is no longer valid\n", ci->hWindowMenu);
        return 0;
    }

    /* Windows finds the last separator in the menu, and if after it
     * there is a menu item with MDI magic ID removes all existing
     * menu items after it, and then adds visible MDI children.
     */
    count = GetMenuItemCount(ci->hWindowMenu);
    for (i = 0; i < count; i++)
    {
        MENUITEMINFOW mii;

        memset(&mii, 0, sizeof(mii));
        mii.cbSize = sizeof(mii);
        mii.fMask  = MIIM_TYPE;
        if (GetMenuItemInfoW(ci->hWindowMenu, i, TRUE, &mii))
        {
            if (mii.fType & MF_SEPARATOR)
            {
                /* Windows checks only ID of the menu item */
                memset(&mii, 0, sizeof(mii));
                mii.cbSize = sizeof(mii);
                mii.fMask  = MIIM_ID;
                if (GetMenuItemInfoW(ci->hWindowMenu, i + 1, TRUE, &mii))
                {
                    if (mii.wID == ci->idFirstChild)
                    {
                        TRACE("removing %u items including separator\n", count - i);
                        while (RemoveMenu(ci->hWindowMenu, i, MF_BYPOSITION))
                            /* nothing */;

                        break;
                    }
                }
            }
        }
    }

    visible = 0;
    for (i = 0; i < ci->nActiveChildren; i++)
    {
        if (GetWindowLongPtrW(ci->child[i], GWL_STYLE) & WS_VISIBLE)
        {
            id = ci->idFirstChild + visible;

            if (visible == MDI_MOREWINDOWSLIMIT)
            {
                LoadStringW(User32Instance, IDS_MDI_MOREWINDOWS, buf, sizeof(buf)/sizeof(WCHAR));
                AppendMenuW(ci->hWindowMenu, MF_STRING, id, buf);
                break;
            }

            if (!visible)
                /* Visio expects that separator has id 0 */
                AppendMenuW(ci->hWindowMenu, MF_SEPARATOR, 0, NULL);

            visible++;

            SetWindowLongPtrW(ci->child[i], GWLP_ID, id);

            buf[0] = '&';
            buf[1] = '0' + visible;
            buf[2] = ' ';
            InternalGetWindowText(ci->child[i], buf + 3, sizeof(buf)/sizeof(WCHAR) - 3);
            TRACE("Adding %p, id %u %s\n", ci->child[i], id, debugstr_w(buf));
            AppendMenuW(ci->hWindowMenu, MF_STRING, id, buf);

            if (ci->child[i] == ci->hwndActiveChild)
                CheckMenuItem(ci->hWindowMenu, id, MF_CHECKED);
        }
        else
            TRACE("MDI child %p is not visible, skipping\n", ci->child[i]);
    }

    return (LRESULT)ci->hFrameMenu;
}