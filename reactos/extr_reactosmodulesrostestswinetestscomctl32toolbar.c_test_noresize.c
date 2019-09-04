#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int member_1; int member_2; int member_6; int idCommand; int fsState; int /*<<< orphan*/  member_5; TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ TBBUTTON ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int CCS_NORESIZE ; 
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int TBSTATE_ENABLED ; 
 int TBSTATE_WRAP ; 
 int TBSTYLE_WRAPABLE ; 
 int /*<<< orphan*/  TB_ADDBUTTONSA ; 
 int /*<<< orphan*/  TB_AUTOSIZE ; 
 int /*<<< orphan*/  TB_BUTTONSTRUCTSIZE ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 int /*<<< orphan*/  TB_SETSTATE ; 
 int /*<<< orphan*/  TOOLBARCLASSNAMEA ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 

__attribute__((used)) static void test_noresize(void)
{
    HWND wnd;
    int i;
    TBBUTTON button = {0, 10, TBSTATE_ENABLED, 0, {0, }, 0, -1};

    wnd = CreateWindowExA(0, TOOLBARCLASSNAMEA, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | TBSTYLE_WRAPABLE, 0, 0, 100, 20,
                          hMainWnd, (HMENU)5, GetModuleHandleA(NULL), NULL);
    SendMessageA(wnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

    for (i=0; i<30; i++)
    {
        button.idCommand = 10 + i;
        SendMessageA(wnd, TB_ADDBUTTONSA, 1, (LPARAM)&button);
    }

    SendMessageA(wnd, TB_SETSTATE, 10, TBSTATE_WRAP|TBSTATE_ENABLED);

    /* autosize clears the wrap on button 0 */
    SendMessageA(wnd, TB_AUTOSIZE, 0, 0);
    for (i=0; i<30; i++)
    {
        SendMessageA(wnd, TB_GETBUTTON, i, (LPARAM)&button);
        if (i % 4 == 3)
            ok(button.fsState == (TBSTATE_WRAP|TBSTATE_ENABLED), "%d: got %08x\n", i, button.fsState);
        else
            ok(button.fsState == TBSTATE_ENABLED, "%d: got %08x\n", i, button.fsState);
    }

    /* changing the parent doesn't do anything */
    MoveWindow(hMainWnd, 0,0, 400, 200, FALSE);
    for (i=0; i<30; i++)
    {
        SendMessageA(wnd, TB_GETBUTTON, i, (LPARAM)&button);
        if (i % 4 == 3)
            ok(button.fsState == (TBSTATE_WRAP|TBSTATE_ENABLED), "%d: got %08x\n", i, button.fsState);
        else
            ok(button.fsState == TBSTATE_ENABLED, "%d: got %08x\n", i, button.fsState);
    }

    /* again nothing here */
    SendMessageA(wnd, TB_AUTOSIZE, 0, 0);
    for (i=0; i<30; i++)
    {
        SendMessageA(wnd, TB_GETBUTTON, i, (LPARAM)&button);
        if (i % 4 == 3)
            ok(button.fsState == (TBSTATE_WRAP|TBSTATE_ENABLED), "%d: got %08x\n", i, button.fsState);
        else
            ok(button.fsState == TBSTATE_ENABLED, "%d: got %08x\n", i, button.fsState);
    }

    DestroyWindow(wnd);

}