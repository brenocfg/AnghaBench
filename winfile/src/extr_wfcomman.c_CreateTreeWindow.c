#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long style; void* lParam; void* cy; void* cx; void* y; void* x; int /*<<< orphan*/  hOwner; int /*<<< orphan*/  szTitle; int /*<<< orphan*/  szClass; } ;
typedef  TYPE_1__ MDICREATESTRUCT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  long LPARAM ;
typedef  void* INT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_ATTRIBS ; 
 int /*<<< orphan*/  GWL_SORT ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GWL_VIEW ; 
 int GetWindowLongPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_TOOMANYWINDOWS ; 
 int /*<<< orphan*/  IDS_WINFILE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_MDICREATE ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int WS_MAXIMIZE ; 
 int /*<<< orphan*/  dwNewAttribs ; 
 int /*<<< orphan*/  dwNewSort ; 
 int /*<<< orphan*/  dwNewView ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  hwndFrame ; 
 int /*<<< orphan*/  hwndMDIClient ; 
 int iNumWindows ; 
 int /*<<< orphan*/  szMessage ; 
 int /*<<< orphan*/  szTitle ; 
 int /*<<< orphan*/  szTreeClass ; 

HWND
CreateTreeWindow(
   LPWSTR szPath,
   INT x,
   INT y,
   INT dx,
   INT dy,
   INT dxSplit)
{
   MDICREATESTRUCT MDICS;
   HWND hwnd;

   //
   // this saves people from creating more windows than they should
   // note, when the mdi window is maximized many people don't realize
   // how many windows they have opened.
   //
   if (iNumWindows > 26) {

      LoadString(hAppInstance, IDS_WINFILE, szTitle, COUNTOF(szTitle));
      LoadString(hAppInstance, IDS_TOOMANYWINDOWS, szMessage, COUNTOF(szMessage));
      MessageBox(hwndFrame, szMessage, szTitle, MB_OK | MB_ICONEXCLAMATION);
      return NULL;
   }

   //
   // Create the Directory Tree window
   //
   MDICS.szClass = szTreeClass;
   MDICS.szTitle = szPath;
   MDICS.hOwner = hAppInstance;
   MDICS.style = 0L;

   MDICS.x  = x;
   MDICS.y  = y;
   MDICS.cx = dx;
   MDICS.cy = dy;

   MDICS.lParam = dxSplit;

   hwnd = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);
   if (hwnd && GetWindowLongPtr(hwnd, GWL_STYLE) & WS_MAXIMIZE)
      MDICS.style |= WS_MAXIMIZE;

   hwnd = (HWND)SendMessage(hwndMDIClient,
                            WM_MDICREATE,
                            0L, (LPARAM)&MDICS);

   //
   // Set all the view/sort/include parameters.  This is to make
   // sure these values get initialized in the case when there is
   // no directory window.
   //
   SetWindowLongPtr(hwnd, GWL_VIEW, dwNewView);
   SetWindowLongPtr(hwnd, GWL_SORT, dwNewSort);
   SetWindowLongPtr(hwnd, GWL_ATTRIBS, dwNewAttribs);

   return hwnd;
}