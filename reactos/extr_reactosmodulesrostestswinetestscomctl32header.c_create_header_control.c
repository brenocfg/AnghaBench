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
struct TYPE_3__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  hwndInsertAfter; } ;
typedef  TYPE_1__ WINDOWPOS ;
struct TYPE_4__ {TYPE_1__* pwpos; int /*<<< orphan*/ * prc; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  TYPE_2__ HDLAYOUT ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HDM_LAYOUT ; 
 int HDS_BUTTONS ; 
 int HDS_HORZ ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_HEADERA ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  hHeaderParentWnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HWND create_header_control (void)
{
    HWND handle;
    HDLAYOUT hlayout;
    RECT rectwin;
    WINDOWPOS winpos;

    handle = CreateWindowExA(0, WC_HEADERA, NULL,
			     WS_CHILD|WS_BORDER|WS_VISIBLE|HDS_BUTTONS|HDS_HORZ,
			     0, 0, 0, 0,
			     hHeaderParentWnd, NULL, NULL, NULL);
    ok(handle != NULL, "failed to create header window\n");

    if (winetest_interactive)
	ShowWindow (hHeaderParentWnd, SW_SHOW);

    GetClientRect(hHeaderParentWnd,&rectwin);
    hlayout.prc = &rectwin;
    hlayout.pwpos = &winpos;
    SendMessageA(handle, HDM_LAYOUT, 0, (LPARAM)&hlayout);
    SetWindowPos(handle, winpos.hwndInsertAfter, winpos.x, winpos.y, 
                 winpos.cx, winpos.cy, 0);

    return handle;
}