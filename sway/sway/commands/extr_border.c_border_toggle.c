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
struct sway_container {int border; TYPE_1__* view; } ;
struct TYPE_2__ {int /*<<< orphan*/  xdg_decoration; scalar_t__ using_csd; } ;

/* Variables and functions */
#define  B_CSD 131 
#define  B_NONE 130 
#define  B_NORMAL 129 
#define  B_PIXEL 128 
 int /*<<< orphan*/  set_border (struct sway_container*,int const) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

__attribute__((used)) static void border_toggle(struct sway_container *con) {
	if (con->view && con->view->using_csd) {
		set_border(con, B_NONE);
		return;
	}
	switch (con->border) {
	case B_NONE:
		set_border(con, B_PIXEL);
		break;
	case B_PIXEL:
		set_border(con, B_NORMAL);
		break;
	case B_NORMAL:
		if (con->view && con->view->xdg_decoration) {
			set_border(con, B_CSD);
		} else {
			set_border(con, B_NONE);
		}
		break;
	case B_CSD:
		// view->using_csd should be true so it would have returned above
		sway_assert(false, "Unreachable");
		break;
	}
}