#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask; char* pszText; int iImage; } ;
typedef  TYPE_1__ TCITEMA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (int /*<<< orphan*/ ,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TCM_INSERTITEMA ; 
 int TCS_FOCUSNEVER ; 
 int /*<<< orphan*/  WC_TABCONTROLA ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 scalar_t__ hFont ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HWND
create_tabcontrol (DWORD style, DWORD mask)
{
    HWND handle;
    TCITEMA tcNewTab;
    static char text1[] = "Tab 1",
    text2[] = "Wide Tab 2",
    text3[] = "T 3";

    handle = CreateWindowA(WC_TABCONTROLA, "TestTab",
            WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TCS_FOCUSNEVER | style, 10, 10, 300, 100, NULL,
            NULL, NULL, 0);
    ok(handle != NULL, "failed to create tab wnd\n");

    SetWindowLongA(handle, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TCS_FOCUSNEVER | style);
    SendMessageA(handle, WM_SETFONT, 0, (LPARAM)hFont);

    tcNewTab.mask = mask;
    tcNewTab.pszText = text1;
    tcNewTab.iImage = 0;
    SendMessageA(handle, TCM_INSERTITEMA, 0, (LPARAM)&tcNewTab);
    tcNewTab.pszText = text2;
    tcNewTab.iImage = 1;
    SendMessageA(handle, TCM_INSERTITEMA, 1, (LPARAM)&tcNewTab);
    tcNewTab.pszText = text3;
    tcNewTab.iImage = 2;
    SendMessageA(handle, TCM_INSERTITEMA, 2, (LPARAM)&tcNewTab);

    if (winetest_interactive)
    {
        ShowWindow (handle, SW_SHOW);
        RedrawWindow (handle, NULL, 0, RDW_UPDATENOW);
        Sleep (1000);
    }

    return handle;
}