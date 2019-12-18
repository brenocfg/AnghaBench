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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVEBAR_FLAG ; 
 int /*<<< orphan*/  MDIClientSizeChange (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
RepaintDriveWindow(HWND hwndChild)
{
   MDIClientSizeChange(hwndChild,DRIVEBAR_FLAG);
}