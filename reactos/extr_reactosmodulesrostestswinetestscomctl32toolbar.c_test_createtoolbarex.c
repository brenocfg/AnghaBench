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
typedef  int /*<<< orphan*/  btns ;
typedef  int /*<<< orphan*/  TBBUTTON ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_IMAGELIST (int,int,int) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDB_BITMAP_128x15 ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_GETBUTTONSIZE ; 
 int /*<<< orphan*/  WS_VISIBLE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  compare (int,int,char*) ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  pCreateToolbarEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

__attribute__((used)) static void test_createtoolbarex(void)
{
    HWND hToolbar;
    TBBUTTON btns[3];
    ZeroMemory(&btns, sizeof(btns));

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, 20, 20, 16, 16, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 20, 20);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0x1a001b, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, 4, 4, 16, 16, sizeof(TBBUTTON));
    CHECK_IMAGELIST(32, 4, 4);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0xa000b, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, 0, 8, 12, 12, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 12, 12);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0x120013, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, -1, 8, 12, 12, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 12, 8);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0xe0013, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, -1, 8, -1, 12, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 16, 8);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0xe0017, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, 0, 0, 12, -1, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 12, 16);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0x160013, "%x");
    DestroyWindow(hToolbar);

    hToolbar = pCreateToolbarEx(hMainWnd, WS_VISIBLE, 1, 16, GetModuleHandleA(NULL), IDB_BITMAP_128x15, btns,
        3, 0, 0, 0, 12, sizeof(TBBUTTON));
    CHECK_IMAGELIST(16, 16, 16);
    compare((int)SendMessageA(hToolbar, TB_GETBUTTONSIZE, 0, 0), 0x160017, "%x");
    DestroyWindow(hToolbar);
}