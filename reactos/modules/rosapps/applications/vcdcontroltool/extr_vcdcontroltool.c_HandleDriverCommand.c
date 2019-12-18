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
typedef  int WORD ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
#define  IDC_DRIVEROK 130 
#define  IDC_DRIVERSTART 129 
#define  IDC_DRIVERSTOP 128 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartDriver () ; 
 int /*<<< orphan*/  StopDriver () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hDriverWnd ; 

__attribute__((used)) static
INT_PTR
HandleDriverCommand(WPARAM wParam,
                    LPARAM lParam)
{
    WORD Msg;

    /* Dispatch the message for the controls we manage */
    Msg = LOWORD(wParam);
    switch (Msg)
    {
        case IDC_DRIVEROK:
            DestroyWindow(hDriverWnd);
            return TRUE;

        case IDC_DRIVERSTART:
            StartDriver();
            return TRUE;

        case IDC_DRIVERSTOP:
            StopDriver();
            return TRUE;
    }

    return FALSE;
}