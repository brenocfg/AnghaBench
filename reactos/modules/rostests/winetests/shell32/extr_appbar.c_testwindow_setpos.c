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
struct TYPE_4__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct testwindow_info {int edge; TYPE_1__ allocated_rect; TYPE_1__ desired_rect; scalar_t__ to_be_deleted; int /*<<< orphan*/  registered; } ;
typedef  int /*<<< orphan*/  abd ;
struct TYPE_5__ {int cbSize; int uEdge; TYPE_1__ rc; int /*<<< orphan*/  hWnd; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_2__ APPBARDATA ;

/* Variables and functions */
#define  ABE_BOTTOM 131 
#define  ABE_LEFT 130 
#define  ABE_RIGHT 129 
#define  ABE_TOP 128 
 int /*<<< orphan*/  ABM_QUERYPOS ; 
 int /*<<< orphan*/  ABM_SETPOS ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 scalar_t__ GetWindowLongPtrA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SHAppBarMessage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testwindow_setpos(HWND hwnd)
{
    struct testwindow_info* info = (struct testwindow_info*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    APPBARDATA abd;
    BOOL ret;

    ok(info != NULL, "got unexpected ABN_POSCHANGED notification\n");

    if (!info || !info->registered)
    {
        return;
    }

    if (info->to_be_deleted)
    {
        win_skip("Some Win95 and NT4 systems send messages to removed taskbars\n");
        return;
    }

    abd.cbSize = sizeof(abd);
    abd.hWnd = hwnd;
    abd.uEdge = info->edge;
    abd.rc = info->desired_rect;
    ret = SHAppBarMessage(ABM_QUERYPOS, &abd);
    ok(ret == TRUE, "SHAppBarMessage returned %i\n", ret);
    switch (info->edge)
    {
        case ABE_BOTTOM:
            ok(info->desired_rect.top == abd.rc.top, "ABM_QUERYPOS changed top of rect from %i to %i\n", info->desired_rect.top, abd.rc.top);
            abd.rc.top = abd.rc.bottom - (info->desired_rect.bottom - info->desired_rect.top);
            break;
        case ABE_LEFT:
            ok(info->desired_rect.right == abd.rc.right, "ABM_QUERYPOS changed right of rect from %i to %i\n", info->desired_rect.right, abd.rc.right);
            abd.rc.right = abd.rc.left + (info->desired_rect.right - info->desired_rect.left);
            break;
        case ABE_RIGHT:
            ok(info->desired_rect.left == abd.rc.left, "ABM_QUERYPOS changed left of rect from %i to %i\n", info->desired_rect.left, abd.rc.left);
            abd.rc.left = abd.rc.right - (info->desired_rect.right - info->desired_rect.left);
            break;
        case ABE_TOP:
            ok(info->desired_rect.bottom == abd.rc.bottom, "ABM_QUERYPOS changed bottom of rect from %i to %i\n", info->desired_rect.bottom, abd.rc.bottom);
            abd.rc.bottom = abd.rc.top + (info->desired_rect.bottom - info->desired_rect.top);
            break;
    }

    ret = SHAppBarMessage(ABM_SETPOS, &abd);
    ok(ret == TRUE, "SHAppBarMessage returned %i\n", ret);

    info->allocated_rect = abd.rc;
    MoveWindow(hwnd, abd.rc.left, abd.rc.top, abd.rc.right-abd.rc.left, abd.rc.bottom-abd.rc.top, TRUE);
}