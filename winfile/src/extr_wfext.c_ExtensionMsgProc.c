#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
typedef  long LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DrawMenuBar (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 long FMFOCUS_DIR ; 
 long FMFOCUS_DRIVES ; 
 long FMFOCUS_SEARCH ; 
 long FMFOCUS_TREE ; 
#define  FM_GETDRIVEINFOA 138 
#define  FM_GETDRIVEINFOW 137 
#define  FM_GETFILESELA 136 
#define  FM_GETFILESELLFNA 135 
#define  FM_GETFILESELLFNW 134 
#define  FM_GETFILESELW 133 
#define  FM_GETFOCUS 132 
#define  FM_GETSELCOUNT 131 
#define  FM_GETSELCOUNTLFN 130 
#define  FM_REFRESH_WINDOWS 129 
#define  FM_RELOAD_EXTENSIONS 128 
 int /*<<< orphan*/  FreeExtensions () ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GW_OWNER ; 
 long GetDriveInfo (scalar_t__,int,int /*<<< orphan*/ ) ; 
 long GetExtSelection (scalar_t__,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetTreeFocus (scalar_t__) ; 
 int /*<<< orphan*/  GetTreeWindows (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitExtensions () ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RefreshWindow (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPC_SET_HITDISK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SaveRestoreToolbar (int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateDriveList () ; 
 int /*<<< orphan*/  UpdateStatus (scalar_t__) ; 
 int /*<<< orphan*/  WM_CANCELMODE ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 
 scalar_t__ hwndDriveBar ; 
 scalar_t__ hwndFrame ; 
 scalar_t__ hwndMDIClient ; 
 scalar_t__ hwndSearch ; 
 scalar_t__ hwndToolbar ; 
 int /*<<< orphan*/  qFreeSpace ; 

LRESULT
ExtensionMsgProc(UINT wMsg, WPARAM wParam, LPARAM lParam)
{
   HWND hwndActive;
   HWND hwndTree, hwndDir, hwndFocus;

   hwndActive = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);
   GetTreeWindows(hwndActive, &hwndTree, &hwndDir);

   switch (wMsg) {

   case FM_RELOAD_EXTENSIONS:
      SendMessage(hwndFrame, WM_CANCELMODE, 0, 0L);

      SaveRestoreToolbar(TRUE);
      SendMessage(hwndToolbar, WM_SETREDRAW, FALSE, 0L);

      FreeExtensions();

      InitExtensions();
      SaveRestoreToolbar(FALSE);

      SendMessage(hwndToolbar, WM_SETREDRAW, TRUE, 0L);
      InvalidateRect(hwndToolbar, NULL, TRUE);

      DrawMenuBar(hwndFrame);
      break;

   case FM_GETFOCUS:
      // wParam       unused
      // lParam       unused
      // return       window tyep with focus

      if (hwndActive == hwndSearch)
         return FMFOCUS_SEARCH;

      hwndFocus = GetTreeFocus(hwndActive);

      if (hwndFocus == hwndTree)
         return FMFOCUS_TREE;
      else if (hwndFocus == hwndDir)
         return FMFOCUS_DIR;
      else if (hwndFocus == hwndDriveBar)
         return FMFOCUS_DRIVES;
      break;

   case FM_GETDRIVEINFOA:
   case FM_GETDRIVEINFOW:

      // wParam       unused
      // lParam       LPFMS_GETDRIVEINFO structure to be filled in

      return GetDriveInfo(hwndActive, wMsg, lParam);
      break;

   case FM_REFRESH_WINDOWS:
      // wParam       0 refresh the current window
      //              non zero refresh all windows
      // lParam       unused


      //
      // Note: For all windows that it refreshes,
      // it requests a WNetGetDirectoryType flush cache.

      UpdateDriveList();

      if (wParam == 0) {
         RefreshWindow(hwndActive, FALSE, TRUE);
      } else {
         HWND hwndT, hwndNext;

         hwndT = GetWindow(hwndMDIClient, GW_CHILD);
         while (hwndT) {
            hwndNext = GetWindow(hwndT, GW_HWNDNEXT);

            if (!GetWindow(hwndT, GW_OWNER)) {

               RefreshWindow(hwndT, FALSE, TRUE);
            }
            hwndT = hwndNext;
         }
      }

      SPC_SET_HITDISK(qFreeSpace);
      UpdateStatus(hwndActive);
      break;

   case FM_GETSELCOUNT:
   case FM_GETSELCOUNTLFN:
      // wParam       unused
      // lParam       unused
      // return       # of selected items

   case FM_GETFILESELA:
   case FM_GETFILESELW:
   case FM_GETFILESELLFNA:
   case FM_GETFILESELLFNW:

      // wParam       index of selected item to get
      // lParam       LPFMS_GETFILESEL structure to be filled in

      if (hwndActive != hwndSearch && !hwndDir)
         return 0L;

      // note, this uses the fact that LFN messages are odd!

      return GetExtSelection(hwndActive, (UINT)wParam, lParam,
         hwndActive == hwndSearch, (wMsg & ~1) == FM_GETSELCOUNT,
         (BOOL)(wMsg & 1),
         (wMsg == FM_GETFILESELW || wMsg == FM_GETFILESELLFNW));
   }

   return 0;
}