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
struct sway_workspace {scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  gaps_inner; } ;
struct sway_view {int dummy; } ;
struct sway_seat {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct sway_container {scalar_t__ layout; scalar_t__ y; scalar_t__ x; TYPE_1__ current_gaps; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct sway_view* view; int /*<<< orphan*/  node; struct sway_container* parent; struct sway_workspace* workspace; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_4__ {scalar_t__ smart_gaps; } ;

/* Variables and functions */
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 TYPE_2__* config ; 
 int container_parent_layout (struct sway_container*) ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 struct sway_container* seat_get_focus_inactive_view (struct sway_seat*,int /*<<< orphan*/ *) ; 
 scalar_t__ view_is_only_visible (struct sway_view*) ; 

void container_add_gaps(struct sway_container *c) {
	if (c->current_gaps.top > 0 || c->current_gaps.right > 0 ||
			c->current_gaps.bottom > 0 || c->current_gaps.left > 0) {
		return;
	}
	// Fullscreen global scratchpad containers cannot have gaps
	struct sway_workspace *ws = c->workspace;
	if (!ws) {
		return;
	}
	// Linear containers don't have gaps because it'd create double gaps
	if (!c->view && c->layout != L_TABBED && c->layout != L_STACKED) {
		return;
	}
	// Descendants of tabbed/stacked containers re-use the gaps of the container
	struct sway_container *temp = c;
	while (temp) {
		enum sway_container_layout layout = container_parent_layout(temp);
		if (layout == L_TABBED || layout == L_STACKED) {
			return;
		}
		temp = temp->parent;
	}
	// If smart gaps is on, don't add gaps if there is only one view visible
	if (config->smart_gaps) {
		struct sway_view *view = c->view;
		if (!view) {
			struct sway_seat *seat =
				input_manager_get_default_seat();
			struct sway_container *focus =
				seat_get_focus_inactive_view(seat, &c->node);
			view = focus ? focus->view : NULL;
		}
		if (view && view_is_only_visible(view)) {
			return;
		}
	}

	c->current_gaps.top = c->y == ws->y ? ws->gaps_inner : 0;
	c->current_gaps.right = ws->gaps_inner;
	c->current_gaps.bottom = ws->gaps_inner;
	c->current_gaps.left = c->x == ws->x ? ws->gaps_inner : 0;

	c->x += c->current_gaps.left;
	c->y += c->current_gaps.top;
	c->width -= c->current_gaps.left + c->current_gaps.right;
	c->height -= c->current_gaps.top + c->current_gaps.bottom;
}