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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_GETITEMRECT ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static BOOL did_recalc(HWND hToolbar)
{
    RECT rect;
    SendMessageA(hToolbar, TB_GETITEMRECT, 1, (LPARAM)&rect);
    ok(rect.top == 2 || rect.top == 0, "Unexpected top margin %d in recalc test\n",
        rect.top);
    return (rect.top == 0);
}