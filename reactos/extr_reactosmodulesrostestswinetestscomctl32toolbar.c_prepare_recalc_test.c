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
 int GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TBSTYLE_FLAT ; 
 int /*<<< orphan*/  TB_GETITEMRECT ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  rebuild_toolbar_with_buttons (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_recalc_test(HWND *phToolbar)
{
    RECT rect;
    rebuild_toolbar_with_buttons(phToolbar);
    SetWindowLongA(*phToolbar, GWL_STYLE,
        GetWindowLongA(*phToolbar, GWL_STYLE) | TBSTYLE_FLAT);
    SendMessageA(*phToolbar, TB_GETITEMRECT, 1, (LPARAM)&rect);
    ok(rect.top == 2, "Test will make no sense because initial top is %d instead of 2\n",
        rect.top);
}