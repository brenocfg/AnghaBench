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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ dwData; int /*<<< orphan*/  ptDrop; int /*<<< orphan*/  hwndSink; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ LPTSTR ;
typedef  TYPE_1__* LPDROPSTRUCT ;
typedef  long LPARAM ;
typedef  scalar_t__ HWND ;
typedef  size_t DRIVEIND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckEsc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMMoveCopyHelper (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t DriveFromPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/  GetSelectedDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIconic (scalar_t__) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RectDrive (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int /*<<< orphan*/  fShowSourceBitmaps ; 
 scalar_t__ hwndDropChild ; 
 scalar_t__ hwndMDIClient ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* rgiDrive ; 
 int /*<<< orphan*/  szStarDotStar ; 

VOID
DrivesDropObject(HWND hWnd, LPDROPSTRUCT lpds)
{
    DRIVEIND driveInd;
    TCHAR szPath[MAXPATHLEN * 2];
    LPTSTR pFrom;
    BOOL bIconic;
    HWND hwndChild;

    hwndChild = hwndDropChild ? hwndDropChild :
    (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);

    bIconic = IsIconic(hwndChild);

    if (bIconic) {
UseCurDir:
      SendMessage(hwndChild, FS_GETDIRECTORY, COUNTOF(szPath), (LPARAM)szPath);
    } else {

      driveInd = DriveFromPoint(lpds->hwndSink, lpds->ptDrop);

      if (driveInd < 0)
          goto UseCurDir;
      // this searches windows in the zorder then asks dos
      // if nothing is found...

      GetSelectedDirectory((WORD)(rgiDrive[driveInd] + 1), szPath);
    }
    AddBackslash(szPath);           // add spec part
    lstrcat(szPath, szStarDotStar);

    pFrom = (LPTSTR)lpds->dwData;

    CheckEsc(szPath);
    DMMoveCopyHelper(pFrom, szPath, fShowSourceBitmaps);

    if (!bIconic)
        RectDrive(driveInd, FALSE);
}