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
struct sway_container {int saved_border; int border; TYPE_1__* view; } ;
typedef  enum sway_container_border { ____Placeholder_sway_container_border } sway_container_border ;
struct TYPE_2__ {int using_csd; } ;

/* Variables and functions */
 int B_CSD ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  view_set_csd_from_server (TYPE_1__*,int) ; 

__attribute__((used)) static void set_border(struct sway_container *con,
		enum sway_container_border new_border) {
	if (con->view) {
		if (con->view->using_csd && new_border != B_CSD) {
			view_set_csd_from_server(con->view, false);
		} else if (!con->view->using_csd && new_border == B_CSD) {
			view_set_csd_from_server(con->view, true);
			con->saved_border = con->border;
		}
	}
	if (new_border != B_CSD || container_is_floating(con)) {
		con->border = new_border;
	}
	if (con->view) {
		con->view->using_csd = new_border == B_CSD;
	}
}