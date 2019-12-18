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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  DRIVEIND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SETCURSEL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GWL_CURDRIVEIND ; 
 int /*<<< orphan*/  RefreshToolbarDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 
 int /*<<< orphan*/  hwndDriveBar ; 
 int /*<<< orphan*/  hwndDriveList ; 

VOID
SelectToolbarDrive(DRIVEIND DriveInd)
{

   //
   // Turn off\on redrawing.
   //

   SendMessage(hwndDriveList, WM_SETREDRAW, (WPARAM)FALSE, 0L);
   RefreshToolbarDrive(DriveInd);

   SendMessage(hwndDriveList, WM_SETREDRAW, (WPARAM)TRUE, 0L);
   SendMessage(hwndDriveList, CB_SETCURSEL, DriveInd, 0L);

   //
   // Move focus of drivebar
   //
   SetWindowLongPtr(hwndDriveBar, GWL_CURDRIVEIND, DriveInd);
}