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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int DRIVEBAR_FLAG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZENORMAL ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TOOLBAR_FLAG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SIZE ; 
 scalar_t__ bDriveBar ; 
 scalar_t__ bToolbar ; 
 int /*<<< orphan*/  hwndDriveBar ; 
 int /*<<< orphan*/  hwndFrame ; 
 int /*<<< orphan*/  hwndMDIClient ; 
 int /*<<< orphan*/  hwndToolbar ; 

VOID
MDIClientSizeChange(HWND hwndActive,INT iFlags)
{
   RECT rc;

   GetClientRect(hwndFrame, &rc);
   SendMessage(hwndFrame, WM_SIZE, SIZENORMAL, MAKELONG(rc.right, rc.bottom));
   UpdateStatus(hwndActive);

   InvalidateRect(hwndMDIClient, NULL, FALSE);

   if (bDriveBar && (iFlags & DRIVEBAR_FLAG))
      InvalidateRect(hwndDriveBar, NULL, TRUE);
   if (bToolbar && (iFlags & TOOLBAR_FLAG))
      InvalidateRect(hwndToolbar, NULL, TRUE);

   UpdateWindow(hwndFrame);
}