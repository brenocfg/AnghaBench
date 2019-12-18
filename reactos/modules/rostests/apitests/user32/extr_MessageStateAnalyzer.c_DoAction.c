#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_3__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
#define  ACTION_ACTIVATE 139 
#define  ACTION_DEACTIVATE 138 
#define  ACTION_DESTROY 137 
#define  ACTION_FIRSTMINMAX 136 
#define  ACTION_HIDE 135 
#define  ACTION_IME_NOTIFY_CLOSE 134 
#define  ACTION_IME_NOTIFY_OPEN 133 
#define  ACTION_IME_SETCONTEXT_CLOSE 132 
#define  ACTION_IME_SETCONTEXT_OPEN 131 
#define  ACTION_NCCREATE 130 
#define  ACTION_SHOW 129 
#define  ACTION_ZERO 128 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HEIGHT ; 
 int /*<<< orphan*/  IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_long (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_iStep ; 

__attribute__((used)) static void DoAction(HWND hwnd, INT iAction, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    switch (iAction)
    {
        case ACTION_ZERO:
            /* does nothing */
            break;
        case ACTION_FIRSTMINMAX:
            GetWindowRect(hwnd, &rc);
            ok_long(rc.right - rc.left, 0);
            ok_long(rc.bottom - rc.top, 0);
            ok_int(IsWindowVisible(hwnd), FALSE);
            break;
        case ACTION_NCCREATE:
            GetWindowRect(hwnd, &rc);
            ok_long(rc.right - rc.left, WIDTH);
            ok_long(rc.bottom - rc.top, HEIGHT);
            ok_int(IsWindowVisible(hwnd), FALSE);
            break;
        case ACTION_SHOW:
            ShowWindow(hwnd, SW_SHOWNORMAL);
            break;
        case ACTION_IME_SETCONTEXT_OPEN:
            ok(wParam == 1, "Step %d: wParam was %p\n", s_iStep, (void *)wParam);
            ok(lParam == 0xC000000F, "Step %d: lParam was %p\n", s_iStep, (void *)lParam);
            break;
        case ACTION_IME_NOTIFY_OPEN:
            ok(wParam == 2, "Step %d: wParam was %p\n", s_iStep, (void *)wParam);
            ok(lParam == 0, "Step %d: lParam was %p\n", s_iStep, (void *)lParam);
            break;
        case ACTION_DESTROY:
            DestroyWindow(hwnd);
            break;
        case ACTION_IME_SETCONTEXT_CLOSE:
            ok(wParam == 0, "Step %d: wParam was %p\n", s_iStep, (void *)wParam);
            ok(lParam == 0xC000000F, "Step %d: lParam was %p\n", s_iStep, (void *)lParam);
            break;
        case ACTION_IME_NOTIFY_CLOSE:
            ok(wParam == 1, "Step %d: wParam was %p\n", s_iStep, (void *)wParam);
            ok(lParam == 0, "Step %d: lParam was %p\n", s_iStep, (void *)lParam);
            break;
        case ACTION_HIDE:
            ShowWindow(hwnd, SW_HIDE);
            break;
        case ACTION_DEACTIVATE:
            SetForegroundWindow(GetDesktopWindow());
            break;
        case ACTION_ACTIVATE:
            SetForegroundWindow(hwnd);
            break;
    }
}