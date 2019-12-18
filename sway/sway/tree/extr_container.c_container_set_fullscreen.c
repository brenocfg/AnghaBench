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
struct sway_container {int fullscreen_mode; TYPE_1__* workspace; } ;
typedef  enum sway_fullscreen_mode { ____Placeholder_sway_fullscreen_mode } sway_fullscreen_mode ;
struct TYPE_4__ {struct sway_container* fullscreen_global; } ;
struct TYPE_3__ {struct sway_container* fullscreen; } ;

/* Variables and functions */
#define  FULLSCREEN_GLOBAL 130 
#define  FULLSCREEN_NONE 129 
#define  FULLSCREEN_WORKSPACE 128 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_global (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_workspace (struct sway_container*) ; 
 TYPE_2__* root ; 

void container_set_fullscreen(struct sway_container *con,
		enum sway_fullscreen_mode mode) {
	if (con->fullscreen_mode == mode) {
		return;
	}

	switch (mode) {
	case FULLSCREEN_NONE:
		container_fullscreen_disable(con);
		break;
	case FULLSCREEN_WORKSPACE:
		if (root->fullscreen_global) {
			container_fullscreen_disable(root->fullscreen_global);
		}
		if (con->workspace && con->workspace->fullscreen) {
			container_fullscreen_disable(con->workspace->fullscreen);
		}
		container_fullscreen_workspace(con);
		break;
	case FULLSCREEN_GLOBAL:
		if (root->fullscreen_global) {
			container_fullscreen_disable(root->fullscreen_global);
		}
		if (con->fullscreen_mode == FULLSCREEN_WORKSPACE) {
			container_fullscreen_disable(con);
		}
		container_fullscreen_global(con);
		break;
	}
}