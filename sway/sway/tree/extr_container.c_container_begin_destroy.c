#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  destroy; } ;
struct TYPE_7__ {int destroying; TYPE_1__ events; } ;
struct sway_container {scalar_t__ fullscreen_mode; TYPE_2__* workspace; scalar_t__ parent; scalar_t__ scratchpad; TYPE_3__ node; scalar_t__ view; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fullscreen; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_GLOBAL ; 
 scalar_t__ FULLSCREEN_WORKSPACE ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_end_mouse_operation (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  node_set_dirty (TYPE_3__*) ; 
 int /*<<< orphan*/  root_scratchpad_remove_container (struct sway_container*) ; 
 int /*<<< orphan*/  wl_signal_emit (int /*<<< orphan*/ *,TYPE_3__*) ; 

void container_begin_destroy(struct sway_container *con) {
	if (con->view) {
		ipc_event_window(con, "close");
	}
	// The workspace must have the fullscreen pointer cleared so that the
	// seat code can find an appropriate new focus.
	if (con->fullscreen_mode == FULLSCREEN_WORKSPACE && con->workspace) {
		con->workspace->fullscreen = NULL;
	}
	if (con->scratchpad && con->fullscreen_mode == FULLSCREEN_GLOBAL) {
		container_fullscreen_disable(con);
	}

	wl_signal_emit(&con->node.events.destroy, &con->node);

	container_end_mouse_operation(con);

	con->node.destroying = true;
	node_set_dirty(&con->node);

	if (con->scratchpad) {
		root_scratchpad_remove_container(con);
	}

	if (con->fullscreen_mode == FULLSCREEN_GLOBAL) {
		container_fullscreen_disable(con);
	}

	if (con->parent || con->workspace) {
		container_detach(con);
	}
}