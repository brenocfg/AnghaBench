#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_7__ {int nSplit; int /*<<< orphan*/  sw; TYPE_2__ pt; TYPE_1__ rc; scalar_t__* szDir; int /*<<< orphan*/  dwAttribs; int /*<<< orphan*/  dwSort; int /*<<< orphan*/  dwView; } ;
typedef  TYPE_3__ WINDOW ;
typedef  scalar_t__ WCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (scalar_t__*) ; 
 int /*<<< orphan*/  COUNTOF (scalar_t__*) ; 
 scalar_t__ CW_USEDEFAULT ; 
 int /*<<< orphan*/  CheckDirExists (scalar_t__*) ; 
 int /*<<< orphan*/  CreateTreeWindow (scalar_t__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetPrivateProfileString (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSavedWindow (scalar_t__*,TYPE_3__*) ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripBackslash (scalar_t__*) ; 
 int /*<<< orphan*/  StripFilespec (scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dwNewAttribs ; 
 int /*<<< orphan*/  dwNewSort ; 
 int /*<<< orphan*/  dwNewView ; 
 int /*<<< orphan*/  lstrcat (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  szDirKeyFormat ; 
 int /*<<< orphan*/  szNULL ; 
 scalar_t__* szOriginalDirPath ; 
 int /*<<< orphan*/  szSettings ; 
 int /*<<< orphan*/  szStarDotStar ; 
 int /*<<< orphan*/  szTheINIFile ; 
 int /*<<< orphan*/  wsprintf (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
CreateSavedWindows()
{
   WCHAR buf[2*MAXPATHLEN+7*7], key[10];
   WINDOW win;

   //
   // since win.szDir is bigger.
   //
   WCHAR szDir[2*MAXPATHLEN];

   INT nDirNum;
   HWND hwnd;
   INT iNumTrees;

   //
   // make sure this thing exists so we don't hit drives that don't
   // exist any more
   //
   nDirNum = 1;
   iNumTrees = 0;

   do {
      wsprintf(key, szDirKeyFormat, nDirNum++);

      GetPrivateProfileString(szSettings, key, szNULL, buf, COUNTOF(buf), szTheINIFile);

      if (*buf) {

         GetSavedWindow(buf, &win);

         //
         // clean off some junk so we
         // can do this test
         //
         lstrcpy(szDir, win.szDir);
         StripFilespec(szDir);
         StripBackslash(szDir);

         if (!CheckDirExists(szDir))
            continue;

         dwNewView = win.dwView;
         dwNewSort = win.dwSort;
         dwNewAttribs = win.dwAttribs;

         hwnd = CreateTreeWindow(win.szDir,
                                 win.rc.left,
                                 win.rc.top,
                                 win.rc.right - win.rc.left,
                                 win.rc.bottom - win.rc.top,
                                 win.nSplit);

         if (!hwnd) {
            continue;
         }

         iNumTrees++;

         //
         // keep track of this for now...
         //
         if (IsIconic(hwnd))
             SetWindowPos(hwnd, NULL, win.pt.x, win.pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

         ShowWindow(hwnd, win.sw);
      }

   } while (*buf);

   //
   // if nothing was saved create a tree for the current drive
   //
   if (!iNumTrees) {

      lstrcpy(buf, szOriginalDirPath);
      AddBackslash(buf);
      lstrcat(buf, szStarDotStar);

      //
      // default to split window
      //
      hwnd = CreateTreeWindow(buf, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, -1);

      if (!hwnd)
         return FALSE;

      iNumTrees++;
   }

   return TRUE;
}