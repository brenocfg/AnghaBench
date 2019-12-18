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

/* Variables and functions */
 int /*<<< orphan*/  GetConsoleHwnd () ; 
 int /*<<< orphan*/  SetForegroundWindow (scalar_t__) ; 
 scalar_t__ s_hwnd ; 

void
win32_set_foreground()
{
# ifndef FEAT_GUI
    GetConsoleHwnd();	    /* get value of s_hwnd */
# endif
    if (s_hwnd != 0)
	SetForegroundWindow(s_hwnd);
}