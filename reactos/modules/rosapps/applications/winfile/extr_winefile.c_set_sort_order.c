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
struct TYPE_4__ {scalar_t__ sortOrder; } ;
typedef  scalar_t__ SORT_ORDER ;
typedef  TYPE_1__ ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  refresh_child (TYPE_1__*) ; 

__attribute__((used)) static void set_sort_order(ChildWnd* child, SORT_ORDER sortOrder)
{
	if (child->sortOrder != sortOrder) {
		child->sortOrder = sortOrder;
		refresh_child(child);
	}
}