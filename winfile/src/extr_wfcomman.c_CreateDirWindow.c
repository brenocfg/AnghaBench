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
typedef  scalar_t__ LPWSTR ;
typedef  long LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DRIVE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (scalar_t__) ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 size_t CD_PATH ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CharUpperBuff (scalar_t__,int) ; 
 int /*<<< orphan*/  CreateTreeWindow (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ DRIVEID (scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FS_CHANGEDISPLAY ; 
 int /*<<< orphan*/  FS_GETFILESPEC ; 
 int /*<<< orphan*/  GET_WM_MDIACTIVATE_MPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t GetSplit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HasDirWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HasTreeWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocateDirWindow (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t MAXFILENAMELEN ; 
 size_t SC_RESTORE ; 
 int /*<<< orphan*/  SelectToolbarDrive (size_t) ; 
 size_t SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  StripFilespec (scalar_t__) ; 
 int /*<<< orphan*/  TC_SETDRIVE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_MDIACTIVATE ; 
 int /*<<< orphan*/  WM_SYSCOMMAND ; 
 size_t cDrives ; 
 int /*<<< orphan*/  hwndDriveList ; 
 int /*<<< orphan*/  hwndMDIClient ; 
 int /*<<< orphan*/  hwndSearch ; 
 int /*<<< orphan*/  lstrcat (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlen (scalar_t__) ; 
 scalar_t__* rgiDrive ; 
 int /*<<< orphan*/  szStarDotStar ; 

HWND
CreateDirWindow(
   register LPWSTR szPath,
   BOOL bReplaceOpen,
   HWND hwndActive)
{
   register HWND hwndT;
   INT dxSplit;

   if (hwndActive == hwndSearch) {
	   bReplaceOpen = FALSE;
	   dxSplit = -1;
   } else {
	   dxSplit = GetSplit(hwndActive);
   }

   //
   // Is a window with this path already open?
   //
   if (!bReplaceOpen && (hwndT = LocateDirWindow(szPath, TRUE, FALSE))) {

      SendMessage(hwndMDIClient, WM_MDIACTIVATE, GET_WM_MDIACTIVATE_MPS(0, 0, hwndT));
      if (IsIconic(hwndT))
         SendMessage(hwndT, WM_SYSCOMMAND, SC_RESTORE, 0L);
      return hwndT;
   }

   //
   // Are we replacing the contents of the currently active child?
   //
   if (bReplaceOpen) {
	   CharUpperBuff(szPath, 1);     // make sure

	   DRIVE drive = DRIVEID(szPath);
	   for (INT i = 0; i<cDrives; i++)
	   {
		   if (drive == rgiDrive[i])
		   {
			   // if not already selected, do so now
			   if (i != SendMessage(hwndDriveList, CB_GETCURSEL, i, 0L))
			   {
				   SelectToolbarDrive(i);
			   }
			   break;
		   }
	   }

	   if (hwndT = HasDirWindow(hwndActive))
	   {
		   AddBackslash(szPath);                   // default to all files
		   SendMessage(hwndT, FS_GETFILESPEC, MAXFILENAMELEN, (LPARAM)(szPath + lstrlen(szPath)));
		   SendMessage(hwndT, FS_CHANGEDISPLAY, CD_PATH, (LPARAM)szPath);
		   StripFilespec(szPath);
	   }

	   //
	   // update the tree if necessary
	   //
	   ;
	   if (hwndT = HasTreeWindow(hwndActive))
	   {
		   SendMessage(hwndT, TC_SETDRIVE, 0, (LPARAM)(szPath));
	   }

	   //
	   // Update the status in case we are "reading"
	   //
	   UpdateStatus(hwndActive);

	   return hwndActive;
   }

   AddBackslash(szPath);                   // default to all files
   lstrcat(szPath, szStarDotStar);

   //
   // create tree and/or dir based on current window split
   //
   hwndActive = CreateTreeWindow(szPath, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, dxSplit);

   // call TC_SETDRIVE like use of CreateTreeWindow in NewTree()
   if (hwndActive && (hwndT = HasTreeWindow(hwndActive)))
	   SendMessage(hwndT,
		   TC_SETDRIVE,
		   MAKELONG(MAKEWORD(FALSE, 0), TRUE),
		   0L);

   return hwndActive;
}