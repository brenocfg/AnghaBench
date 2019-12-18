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
struct TYPE_3__ {int right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ LPTSTR ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateWindowEx (long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  EnableCheckTBButtons (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_READLEVEL ; 
 int /*<<< orphan*/  GWL_SPLIT ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetTreeIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetTreeWindows (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 scalar_t__ IDCW_DIR ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 scalar_t__ IDCW_TREECONTROL ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TC_SETDRIVE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatus (scalar_t__) ; 
 int /*<<< orphan*/  WM_SETICON ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_VISIBLE ; 
 int dxDriveBitmap ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  hwndDriveBar ; 
 int /*<<< orphan*/  szDirClass ; 
 int /*<<< orphan*/  szTreeControlClass ; 

BOOL
ResizeSplit(HWND hwnd, INT dxSplit)
{
   RECT rc;
   HWND hwndTree, hwndDir, hwndLB;

   GetTreeWindows(hwnd, &hwndTree, &hwndDir);

   if (hwndTree && GetWindowLongPtr(hwndTree, GWL_READLEVEL))
      return FALSE;

   GetClientRect(hwnd, &rc);

   if (dxSplit > dxDriveBitmap * 2) {

      if (!hwndTree) {        // make new tree window

         hwndTree = CreateWindowEx(0L,
                                   szTreeControlClass,
                                   NULL,
                                   WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                                   0, 0, 0, 0,
                                   hwnd,
                                   (HMENU)IDCW_TREECONTROL,
                                   hAppInstance, NULL);

         if (!hwndTree)
            return FALSE;

         //
         // only reset this if the dir window already
         // exists, that is we are creating the tree
         // by splitting open a dir window
         //
         if (hwndDir)
            SendMessage(hwndTree, TC_SETDRIVE, MAKEWORD(FALSE, 0), 0L);
      }
   } else {

      //
      // In this conditional, always set dxSplit=0.
      //
      if (hwndTree) {          // we are closing the tree window

         //
         // If the directory window is empty, then set the focus to the
         // drives window.
         //
         if (hwndDir) {
            hwndLB = GetDlgItem (hwndDir,IDCW_LISTBOX);
            if (hwndLB) {
               PVOID pv;
               SendMessage (hwndLB,LB_GETTEXT,0,(LPARAM)(LPTSTR) &pv);
               if (!pv)
                  SetFocus(hwndDriveBar);
            }
         }
         DestroyWindow(hwndTree);
      }
      dxSplit = 0;
   }

   if ((rc.right - dxSplit) > dxDriveBitmap * 2) {

      if (!hwndDir) {
         hwndDir = CreateWindowEx(0L,
                                  szDirClass,
                                  NULL,
                                  WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                                  0, 0, 0, 0,
                                  hwnd,
                                  (HMENU)IDCW_DIR,
                                  hAppInstance,
                                  NULL);
         if (!hwndDir)
            return FALSE;

      } else {

         //
         // Must invalidate: if viewing extreme left, paint residue left.
         //
         InvalidateRect(hwndDir, NULL, TRUE);
      }
   } else {

      //
      // Again, always set dxSplit
      //
      if (hwndDir) {
         DestroyWindow(hwndDir);
      }
      dxSplit = rc.right;
   }


   SetWindowLongPtr(hwnd, GWL_SPLIT, dxSplit);

   SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)GetTreeIcon(hwnd));

   UpdateStatus(hwnd);
   EnableCheckTBButtons(hwnd);

   return TRUE;
}