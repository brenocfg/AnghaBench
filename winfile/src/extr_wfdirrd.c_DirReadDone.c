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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPXDTALINK ;
typedef  long LPARAM ;
typedef  long INT ;
typedef  scalar_t__ HWND ;
typedef  int EDIRABORT ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int EDIRABORT_READREQUEST ; 
 int EDIRABORT_WINDOWCLOSE ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_FLAGS ; 
 int /*<<< orphan*/  FS_TESTEMPTY ; 
 int /*<<< orphan*/  FillDirList (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GWL_HDTA ; 
 int /*<<< orphan*/  GWL_HDTAABORT ; 
 int /*<<< orphan*/  GWL_IERROR ; 
 int /*<<< orphan*/  GWL_NEXTHWND ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMDIWindowText (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ModifyWatchList (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPC_SET_INVALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (scalar_t__,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  StripFilespec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qFreeSpace ; 

LPXDTALINK
DirReadDone(
   HWND hwndDir,
   LPXDTALINK lpStart,
   INT iError)
{
   HWND hwndLB = GetDlgItem(hwndDir, IDCW_LISTBOX);
   HWND hwndParent = GetParent(hwndDir);
   WCHAR szPath[MAXPATHLEN];
   HWND hwndNext;


   EDIRABORT eDirAbort;

   eDirAbort = (EDIRABORT)GetWindowLongPtr(hwndDir, GWL_HDTAABORT);

   //
   // Last chance check for abort
   //
   if ((eDirAbort & (EDIRABORT_READREQUEST|EDIRABORT_WINDOWCLOSE)) ||
      GetWindowLongPtr(hwndDir, GWL_HDTA)) {

      //
      // We don't want it
      //
      return NULL;
   }

   GetMDIWindowText(hwndParent, szPath, COUNTOF(szPath));
   StripFilespec(szPath);

   ModifyWatchList(hwndParent,
                   szPath,
                   FILE_NOTIFY_CHANGE_FLAGS);

   SetWindowLongPtr(hwndDir, GWL_IERROR, iError);
   SetWindowLongPtr(hwndDir, GWL_HDTA, (LPARAM)lpStart);

   //
   // Remove the "reading" token
   //
   SendMessage(hwndLB, LB_DELETESTRING, 0, 0);

   FillDirList(hwndDir, lpStart);

   SetWindowLongPtr(hwndDir, GWLP_USERDATA, 0);

   hwndNext = (HWND)GetWindowLongPtr(hwndDir, GWL_NEXTHWND);
   if (hwndNext)
   {
       SendMessage(hwndDir, FS_TESTEMPTY, 0L, (LPARAM)hwndNext);
   }
   SetWindowLongPtr(hwndDir, GWL_NEXTHWND, 0L);

   //
   // Refresh display, but don't hit disk
   //
   SPC_SET_INVALID(qFreeSpace);

   return lpStart;
}