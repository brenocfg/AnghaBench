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
struct sway_workspace {int prev_split_layout; int layout; TYPE_1__* tiling; } ;
struct sway_container {int layout; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 struct sway_container* workspace_wrap_children (struct sway_workspace*) ; 

struct sway_container *workspace_split(struct sway_workspace *workspace,
		enum sway_container_layout layout) {
	if (workspace->tiling->length == 0) {
		workspace->prev_split_layout = workspace->layout;
		workspace->layout = layout;
		return NULL;
	}

	enum sway_container_layout old_layout = workspace->layout;
	struct sway_container *middle = workspace_wrap_children(workspace);
	workspace->layout = layout;
	middle->layout = old_layout;

	return middle;
}