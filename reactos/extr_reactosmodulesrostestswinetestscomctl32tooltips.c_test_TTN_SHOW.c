#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int right; int left; int top; int bottom; } ;
struct TYPE_4__ {int cbSize; int uId; int lParam; int /*<<< orphan*/  rect; scalar_t__ lpszText; int /*<<< orphan*/  uFlags; int /*<<< orphan*/  hinst; int /*<<< orphan*/ * hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOA ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  MAKELPARAM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursorPos (int,int) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_CLASSA ; 
 int /*<<< orphan*/  TTDT_INITIAL ; 
 int /*<<< orphan*/  TTF_SUBCLASS ; 
 int /*<<< orphan*/  TTM_ADDTOOLA ; 
 int /*<<< orphan*/  TTM_SETDELAYTIME ; 
 int /*<<< orphan*/  TTS_ALWAYSTIP ; 
 int /*<<< orphan*/  WS_EX_TOPMOST ; 
 int /*<<< orphan*/ * create_parent_window () ; 
 int /*<<< orphan*/  flush_events (int) ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  ttn_show_parent_seq ; 

__attribute__((used)) static void test_TTN_SHOW(void)
{
    HWND hwndTip, hwnd;
    TTTOOLINFOA ti;
    RECT rect;
    BOOL ret;

    hwnd = create_parent_window();
    ok(hwnd != NULL, "Failed to create parent window.\n");

    /* Put cursor outside the window */
    GetWindowRect(hwnd, &rect);
    SetCursorPos(rect.right + 200, 0);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    flush_events(100);

    /* Create tooltip */
    hwndTip = CreateWindowExA(WS_EX_TOPMOST, TOOLTIPS_CLASSA, NULL, TTS_ALWAYSTIP, 10, 10, 300, 300,
        hwnd, NULL, NULL, 0);
    ok(hwndTip != NULL, "Failed to create tooltip window.\n");

    SetWindowPos(hwndTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    ti.cbSize = sizeof(TTTOOLINFOA);
    ti.hwnd = hwnd;
    ti.hinst = GetModuleHandleA(NULL);
    ti.uFlags = TTF_SUBCLASS;
    ti.uId = 0x1234abcd;
    ti.lpszText = (LPSTR)"This is a test tooltip";
    ti.lParam = 0xdeadbeef;
    GetClientRect(hwnd, &ti.rect);
    ret = SendMessageA(hwndTip, TTM_ADDTOOLA, 0, (LPARAM)&ti);
    ok(ret, "Failed to add a tool.\n");

    /* Make tooltip appear quickly */
    SendMessageA(hwndTip, TTM_SETDELAYTIME, TTDT_INITIAL, MAKELPARAM(1, 0));

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    /* Put cursor inside window, tooltip will appear immediately */
    GetWindowRect(hwnd, &rect);
    SetCursorPos((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
    flush_events(200);

    ok_sequence(sequences, PARENT_SEQ_INDEX, ttn_show_parent_seq, "TTN_SHOW parent seq", FALSE);

    DestroyWindow(hwndTip);
    DestroyWindow(hwnd);
}