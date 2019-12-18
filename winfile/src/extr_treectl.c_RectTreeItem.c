#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_15__ {int nLevels; } ;
struct TYPE_14__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_13__ {scalar_t__ cx; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PDNODE ;
typedef  scalar_t__ LPRECT ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int /*<<< orphan*/  COLOR_WINDOWFRAME ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDC (scalar_t__) ; 
 scalar_t__ GetRealExtent (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTreePath (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDS_DRAG_COPYING ; 
 scalar_t__ IDS_DRAG_MOVING ; 
 int /*<<< orphan*/  InflateRect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntersectRect (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,TYPE_2__*,scalar_t__) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETITEMRECT ; 
 int /*<<< orphan*/  LB_GETSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int SBT_NOBORDERS ; 
 int /*<<< orphan*/  SB_SETTEXT ; 
 int SST_FORMAT ; 
 int SST_RESOURCE ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  SetStatusText (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripBackslash (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 scalar_t__ dxFolder ; 
 int dxText ; 
 int /*<<< orphan*/  dyBorder ; 
 int dyBorderx2 ; 
 scalar_t__ fShowSourceBitmaps ; 
 scalar_t__ hwndDragging ; 
 scalar_t__ hwndStatus ; 
 scalar_t__ szNULL ; 

BOOL
RectTreeItem(HWND hwndLB, INT iItem, BOOL bFocusOn)
{
   INT           len;
   HDC           hdc;
   RECT          rc;
   RECT          rcClip;
   BOOL          bSel;
   WORD          wColor;
   PDNODE         pNode;
   HBRUSH        hBrush;
   TCHAR          szPath[MAXPATHLEN];
   SIZE          size;

   if (iItem == -1) {

EmptyStatusAndReturn:
      SendMessage(hwndStatus, SB_SETTEXT, SBT_NOBORDERS|255,
         (LPARAM)szNULL);
      UpdateWindow(hwndStatus);
      return FALSE;
   }

   // Are we over ourselves? (i.e. a selected item in the source listbox)

   bSel = (BOOL)SendMessage(hwndLB, LB_GETSEL, iItem, 0L);

   if (bSel && (hwndDragging == hwndLB))
      goto EmptyStatusAndReturn;

   if (SendMessage(hwndLB, LB_GETTEXT, iItem, (LPARAM)&pNode) == LB_ERR)
      goto EmptyStatusAndReturn;

   SendMessage(hwndLB, LB_GETITEMRECT, iItem, (LPARAM)(LPRECT)&rc);

   hdc = GetDC(hwndLB);

   /*
    *  Save the real extent.
    */
   size.cx = GetRealExtent(pNode, NULL, szPath, &len);
   size.cx += dyBorder;


   // rc.left always equals 0 regardless if the horizontal scrollbar
   // is scrolled.  Furthermore, the DC of the listbox uses the visible
   // upper-left corner as (0,0) instead of the conceptual one.

   // To fix this problem, we subtract of the offset between the visible
   // left edge and the conceptual one.  This is done by checking the
   // size of the visible window and subtracting this from the right
   // edge, which is correct.

   // moved up
   GetClientRect(hwndLB, &rcClip);

   rc.left = pNode->nLevels * dxText * 2 -
      (rc.right - (rcClip.right-rcClip.left));

   rc.right = rc.left + dxFolder + size.cx + 4 * dyBorderx2;

   IntersectRect(&rc, &rc, &rcClip);

   if (bFocusOn) {

      GetTreePath(pNode, szPath);
      StripBackslash(szPath);

      SetStatusText(SBT_NOBORDERS|255, SST_FORMAT|SST_RESOURCE,
               (LPCTSTR)(DWORD)(fShowSourceBitmaps ? IDS_DRAG_COPYING : IDS_DRAG_MOVING),
               szPath);
      UpdateWindow(hwndStatus);

      if (bSel) {
          wColor = COLOR_WINDOW;
          InflateRect(&rc, -dyBorder, -dyBorder);
      } else
          wColor = COLOR_WINDOWFRAME;
      if (hBrush = CreateSolidBrush(GetSysColor(wColor))) {
        FrameRect(hdc, &rc, hBrush);
        DeleteObject(hBrush);
      }
   } else {
      InvalidateRect(hwndLB, &rc, TRUE);
      UpdateWindow(hwndLB);
   }
   ReleaseDC(hwndLB, hdc);
   return TRUE;
}