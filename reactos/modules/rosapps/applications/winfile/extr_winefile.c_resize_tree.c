#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x; int flags; int cx; scalar_t__ cy; scalar_t__ y; int /*<<< orphan*/  hwndInsertAfter; } ;
typedef  TYPE_3__ WINDOWPOS ;
struct TYPE_9__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hwndHeader; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hwndHeader; } ;
struct TYPE_13__ {int split_pos; TYPE_2__ right; TYPE_1__ left; } ;
struct TYPE_12__ {TYPE_3__* pwpos; TYPE_4__* prc; } ;
struct TYPE_11__ {int left; int right; int bottom; scalar_t__ top; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_5__ HD_LAYOUT ;
typedef  int /*<<< orphan*/  HDWP ;
typedef  TYPE_6__ ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  BeginDeferWindowPos (int) ; 
 int /*<<< orphan*/  DeferWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  EndDeferWindowPos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDM_LAYOUT ; 
 int SPLIT_WIDTH ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resize_tree(ChildWnd* child, int cx, int cy)
{
	HDWP hdwp = BeginDeferWindowPos(4);
	RECT rt;
        WINDOWPOS wp;
        HD_LAYOUT hdl;

	rt.left   = 0;
	rt.top    = 0;
	rt.right  = cx;
	rt.bottom = cy;

	cx = child->split_pos + SPLIT_WIDTH/2;
        hdl.prc   = &rt;
        hdl.pwpos = &wp;

        SendMessageW(child->left.hwndHeader, HDM_LAYOUT, 0, (LPARAM)&hdl);

        DeferWindowPos(hdwp, child->left.hwndHeader, wp.hwndInsertAfter,
                       wp.x-1, wp.y, child->split_pos-SPLIT_WIDTH/2+1, wp.cy, wp.flags);
        DeferWindowPos(hdwp, child->right.hwndHeader, wp.hwndInsertAfter,
                       rt.left+cx+1, wp.y, wp.cx-cx+2, wp.cy, wp.flags);
	DeferWindowPos(hdwp, child->left.hwnd, 0, rt.left, rt.top, child->split_pos-SPLIT_WIDTH/2-rt.left, rt.bottom-rt.top, SWP_NOZORDER|SWP_NOACTIVATE);
	DeferWindowPos(hdwp, child->right.hwnd, 0, rt.left+cx+1, rt.top, rt.right-cx, rt.bottom-rt.top, SWP_NOZORDER|SWP_NOACTIVATE);

	EndDeferWindowPos(hdwp);
}