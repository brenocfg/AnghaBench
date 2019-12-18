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
struct TYPE_3__ {int dwAttrs; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * PDOCBUCKET ;
typedef  TYPE_1__* LPXDTA ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPTSTR ;
typedef  scalar_t__ LPRECT ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ATTR_DIR ; 
 int ATTR_PARENT ; 
 int COLOR_WINDOW ; 
 int COLOR_WINDOWFRAME ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (scalar_t__) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetSysColor (int) ; 
 scalar_t__ IDS_DRAG_COPYING ; 
 scalar_t__ IDS_DRAG_EXECUTING ; 
 scalar_t__ IDS_DRAG_MOVING ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  IntersectRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * IsProgramFile (int /*<<< orphan*/ *) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETITEMRECT ; 
 int /*<<< orphan*/  LB_GETSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/ * MemGetFileName (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int SBT_NOBORDERS ; 
 int /*<<< orphan*/  SB_SETTEXT ; 
 int SST_FORMAT ; 
 int SST_RESOURCE ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  SetStatusText (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripFilespec (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 scalar_t__ fShowSourceBitmaps ; 
 scalar_t__ hwndDragging ; 
 scalar_t__ hwndStatus ; 
 scalar_t__ szNULL ; 

BOOL 
DSRectItem(
   HWND hwndLB,
   INT iItem,
   BOOL bFocusOn,
   BOOL bSearch)
{
   RECT      rc;
   RECT      rcT;
   HDC       hDC;
   BOOL      bSel;
   INT       nColor;
   HBRUSH    hBrush;
   LPXDTA    lpxdta;
   WCHAR     szTemp[MAXPATHLEN];
   PDOCBUCKET pIsProgram = NULL;
   LPWSTR    pszFile;

   //
   // Are we over an unused part of the listbox?
   //
   if (iItem == -1) {
      if (bSearch || hwndDragging == hwndLB) {
         SendMessage(hwndStatus,
                     SB_SETTEXT,
                     SBT_NOBORDERS|255,
                     (LPARAM)szNULL);

         UpdateWindow(hwndStatus);

      } else {

         SendMessage(GetParent(hwndLB),
                     FS_GETDIRECTORY,
                     COUNTOF(szTemp),
                     (LPARAM)szTemp);

         StripBackslash(szTemp);

         SetStatusText(SBT_NOBORDERS|255,
                       SST_RESOURCE|SST_FORMAT,
                       (LPWSTR)(fShowSourceBitmaps ?
                          IDS_DRAG_COPYING :
                          IDS_DRAG_MOVING),
                       szTemp);

         UpdateWindow(hwndStatus);
      }
      return FALSE;
   }

   //
   // Are we over ourselves? (i.e. a selected item in the source listbox)
   //
   bSel = (BOOL)SendMessage(hwndLB, LB_GETSEL, iItem, 0L);

   if (bSel && (hwndDragging == hwndLB)) {

ClearStatus:

      SendMessage(hwndStatus,
                  SB_SETTEXT,
                  SBT_NOBORDERS|255,
                  (LPARAM)szNULL);

      UpdateWindow(hwndStatus);
      return FALSE;
   }

   //
   // We only put rectangles around directories and program items.
   //
   if (SendMessage(hwndLB,
                   LB_GETTEXT,
                   iItem,
                   (LPARAM)(LPTSTR)&lpxdta) == LB_ERR || !lpxdta) {
      return FALSE;
   }

   if (!(lpxdta->dwAttrs & ATTR_DIR)  &&
      !(pIsProgram = IsProgramFile(MemGetFileName(lpxdta)))) {

      //
      // It's not a directory
      //

      //
      // If it's the same dir window, or we are dropping to a search
      // window, don't show any text!
      //
      if ((hwndDragging == hwndLB) || bSearch) {
         goto ClearStatus;
      }

      //
      // We are in a directory window (not search window)
      // but we aren't over a folder, so just use the current directory.
      //
      SendMessage(GetParent(hwndLB), FS_GETDIRECTORY, COUNTOF(szTemp), (LPARAM)szTemp);
      StripBackslash(szTemp);

      SetStatusText(SBT_NOBORDERS|255,
                    SST_FORMAT | SST_RESOURCE,
                    (LPWSTR)(fShowSourceBitmaps ?
                        IDS_DRAG_COPYING :
                        IDS_DRAG_MOVING),
                    szTemp);

      UpdateWindow(hwndStatus);
      return FALSE;
   }

   //
   // At this point, we are over a directory folder,
   // be we could be in a search or directory window.
   //

   //
   // Turn the item's rectangle on or off.
   //
   if (bSearch || !(lpxdta->dwAttrs & ATTR_PARENT)) {

      pszFile = MemGetFileName(lpxdta);

   } else {

      SendMessage(GetParent(hwndLB), FS_GETDIRECTORY, COUNTOF(szTemp), (LPARAM)szTemp);
      StripBackslash(szTemp);  // trim it down
      StripFilespec(szTemp);

      pszFile = szTemp;
   }

   //
   // Else bSearch and szTemp contains the file name
   //
   if (bFocusOn) {

      SetStatusText(SBT_NOBORDERS|255,
                    SST_FORMAT | SST_RESOURCE,
                    (LPWSTR)(pIsProgram ?
                       IDS_DRAG_EXECUTING :
                       (fShowSourceBitmaps ?
                          IDS_DRAG_COPYING :
                          IDS_DRAG_MOVING)),
                   pszFile);

      UpdateWindow(hwndStatus);
   }

   SendMessage(hwndLB, LB_GETITEMRECT, iItem, (LPARAM)(LPRECT)&rc);
   GetClientRect(hwndLB,&rcT);
   IntersectRect(&rc,&rc,&rcT);

   if (bFocusOn) {
      hDC = GetDC(hwndLB);
      if (bSel) {
         nColor = COLOR_WINDOW;
         InflateRect(&rc, -1, -1);
      } else
         nColor = COLOR_WINDOWFRAME;

      if (hBrush = CreateSolidBrush(GetSysColor(nColor))) {
         FrameRect(hDC, &rc, hBrush);
         DeleteObject(hBrush);
      }
      ReleaseDC(hwndLB, hDC);
   } else {
      InvalidateRect(hwndLB, &rc, FALSE);
      UpdateWindow(hwndLB);
   }

   return TRUE;
}