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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckTBButton (int) ; 
 int /*<<< orphan*/  GWL_SORT ; 
 int /*<<< orphan*/  GWL_TYPE ; 
 int /*<<< orphan*/  GWL_VIEW ; 
 int GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HasDirWindow (scalar_t__) ; 
 int IDD_NAME ; 
 scalar_t__ IDM_BYDATE ; 
 int IDM_BYNAME ; 
 int IDM_VDETAILS ; 
 int IDM_VNAME ; 
 int IDM_VOTHER ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  SwitchDriveSelection (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_ENABLEBUTTON ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatus (scalar_t__) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
#define  VIEW_EVERYTHING 129 
#define  VIEW_NAMEONLY 128 
 scalar_t__ hwndSearch ; 
 int /*<<< orphan*/  hwndToolbar ; 

VOID
EnableCheckTBButtons(HWND hwndActive)
{
   DWORD dwSort;
   BOOL fEnable;
   INT  iButton;

   // If the active window is the search window, clear the selection
   // in the drive list.

   if (hwndActive == hwndSearch) {

      SwitchDriveSelection(hwndSearch, TRUE);
      UpdateStatus(hwndSearch);
   }

   // Check or uncheck the sort-by and view-details buttons based
   // on the settings for the active window.

   switch (GetWindowLongPtr(hwndActive, GWL_VIEW) & VIEW_EVERYTHING) {
   case VIEW_NAMEONLY:
      CheckTBButton(IDM_VNAME);
      break;

   case VIEW_EVERYTHING:
      CheckTBButton(IDM_VDETAILS);
      break;

   default:
      CheckTBButton(IDM_VOTHER);
      break;
   }

   // Now do the sort-by buttons.  While we're at it, disable them all
   // if the active window is a search window or lacks a directory pane,
   // else enable them all.

   dwSort = GetWindowLongPtr(hwndActive, GWL_SORT) - IDD_NAME + IDM_BYNAME;

   fEnable = ((int)GetWindowLongPtr(hwndActive, GWL_TYPE) >= 0 &&
      HasDirWindow(hwndActive));

   CheckTBButton(dwSort);
   for (iButton=IDM_BYNAME; iButton<=IDM_BYDATE; ++iButton) {
      SendMessage(hwndToolbar, TB_ENABLEBUTTON, iButton, fEnable);
   }

   UpdateWindow(hwndToolbar);
}