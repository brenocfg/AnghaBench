#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_container {TYPE_2__* view; } ;
struct TYPE_4__ {TYPE_1__* impl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_fullscreen ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void set_fullscreen_iterator(struct sway_container *con, void *data) {
	if (!con->view) {
		return;
	}
	if (con->view->impl->set_fullscreen) {
		bool *enable = data;
		con->view->impl->set_fullscreen(con->view, *enable);
	}
}