#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int left; int right; int top; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_2__*) ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 int /*<<< orphan*/  MK_RBUTTON ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 int /*<<< orphan*/  PostMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursorPos (int,int) ; 
 int /*<<< orphan*/  TREEVIEW_SEQ_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVGN_CARET ; 
 int /*<<< orphan*/  TVM_ENSUREVISIBLE ; 
 int /*<<< orphan*/  TVM_GETITEMRECT ; 
 int /*<<< orphan*/  TVM_GETNEXTITEM ; 
 int /*<<< orphan*/  TVM_SELECTITEM ; 
 int /*<<< orphan*/  WM_RBUTTONDOWN ; 
 int /*<<< orphan*/  WM_RBUTTONUP ; 
 int /*<<< orphan*/  create_treeview_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hChild ; 
 int /*<<< orphan*/  hMainWnd ; 
 scalar_t__ hRoot ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_right_click_seq ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  test_right_click_seq ; 

__attribute__((used)) static void test_right_click(void)
{
    HWND hTree;
    HTREEITEM selected;
    RECT rc;
    LRESULT result;
    POINT pt, orig_pos;

    hTree = create_treeview_control(0);
    fill_tree(hTree);

    SendMessageA(hTree, TVM_ENSUREVISIBLE, 0, (LPARAM)hChild);
    SendMessageA(hTree, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hChild);
    selected = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_CARET, 0);
    ok(selected == hChild, "child item not selected\n");

    *(HTREEITEM *)&rc = hRoot;
    result = SendMessageA(hTree, TVM_GETITEMRECT, TRUE, (LPARAM)&rc);
    ok(result, "TVM_GETITEMRECT failed\n");

    flush_events();

    pt.x = (rc.left + rc.right) / 2;
    pt.y = (rc.top + rc.bottom) / 2;
    ClientToScreen(hMainWnd, &pt);
    GetCursorPos(&orig_pos);
    SetCursorPos(pt.x, pt.y);

    flush_events();
    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    PostMessageA(hTree, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pt.x, pt.y));
    PostMessageA(hTree, WM_RBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));

    flush_events();

    ok_sequence(sequences, TREEVIEW_SEQ_INDEX, test_right_click_seq, "right click sequence", FALSE);
    ok_sequence(sequences, PARENT_SEQ_INDEX, parent_right_click_seq, "parent right click sequence", FALSE);

    selected = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_CARET, 0);
    ok(selected == hChild, "child item should still be selected\n");

    SetCursorPos(orig_pos.x, orig_pos.y);
    DestroyWindow(hTree);
}