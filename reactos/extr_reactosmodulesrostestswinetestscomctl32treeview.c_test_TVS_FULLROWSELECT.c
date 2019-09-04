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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TVS_FULLROWSELECT ; 
 int TVS_HASLINES ; 
 int /*<<< orphan*/  create_treeview_control (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_TVS_FULLROWSELECT(void)
{
    DWORD style;
    HWND hwnd;

    /* try to create both with TVS_HASLINES and TVS_FULLROWSELECT */
    hwnd = create_treeview_control(TVS_FULLROWSELECT);

    style = GetWindowLongA(hwnd, GWL_STYLE);
    ok((style & (TVS_FULLROWSELECT | TVS_HASLINES)) == (TVS_FULLROWSELECT | TVS_HASLINES), "got style 0x%08x\n", style);

    DestroyWindow(hwnd);

    /* create just with TVS_HASLINES, try to enable TVS_FULLROWSELECT later */
    hwnd = create_treeview_control(0);

    style = GetWindowLongA(hwnd, GWL_STYLE);
    SetWindowLongA(hwnd, GWL_STYLE, style | TVS_FULLROWSELECT);
    style = GetWindowLongA(hwnd, GWL_STYLE);
    ok(style & TVS_FULLROWSELECT, "got style 0x%08x\n", style);

    DestroyWindow(hwnd);
}