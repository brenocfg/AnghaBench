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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWL_ATTRIBS ; 
 int /*<<< orphan*/  GWL_HDTA ; 
 int /*<<< orphan*/  GWL_IERROR ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GetMDIWindowText (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HasDirWindow (scalar_t__) ; 
 scalar_t__ IDS_NOFILES ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/ * MemClone (int /*<<< orphan*/ *) ; 
 scalar_t__ hwndMDIClient ; 
 int /*<<< orphan*/  lstrcmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

LPXDTALINK
StealDTABlock(
   HWND hwndCur,
   LPWSTR pPath,
   DWORD dwAttribs)
{
   HWND hwndDir;
   HWND hwnd;
   WCHAR szPath[MAXPATHLEN];

   LPXDTALINK lpStart, lpStartCopy;
   INT iError;

   for (hwnd = GetWindow(hwndMDIClient, GW_CHILD);
      hwnd;
      hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {

      if ((hwndDir = HasDirWindow(hwnd)) && (hwndDir != hwndCur)) {

         GetMDIWindowText(hwnd, szPath, COUNTOF(szPath));

         if ((dwAttribs == (DWORD)GetWindowLongPtr(hwnd, GWL_ATTRIBS)) &&
            !lstrcmpi(pPath, szPath) &&
            (lpStart = (LPXDTALINK)GetWindowLongPtr(hwndDir, GWL_HDTA))) {

            iError = (INT)GetWindowLongPtr(hwndDir, GWL_IERROR);
            if (!iError || IDS_NOFILES == iError) {

               lpStartCopy = MemClone(lpStart);

               return lpStartCopy;
            }
         }
      }
   }

   return NULL;
}