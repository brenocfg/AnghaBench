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
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CheckSize (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  MAKELPARAM (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCM_SETITEMSIZE ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void TabCheckSetSize(HWND hwnd, INT set_width, INT set_height, INT exp_width,
    INT exp_height, const char *msg, int line)
{
    SendMessageA(hwnd, TCM_SETITEMSIZE, 0,
            MAKELPARAM((set_width >= 0) ? set_width : 0, (set_height >= 0) ? set_height : 0));
    if (winetest_interactive) RedrawWindow (hwnd, NULL, 0, RDW_UPDATENOW);
    CheckSize(hwnd, exp_width, exp_height, msg, line);
}