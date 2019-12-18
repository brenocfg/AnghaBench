#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {TYPE_1__ ptDrop; int /*<<< orphan*/ * hwndSink; int /*<<< orphan*/ * hwndSource; } ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_8__ {scalar_t__ left; scalar_t__ top; scalar_t__ bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  TYPE_4__* LPDROPSTRUCT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetMDIChildFromDescendant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HasDirWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HasTreeWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 int /*<<< orphan*/  SB_LINEDOWN ; 
 int /*<<< orphan*/  SB_LINEUP ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  WM_VSCROLL ; 

VOID
DSDragScrollSink(LPDROPSTRUCT lpds)
{
    HWND hwndMDIChildSource;
    HWND hwndMDIChildSink;

    RECT rcSink;
    RECT rcScroll;
    POINT ptDropScr;
    HWND hwndToScroll;

    hwndMDIChildSource = GetMDIChildFromDescendant(lpds->hwndSource);
    hwndMDIChildSink = GetMDIChildFromDescendant(lpds->hwndSink);

    // calculate the screen x/y of the ptDrop
    if (lpds->hwndSink == NULL)
    {
      rcSink.left = rcSink.top = 0;
    }
    else
    {
      GetClientRect(lpds->hwndSink, &rcSink);
      ClientToScreen(lpds->hwndSink, (LPPOINT)&rcSink.left);
      ClientToScreen(lpds->hwndSink, (LPPOINT)&rcSink.right);
    }

    ptDropScr.x = rcSink.left + lpds->ptDrop.x;
    ptDropScr.y = rcSink.top + lpds->ptDrop.y;

    // determine which window we will be potentially scrolling; if the sink MDI is null,
    // this means that the mouse is over the frame of this app or outside that;
    // we scroll the source mdi child in that case
    hwndToScroll = hwndMDIChildSink;
    if (hwndToScroll == NULL)
    {
      hwndToScroll = hwndMDIChildSource;
    }

    GetClientRect(hwndToScroll, &rcScroll);
    ClientToScreen(hwndToScroll, (LPPOINT)&rcScroll.left);
    ClientToScreen(hwndToScroll, (LPPOINT)&rcScroll.right);

    // if the drop y is above the top of the window to scroll
    if (ptDropScr.y < rcScroll.top || ptDropScr.y > rcScroll.bottom)
    {
      // scroll up/down one line; figure out whether tree or dir list box
      HWND hwndTree = HasTreeWindow(hwndToScroll);
      HWND hwndDir = HasDirWindow(hwndToScroll);
      HWND hwndLB = NULL;

      if (hwndDir)
      {
        hwndLB = GetDlgItem(hwndDir, IDCW_LISTBOX);
        if (hwndLB)
        {
            RECT rcLB;
            GetClientRect(hwndLB, &rcLB);
            ClientToScreen(hwndLB, (LPPOINT)&rcLB.left);
            // no need: ClientToScreen(hwndLB, (LPPOINT)&rcLB.right);

            if (ptDropScr.x < rcLB.left)
            {
                // to left of dir list box; switch to tree
                hwndLB = NULL;
            }
        }
      }

      if (hwndLB == NULL && hwndTree)
      {
          // no dir or point outside of dir list box
          hwndLB = GetDlgItem(hwndTree, IDCW_TREELISTBOX);
      }

      if (hwndLB)
      {
          SendMessage(hwndLB, WM_VSCROLL, ptDropScr.y < rcScroll.top ? SB_LINEUP : SB_LINEDOWN, 0L);
      }
    }          
}