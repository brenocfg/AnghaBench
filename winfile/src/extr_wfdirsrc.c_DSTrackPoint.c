#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int dwAttrs; } ;
struct TYPE_10__ {scalar_t__ message; long lParam; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ MSG ;
typedef  TYPE_3__* LPXDTA ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ATTR_DIR ; 
 int ATTR_PARENT ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DOF_DIRECTORY ; 
 scalar_t__ DOF_DOCUMENT ; 
 scalar_t__ DOF_EXECUTABLE ; 
 scalar_t__ DOF_MULTIPLE ; 
 scalar_t__ DO_DROPFILE ; 
 scalar_t__ DO_PRINTFILE ; 
 int /*<<< orphan*/  DispatchMessage (TYPE_2__*) ; 
 scalar_t__ DragObject (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DropFilesOnApplication (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  FS_GETSELECTION ; 
 int /*<<< orphan*/  GET_WM_COMMAND_MPS (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (scalar_t__) ; 
 scalar_t__ IsDocument (scalar_t__) ; 
 scalar_t__ IsProgramFile (scalar_t__) ; 
 scalar_t__ IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETANCHORINDEX ; 
 int /*<<< orphan*/  LB_GETSEL ; 
 int /*<<< orphan*/  LB_GETSELCOUNT ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_SELITEMRANGE ; 
 int /*<<< orphan*/  LB_SETCARETINDEX ; 
 int /*<<< orphan*/  LB_SETSEL ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 long MAKELONG (int,scalar_t__) ; 
 int /*<<< orphan*/  MULTCOPYCURSOR ; 
 scalar_t__ MemGetFileName (TYPE_3__*) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 int /*<<< orphan*/  POINTSTOPOINT (TYPE_1__,long) ; 
 scalar_t__ PeekMessage (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtInRect (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SINGLECOPYCURSOR ; 
 int /*<<< orphan*/  ScreenToClient (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectItem (scalar_t__,int,int) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetWindowDirectory () ; 
 int /*<<< orphan*/  ShowItemBitmaps (scalar_t__,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  VK_SHIFT ; 
 int /*<<< orphan*/  WFPrint (scalar_t__) ; 
 scalar_t__ WM_CANCELMODE ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 scalar_t__ WM_LBUTTONUP ; 
 scalar_t__ WM_MOUSEMOVE ; 
 scalar_t__ dxClickRect ; 
 scalar_t__ dyClickRect ; 
 int /*<<< orphan*/ * hdlgProgress ; 
 int /*<<< orphan*/ * hwndDragging ; 
 int /*<<< orphan*/  iCurDrag ; 

INT
DSTrackPoint(
   HWND hwnd,
   HWND hwndLB,
   WPARAM wParam,
   LPARAM lParam,
   BOOL bSearch)
{
   UINT      iSel;
   MSG       msg;
   RECT      rc;
   DWORD     dwAnchor;
   DWORD     dwTemp;
   LPWSTR    pch;
   BOOL      bDir;
   BOOL      bSelected;
   BOOL      bSelectOneItem;
   BOOL      bUnselectIfNoDrag;
   LPWSTR    pszFile;
   POINT     pt;

   bSelectOneItem = FALSE;
   bUnselectIfNoDrag = FALSE;

   bSelected = (BOOL)SendMessage(hwndLB, LB_GETSEL, wParam, 0L);

   if (GetKeyState(VK_SHIFT) < 0) {

      // What is the state of the Anchor point?
      dwAnchor = SendMessage(hwndLB, LB_GETANCHORINDEX, 0, 0L);
      bSelected = (BOOL)SendMessage(hwndLB, LB_GETSEL, dwAnchor, 0L);

      // If Control is up, turn everything off.

      if (!(GetKeyState(VK_CONTROL) < 0))
         SendMessage(hwndLB, LB_SETSEL, FALSE, -1L);

      // Select everything between the Anchor point and the item.
      SendMessage(hwndLB, LB_SELITEMRANGE, bSelected, MAKELONG(wParam, dwAnchor));

      // Give the selected item the focus rect.
      SendMessage(hwndLB, LB_SETCARETINDEX, wParam, 0L);

   } else if (GetKeyState(VK_CONTROL) < 0) {
      if (bSelected)
         bUnselectIfNoDrag = TRUE;
      else
         SelectItem(hwndLB, wParam, TRUE);

   } else {
      if (bSelected)
         bSelectOneItem = TRUE;
      else {
         // Deselect everything.
         SendMessage(hwndLB, LB_SETSEL, FALSE, -1L);

         // Select the current item.
         SelectItem(hwndLB, wParam, TRUE);
      }
   }

   if (!bSearch)
      UpdateStatus(GetParent(hwnd));

   POINTSTOPOINT(pt, lParam);
   ClientToScreen(hwndLB, (LPPOINT)&pt);
   ScreenToClient(hwnd, (LPPOINT)&pt);

   // See if the user moves a certain number of pixels in any direction

   SetRect(&rc, pt.x - dxClickRect, pt.y - dyClickRect,
      pt.x + dxClickRect, pt.y + dyClickRect);

   SetCapture(hwnd);

   for (;;) {

      if (GetCapture() != hwnd) {
          msg.message = WM_LBUTTONUP;   // don't proceed below
          break;
      }

      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
          DispatchMessage(&msg);

          //
          // WM_CANCELMODE messages will unset the capture, in that
          // case I want to exit this loop

          //
          // Must do explicit check.
          //
      if (msg.message == WM_CANCELMODE || GetCapture() != hwnd) {
              msg.message = WM_LBUTTONUP;   // don't proceed below

              break;
          }

          if (msg.message == WM_LBUTTONUP)
              break;

          POINTSTOPOINT(pt, msg.lParam);
          if ((msg.message == WM_MOUSEMOVE) && !(PtInRect(&rc, pt)))
              break;
      }
    }
    ReleaseCapture();

    // Did the guy NOT drag anything?
    if (msg.message == WM_LBUTTONUP) {
       if (bSelectOneItem) {
          /* Deselect everything. */
          SendMessage(hwndLB, LB_SETSEL, FALSE, -1L);

          /* Select the current item. */
          SelectItem(hwndLB, wParam, TRUE);
       }

      if (bUnselectIfNoDrag)
         SelectItem(hwndLB, wParam, FALSE);

      // notify the appropriate people

      SendMessage(hwnd, WM_COMMAND,
         GET_WM_COMMAND_MPS(0, hwndLB, LBN_SELCHANGE));

      return 1;
   }

   //
   // Enter Danger Mouse's BatCave.
   //
   if (SendMessage(hwndLB, LB_GETSELCOUNT, 0, 0L) == 1) {

      LPXDTA lpxdta;

      //
      // There is only one thing selected.
      //  Figure out which cursor to use.
      //
      // There is only one thing selected.
      //  Figure out which cursor to use.

      if (SendMessage(hwndLB,
                      LB_GETTEXT,
                      wParam,
                      (LPARAM)&lpxdta) == LB_ERR || !lpxdta) {
         return 1;
      }

      pszFile = MemGetFileName(lpxdta);

      bDir = lpxdta->dwAttrs & ATTR_DIR;

      //
      // avoid dragging the parent dir
      //
      if (lpxdta->dwAttrs & ATTR_PARENT) {
         return 1;
      }

      if (bDir) {
         iSel = DOF_DIRECTORY;
      } else if (IsProgramFile(pszFile)) {
         iSel = DOF_EXECUTABLE;
      } else if (IsDocument(pszFile)) {
         iSel = DOF_DOCUMENT;
      } else
         iSel = DOF_DOCUMENT;

      iCurDrag = SINGLECOPYCURSOR;
   } else {

      // Multiple files are selected.
      iSel = DOF_MULTIPLE;
      iCurDrag = MULTCOPYCURSOR;
   }


   // Get the list of selected things.
   pch = (LPTSTR)SendMessage(hwnd, FS_GETSELECTION, FALSE, 0L);

   // Wiggle things around.
   hwndDragging = hwndLB;

   dwTemp = DragObject(GetDesktopWindow(), hwnd, (UINT)iSel, (ULONG_PTR)pch, NULL);

   SetWindowDirectory();

   if (dwTemp == DO_PRINTFILE) {
      // print these suckers
      hdlgProgress = NULL;
      WFPrint(pch);
   } else if (dwTemp == DO_DROPFILE) {
      // try and drop them on an application
      DropFilesOnApplication(pch);
   }

   LocalFree((HANDLE)pch);

   if (IsWindow(hwnd))
      ShowItemBitmaps(hwndLB, TRUE);

   hwndDragging = NULL;

   if (!bSearch && IsWindow(hwnd))
      UpdateStatus(GetParent(hwnd));

   return 2;
}