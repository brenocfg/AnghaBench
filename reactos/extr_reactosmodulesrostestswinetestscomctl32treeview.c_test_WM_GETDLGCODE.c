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
 int DLGC_WANTARROWS ; 
 int DLGC_WANTCHARS ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_TAB ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 
 int /*<<< orphan*/  create_treeview_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_WM_GETDLGCODE(void)
{
    DWORD code;
    HWND hTree;

    hTree = create_treeview_control(0);

    code = SendMessageA(hTree, WM_GETDLGCODE, VK_TAB, 0);
    ok(code == (DLGC_WANTCHARS | DLGC_WANTARROWS), "0x%08x\n", code);

    DestroyWindow(hTree);
}