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
struct sway_container {int scratchpad; } ;
struct TYPE_2__ {int /*<<< orphan*/  scratchpad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ,int) ; 
 int list_find (int /*<<< orphan*/ ,struct sway_container*) ; 
 TYPE_1__* root ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

void root_scratchpad_remove_container(struct sway_container *con) {
	if (!sway_assert(con->scratchpad, "Container is not in scratchpad")) {
		return;
	}
	con->scratchpad = false;
	int index = list_find(root->scratchpad, con);
	if (index != -1) {
		list_del(root->scratchpad, index);
		ipc_event_window(con, "move");
	}
}