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
struct TYPE_4__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRectEx (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 int /*<<< orphan*/  SM_CYHSCROLL ; 
 int WS_EX_LEFTSCROLLBAR ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 

__attribute__((used)) static void FixedAdjustWindowRectEx(RECT* rc, LONG style, BOOL menu, LONG exstyle)
{
    AdjustWindowRectEx(rc, style, menu, exstyle);
    /* AdjustWindowRectEx does not include scroll bars */
    if (style & WS_VSCROLL)
    {
        if(exstyle & WS_EX_LEFTSCROLLBAR)
            rc->left  -= GetSystemMetrics(SM_CXVSCROLL);
        else
            rc->right += GetSystemMetrics(SM_CXVSCROLL);
    }
    if (style & WS_HSCROLL)
	rc->bottom += GetSystemMetrics(SM_CYHSCROLL);
}