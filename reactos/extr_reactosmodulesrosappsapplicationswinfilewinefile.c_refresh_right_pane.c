#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  root; int /*<<< orphan*/  hwnd; } ;
struct TYPE_6__ {TYPE_2__ right; int /*<<< orphan*/  filter_flags; int /*<<< orphan*/  filter_pattern; } ;
typedef  TYPE_1__ ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_widths (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_entries (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_header (TYPE_2__*) ; 

__attribute__((used)) static void refresh_right_pane(ChildWnd* child)
{
	SendMessageW(child->right.hwnd, LB_RESETCONTENT, 0, 0);
	insert_entries(&child->right, child->right.root, child->filter_pattern, child->filter_flags, -1);
	calc_widths(&child->right, FALSE);

	set_header(&child->right);
}