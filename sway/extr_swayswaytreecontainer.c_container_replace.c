#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_container {int fullscreen_mode; int scratchpad; scalar_t__ workspace; scalar_t__ parent; } ;
typedef  enum sway_fullscreen_mode { ____Placeholder_sway_fullscreen_mode } sway_fullscreen_mode ;

/* Variables and functions */
#define  FULLSCREEN_GLOBAL 130 
#define  FULLSCREEN_NONE 129 
#define  FULLSCREEN_WORKSPACE 128 
 int /*<<< orphan*/  container_add_sibling (struct sway_container*,struct sway_container*,int) ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_global (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_workspace (struct sway_container*) ; 
 int /*<<< orphan*/  root_scratchpad_add_container (struct sway_container*) ; 
 int /*<<< orphan*/  root_scratchpad_remove_container (struct sway_container*) ; 
 int /*<<< orphan*/  root_scratchpad_show (struct sway_container*) ; 

void container_replace(struct sway_container *container,
		struct sway_container *replacement) {
	enum sway_fullscreen_mode fullscreen = container->fullscreen_mode;
	bool scratchpad = container->scratchpad;
	if (fullscreen != FULLSCREEN_NONE) {
		container_fullscreen_disable(container);
	}
	if (scratchpad) {
		root_scratchpad_show(container);
		root_scratchpad_remove_container(container);
	}
	if (container->parent || container->workspace) {
		container_add_sibling(container, replacement, 1);
		container_detach(container);
	}
	if (scratchpad) {
		root_scratchpad_add_container(replacement);
	}
	switch (fullscreen) {
	case FULLSCREEN_WORKSPACE:
		container_fullscreen_workspace(replacement);
		break;
	case FULLSCREEN_GLOBAL:
		container_fullscreen_global(replacement);
		break;
	case FULLSCREEN_NONE:
		// noop
		break;
	}
}