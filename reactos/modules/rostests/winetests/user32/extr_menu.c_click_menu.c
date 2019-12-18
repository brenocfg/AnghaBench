#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct menu_item_pair_s {size_t uMenu; int /*<<< orphan*/  uItem; } ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_10__ {int left; int top; } ;
struct TYPE_7__ {int dx; int dy; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_8__ {TYPE_1__ mi; } ;
struct TYPE_9__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ TEST_INPUT ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  INPUT ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetMenuItemRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_MOUSE ; 
 int /*<<< orphan*/  MOUSEEVENTF_ABSOLUTE ; 
 int /*<<< orphan*/  MOUSEEVENTF_LEFTDOWN ; 
 int /*<<< orphan*/  MOUSEEVENTF_LEFTUP ; 
 int /*<<< orphan*/  MOUSEEVENTF_MOVE ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/ * hMenus ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pSendInput (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL click_menu(HANDLE hWnd, struct menu_item_pair_s *mi)
{
    HMENU hMenu = hMenus[mi->uMenu];
    TEST_INPUT i[3];
    MSG msg;
    RECT r;
    int screen_w = GetSystemMetrics(SM_CXSCREEN);
    int screen_h = GetSystemMetrics(SM_CYSCREEN);
    BOOL ret = GetMenuItemRect(mi->uMenu > 2 ? NULL : hWnd, hMenu, mi->uItem, &r);
    if(!ret) return FALSE;

    memset(i, 0, sizeof(i));
    i[0].type = i[1].type = i[2].type = INPUT_MOUSE;
    i[0].u.mi.dx = i[1].u.mi.dx = i[2].u.mi.dx
            = ((r.left + 5) * 65535) / screen_w;
    i[0].u.mi.dy = i[1].u.mi.dy = i[2].u.mi.dy
            = ((r.top + 5) * 65535) / screen_h;
    i[0].u.mi.dwFlags = i[1].u.mi.dwFlags = i[2].u.mi.dwFlags
            = MOUSEEVENTF_ABSOLUTE;
    i[0].u.mi.dwFlags |= MOUSEEVENTF_MOVE;
    i[1].u.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;
    i[2].u.mi.dwFlags |= MOUSEEVENTF_LEFTUP;
    ret = pSendInput(3, (INPUT *) i, sizeof(INPUT));

    /* hack to prevent mouse message buildup in Wine */
    while (PeekMessageA( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    return ret;
}