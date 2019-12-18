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
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_DRIVERSTART ; 
 int /*<<< orphan*/  IDC_DRIVERSTOP ; 
 int /*<<< orphan*/  hDriverWnd ; 

VOID
SetServiceState(BOOLEAN Started)
{
    HWND hControl;

    /* If started, disable start button */
    hControl = GetDlgItem(hDriverWnd, IDC_DRIVERSTART);
    EnableWindow(hControl, !Started);

    /* If started, enable stop button */
    hControl = GetDlgItem(hDriverWnd, IDC_DRIVERSTOP);
    EnableWindow(hControl, Started);
}