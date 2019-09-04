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
 int /*<<< orphan*/  NtUserCallHwndLock (int /*<<< orphan*/ ,int) ; 

void
Test_HwndLockRoutine_GetSysMenuHandle(HWND hWnd) /* 0x57 */
{
    NtUserCallHwndLock(hWnd, 0x5c);
//  HMENU hMenu = (HMENU)NtUserCallHwndLock(hWnd, 0x57);
//  TEST(hMenu != 0);

}