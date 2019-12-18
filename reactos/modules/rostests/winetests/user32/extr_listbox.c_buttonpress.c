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
typedef  int WORD ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  MK_LBUTTON ; 
 int /*<<< orphan*/  REDRAW ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WAIT ; 
 int /*<<< orphan*/  WM_LBUTTONDOWN ; 
 int /*<<< orphan*/  WM_LBUTTONUP ; 

__attribute__((used)) static void
buttonpress (HWND handle, WORD x, WORD y)
{
  LPARAM lp=x+(y<<16);

  WAIT;
  SendMessageA(handle, WM_LBUTTONDOWN, MK_LBUTTON, lp);
  SendMessageA(handle, WM_LBUTTONUP, 0, lp);
  REDRAW;
}