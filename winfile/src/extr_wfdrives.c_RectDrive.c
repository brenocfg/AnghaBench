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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  DRIVEIND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WINDOWTEXT ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDriveRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyBorder ; 
 int /*<<< orphan*/  hwndDriveBar ; 

VOID
RectDrive(DRIVEIND driveInd, BOOL bDraw)
{
   RECT rc, rcDrive;
   HBRUSH hBrush;
   HDC hdc;

   GetDriveRect(driveInd, &rc);
   rcDrive = rc;
   InflateRect(&rc, -dyBorder, -dyBorder);

   if (bDraw) {

      hdc = GetDC(hwndDriveBar);

      if (hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOWTEXT))) {
         FrameRect(hdc, &rc, hBrush);
         DeleteObject(hBrush);
      }

      ReleaseDC(hwndDriveBar, hdc);

   } else {
      InvalidateRect(hwndDriveBar, &rcDrive, TRUE);
      UpdateWindow(hwndDriveBar);
   }
}