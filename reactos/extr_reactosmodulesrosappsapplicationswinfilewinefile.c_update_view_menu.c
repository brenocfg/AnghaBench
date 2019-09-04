#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hMenuView; } ;
struct TYPE_4__ {scalar_t__ sortOrder; } ;
typedef  TYPE_1__ ChildWnd ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ Globals ; 
 int /*<<< orphan*/  ID_VIEW_SORT_DATE ; 
 int /*<<< orphan*/  ID_VIEW_SORT_NAME ; 
 int /*<<< orphan*/  ID_VIEW_SORT_SIZE ; 
 int /*<<< orphan*/  ID_VIEW_SORT_TYPE ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 int /*<<< orphan*/  MF_UNCHECKED ; 
 scalar_t__ SORT_DATE ; 
 scalar_t__ SORT_EXT ; 
 scalar_t__ SORT_NAME ; 
 scalar_t__ SORT_SIZE ; 

__attribute__((used)) static void update_view_menu(ChildWnd* child)
{
	CheckMenuItem(Globals.hMenuView, ID_VIEW_SORT_NAME, child->sortOrder==SORT_NAME? MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(Globals.hMenuView, ID_VIEW_SORT_TYPE, child->sortOrder==SORT_EXT? MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(Globals.hMenuView, ID_VIEW_SORT_SIZE, child->sortOrder==SORT_SIZE? MF_CHECKED: MF_UNCHECKED);
	CheckMenuItem(Globals.hMenuView, ID_VIEW_SORT_DATE, child->sortOrder==SORT_DATE? MF_CHECKED: MF_UNCHECKED);
}