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
 int /*<<< orphan*/  BringWindowToTop (int /*<<< orphan*/ ) ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_RESTORE ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SYSCOMMAND ; 

void MakeWindowActive(HWND hwnd)
{
   if (IsIconic(hwnd))
      PostMessageW(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);

   BringWindowToTop(hwnd);  // same as: SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE); ?
   SetForegroundWindow(hwnd);
}