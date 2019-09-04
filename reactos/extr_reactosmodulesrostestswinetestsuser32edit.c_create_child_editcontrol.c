#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRect (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreateWindowExA (int,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 char* szEditTextPositionClass ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HWND create_child_editcontrol (DWORD style, DWORD exstyle)
{
    HWND parentWnd;
    HWND editWnd;
    RECT rect;
    BOOL b;
    SetRect(&rect, 0, 0, 300, 300);
    b = AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    ok(b, "AdjustWindowRect failed\n");
    
    parentWnd = CreateWindowExA(0,
                            szEditTextPositionClass,
                            "Edit Test",
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            rect.right - rect.left, rect.bottom - rect.top,
                            NULL, NULL, hinst, NULL);
    ok (parentWnd != NULL, "CreateWindow EDIT Test failed\n");
    assert(parentWnd);

    editWnd = CreateWindowExA(exstyle,
                            "EDIT",
                            "Test Text",
                            WS_CHILD | style,
                            0, 0, 300, 300,
                            parentWnd, NULL, hinst, NULL);
    ok (editWnd != NULL, "CreateWindow EDIT Test Text failed\n");
    assert(editWnd);
    if (winetest_interactive)
        ShowWindow (parentWnd, SW_SHOW);
    return editWnd;
}