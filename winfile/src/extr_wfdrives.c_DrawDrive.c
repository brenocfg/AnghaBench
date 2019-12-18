#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  iOffset; } ;
struct TYPE_7__ {int left; int right; int top; int bottom; } ;
typedef  scalar_t__ TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  size_t DRIVEIND ;
typedef  size_t DRIVE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  COLOR_BTNTEXT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawFocusRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (TYPE_1__*,int,int) ; 
 int NOMIRRORBITMAP ; 
 int SRCCOPY ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int,int,scalar_t__*,int) ; 
 TYPE_2__* aDriveInfo ; 
 size_t chFirstDrive ; 
 int dxDrive ; 
 int dxDriveBitmap ; 
 int dyBorder ; 
 int dyDrive ; 
 int dyDriveBitmap ; 
 int dyFolder ; 
 int dyText ; 
 int /*<<< orphan*/  hdcMem ; 
 size_t* rgiDrive ; 

VOID
DrawDrive(HDC hdc, INT x, INT y, DRIVEIND driveInd, BOOL bCurrent, BOOL bFocus)
{
   RECT rc;
   TCHAR szTemp[2];
   DWORD rgb;
   DRIVE drive;

   drive = rgiDrive[driveInd];

   rc.left = x;
   rc.right = x + dxDrive;
   rc.top = y;
   rc.bottom = y + dyDrive;

   rgb = GetSysColor(COLOR_BTNTEXT);

   if (bCurrent) {
      HBRUSH hbr;

      if (hbr = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT))) {
         if (bFocus) {
            rgb = GetSysColor(COLOR_HIGHLIGHTTEXT);
            FillRect(hdc, &rc, hbr);
         } else {
            InflateRect(&rc, -dyBorder, -dyBorder);
            FrameRect(hdc, &rc, hbr);
         }
         DeleteObject(hbr);
      }
   }

   if (bFocus)
      DrawFocusRect(hdc, &rc);

   szTemp[0] = (TCHAR)(chFirstDrive + rgiDrive[driveInd]);
   SetBkMode(hdc, TRANSPARENT);

   rgb = SetTextColor(hdc, rgb);
   TextOut(hdc, x + dxDriveBitmap+(dyBorder*6), y + (dyDrive - dyText) / 2, szTemp, 1);
   SetTextColor(hdc, rgb);

   BitBlt(hdc, x + 4*dyBorder, y + (dyDrive - dyDriveBitmap) / 2, dxDriveBitmap, dyDriveBitmap,
      hdcMem, aDriveInfo[drive].iOffset, 2 * dyFolder, SRCCOPY | NOMIRRORBITMAP);
}