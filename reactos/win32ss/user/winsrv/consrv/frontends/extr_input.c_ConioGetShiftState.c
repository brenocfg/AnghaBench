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
typedef  int* PBYTE ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CAPSLOCK_ON ; 
 int /*<<< orphan*/  ENHANCED_KEY ; 
 int /*<<< orphan*/  LEFT_ALT_PRESSED ; 
 int /*<<< orphan*/  LEFT_CTRL_PRESSED ; 
 int /*<<< orphan*/  NUMLOCK_ON ; 
 int /*<<< orphan*/  RIGHT_ALT_PRESSED ; 
 int /*<<< orphan*/  RIGHT_CTRL_PRESSED ; 
 int /*<<< orphan*/  SCROLLLOCK_ON ; 
 int /*<<< orphan*/  SHIFT_PRESSED ; 
 size_t VK_CAPITAL ; 
 size_t VK_LCONTROL ; 
 size_t VK_LMENU ; 
 size_t VK_NUMLOCK ; 
 size_t VK_RCONTROL ; 
 size_t VK_RMENU ; 
 size_t VK_SCROLL ; 
 size_t VK_SHIFT ; 

__attribute__((used)) static DWORD
ConioGetShiftState(PBYTE KeyState, LPARAM lParam)
{
    DWORD ssOut = 0;

    if (KeyState[VK_CAPITAL] & 0x01)
        ssOut |= CAPSLOCK_ON;

    if (KeyState[VK_NUMLOCK] & 0x01)
        ssOut |= NUMLOCK_ON;

    if (KeyState[VK_SCROLL] & 0x01)
        ssOut |= SCROLLLOCK_ON;

    if (KeyState[VK_SHIFT] & 0x80)
        ssOut |= SHIFT_PRESSED;

    if (KeyState[VK_LCONTROL] & 0x80)
        ssOut |= LEFT_CTRL_PRESSED;
    if (KeyState[VK_RCONTROL] & 0x80)
        ssOut |= RIGHT_CTRL_PRESSED;

    if (KeyState[VK_LMENU] & 0x80)
        ssOut |= LEFT_ALT_PRESSED;
    if (KeyState[VK_RMENU] & 0x80)
        ssOut |= RIGHT_ALT_PRESSED;

    /* See WM_CHAR MSDN documentation for instance */
    if (lParam & 0x01000000)
        ssOut |= ENHANCED_KEY;

    return ssOut;
}