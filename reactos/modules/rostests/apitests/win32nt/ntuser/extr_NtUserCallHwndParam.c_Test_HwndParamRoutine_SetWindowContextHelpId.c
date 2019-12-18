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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  HWND_ROUTINE_GETWNDCONTEXTHLPID ; 
 int NtUserCallHwnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NtUserCallHwndParam (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _HWNDPARAM_ROUTINE_SETWNDCONTEXTHLPID ; 

void
Test_HwndParamRoutine_SetWindowContextHelpId(HWND hWnd)
{
    TEST(NtUserCallHwndParam(hWnd, 12345, _HWNDPARAM_ROUTINE_SETWNDCONTEXTHLPID) == TRUE);
    TEST(NtUserCallHwnd(hWnd, HWND_ROUTINE_GETWNDCONTEXTHLPID) == 12345);
}