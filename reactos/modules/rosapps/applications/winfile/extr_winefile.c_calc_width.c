#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hDC; } ;
struct TYPE_8__ {scalar_t__* widths; } ;
struct TYPE_7__ {scalar_t__ right; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ Pane ;
typedef  TYPE_3__* LPDRAWITEMSTRUCT ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int DT_CALCRECT ; 
 int DT_NOPREFIX ; 
 int DT_SINGLELINE ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int) ; 

__attribute__((used)) static void calc_width(Pane* pane, LPDRAWITEMSTRUCT dis, int col, LPCWSTR str)
{
	RECT rt = {0, 0, 0, 0};

	DrawTextW(dis->hDC, str, -1, &rt, DT_CALCRECT|DT_SINGLELINE|DT_NOPREFIX);

	if (rt.right > pane->widths[col])
		pane->widths[col] = rt.right;
}