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
typedef  int /*<<< orphan*/  MEASUREITEMSTRUCT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_MEASUREITEM ; 
 int /*<<< orphan*/  create_rebar_control () ; 
 int g_parent_measureitem ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_notification(void)
{
    MEASUREITEMSTRUCT mis;
    HWND rebar;

    rebar = create_rebar_control();

    g_parent_measureitem = 0;
    SendMessageA(rebar, WM_MEASUREITEM, 0, (LPARAM)&mis);
    ok(g_parent_measureitem == 1, "got %d\n", g_parent_measureitem);

    DestroyWindow(rebar);
}