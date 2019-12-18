#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int left; int right; int top; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ DRIVEIND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  InflateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PtInRect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bDriveBar ; 
 scalar_t__ cDrives ; 
 int dxDrive ; 
 int /*<<< orphan*/  dyBorder ; 
 int dyDrive ; 
 scalar_t__ hwndDriveBar ; 

INT
DriveFromPoint(HWND hwnd, POINT pt)
{
   RECT rc, rcDrive;
   INT x, y;

   DRIVEIND driveInd;

   if (!bDriveBar || hwnd != hwndDriveBar)
      return -1;

   GetClientRect(hwndDriveBar, &rc);

   x = 0;
   y = 0;
   driveInd = 0;

   for (driveInd = 0; driveInd < cDrives; driveInd++) {
      rcDrive.left = x;
      rcDrive.right = x + dxDrive;
      rcDrive.top = y;
      rcDrive.bottom = y + dyDrive;
      InflateRect(&rcDrive, -dyBorder, -dyBorder);

      if (PtInRect(&rcDrive, pt))
         return driveInd;

      x += dxDrive;

      if (x + dxDrive > rc.right) {
         x = 0;
         y += dyDrive;
      }
   }

   return -1;      // no hit
}