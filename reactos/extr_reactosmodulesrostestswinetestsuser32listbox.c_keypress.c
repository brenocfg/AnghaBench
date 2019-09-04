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
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int KEYEVENTF_EXTENDEDKEY ; 
 int /*<<< orphan*/  REDRAW ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WAIT ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int /*<<< orphan*/  WM_KEYUP ; 

__attribute__((used)) static void
keypress (HWND handle, WPARAM keycode, BYTE scancode, BOOL extended)
{
  LPARAM lp=1+(scancode<<16)+(extended?KEYEVENTF_EXTENDEDKEY:0);

  WAIT;
  SendMessageA(handle, WM_KEYDOWN, keycode, lp);
  SendMessageA(handle, WM_KEYUP  , keycode, lp | 0xc000000);
  REDRAW;
}