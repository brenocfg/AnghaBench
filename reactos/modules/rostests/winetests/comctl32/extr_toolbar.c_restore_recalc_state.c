#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TBSTYLE_FLAT ; 
 int /*<<< orphan*/  TB_ADDBUTTONSA ; 
 int /*<<< orphan*/  TB_GETITEMRECT ; 
 int /*<<< orphan*/  TB_GETSTYLE ; 
 int /*<<< orphan*/ * buttons3 ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void restore_recalc_state(HWND hToolbar)
{
    RECT rect;
    /* return to style with a 2px top margin */
    SetWindowLongA(hToolbar, GWL_STYLE,
                   SendMessageA(hToolbar, TB_GETSTYLE, 0, 0) & ~TBSTYLE_FLAT);
    /* recalc */
    SendMessageA(hToolbar, TB_ADDBUTTONSA, 1, (LPARAM)&buttons3[3]);
    /* top margin will be 0px if a recalc occurs */
    SetWindowLongA(hToolbar, GWL_STYLE,
                   SendMessageA(hToolbar, TB_GETSTYLE, 0, 0) | TBSTYLE_FLAT);
    /* safety check */
    SendMessageA(hToolbar, TB_GETITEMRECT, 1, (LPARAM)&rect);
    ok(rect.top == 2, "Test will make no sense because initial top is %d instead of 2\n",
        rect.top);
}