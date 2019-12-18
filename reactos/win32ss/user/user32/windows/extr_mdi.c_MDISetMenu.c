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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ hFrameMenu; scalar_t__ hWindowMenu; scalar_t__ hwndChildMaximized; scalar_t__ nActiveChildren; int /*<<< orphan*/  hBmpClose; } ;
typedef  TYPE_1__ MDICLIENTINFO ;
typedef  long LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsMenu (scalar_t__) ; 
 int /*<<< orphan*/  MDI_AugmentFrameMenu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MDI_RefreshMenu (TYPE_1__*) ; 
 int /*<<< orphan*/  MDI_RestoreFrameMenu (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMenu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 TYPE_1__* get_client_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT MDISetMenu( HWND hwnd, HMENU hmenuFrame,
                           HMENU hmenuWindow)
{
    MDICLIENTINFO *ci;
    HWND hwndFrame = GetParent(hwnd);

    TRACE("%p, frame menu %p, window menu %p\n", hwnd, hmenuFrame, hmenuWindow);

    if (hmenuFrame && !IsMenu(hmenuFrame))
    {
	WARN("hmenuFrame is not a menu handle\n");
	return 0L;
    }

    if (hmenuWindow && !IsMenu(hmenuWindow))
    {
	WARN("hmenuWindow is not a menu handle\n");
	return 0L;
    }

    if (!(ci = get_client_info( hwnd ))) return 0;

    TRACE("old frame menu %p, old window menu %p\n", ci->hFrameMenu, ci->hWindowMenu);

    if (hmenuFrame)
    {
        if (hmenuFrame == ci->hFrameMenu) return (LRESULT)hmenuFrame;

        if (ci->hwndChildMaximized)
            MDI_RestoreFrameMenu( hwndFrame, ci->hwndChildMaximized, ci->hBmpClose );
    }

    if( hmenuWindow && hmenuWindow != ci->hWindowMenu )
    {
        /* delete menu items from ci->hWindowMenu
         * and add them to hmenuWindow */
        /* Agent newsreader calls this function with  ci->hWindowMenu == NULL */
        if( ci->hWindowMenu && ci->nActiveChildren )
        {
            UINT nActiveChildren_old = ci->nActiveChildren;

            /* Remove all items from old Window menu */
            ci->nActiveChildren = 0;
            MDI_RefreshMenu(ci);

            ci->hWindowMenu = hmenuWindow;

            /* Add items to the new Window menu */
            ci->nActiveChildren = nActiveChildren_old;
            MDI_RefreshMenu(ci);
        }
        else
            ci->hWindowMenu = hmenuWindow;
    }

    if (hmenuFrame)
    {
        SetMenu(hwndFrame, hmenuFrame);
        if( hmenuFrame != ci->hFrameMenu )
        {
            HMENU oldFrameMenu = ci->hFrameMenu;

            ci->hFrameMenu = hmenuFrame;
            if (ci->hwndChildMaximized)
                MDI_AugmentFrameMenu( hwndFrame, ci->hwndChildMaximized );

            return (LRESULT)oldFrameMenu;
        }
    }

    return 0;
}