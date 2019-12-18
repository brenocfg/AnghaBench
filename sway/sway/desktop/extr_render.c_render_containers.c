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
struct sway_output {int dummy; } ;
struct sway_container {scalar_t__ view; } ;
struct parent_data {int layout; TYPE_1__* children; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_4__ {scalar_t__ hide_lone_tab; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;

/* Variables and functions */
#define  L_HORIZ 132 
#define  L_NONE 131 
#define  L_STACKED 130 
#define  L_TABBED 129 
#define  L_VERT 128 
 TYPE_2__* config ; 
 int /*<<< orphan*/  render_containers_linear (struct sway_output*,int /*<<< orphan*/ *,struct parent_data*) ; 
 int /*<<< orphan*/  render_containers_stacked (struct sway_output*,int /*<<< orphan*/ *,struct parent_data*) ; 
 int /*<<< orphan*/  render_containers_tabbed (struct sway_output*,int /*<<< orphan*/ *,struct parent_data*) ; 

__attribute__((used)) static void render_containers(struct sway_output *output,
		pixman_region32_t *damage, struct parent_data *parent) {
	if (config->hide_lone_tab && parent->children->length == 1) {
		struct sway_container *child = parent->children->items[0];
		if (child->view) {
			render_containers_linear(output,damage, parent);
			return;
		}
	}

	switch (parent->layout) {
	case L_NONE:
	case L_HORIZ:
	case L_VERT:
		render_containers_linear(output, damage, parent);
		break;
	case L_STACKED:
		render_containers_stacked(output, damage, parent);
		break;
	case L_TABBED:
		render_containers_tabbed(output, damage, parent);
		break;
	}
}