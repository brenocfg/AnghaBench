#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_texture {int dummy; } ;
struct sway_view {int dummy; } ;
struct sway_output {int dummy; } ;
struct sway_container_state {int x; scalar_t__ focused; } ;
struct sway_container {struct sway_container_state current; struct sway_view* view; struct wlr_texture* marks_unfocused; struct wlr_texture* title_unfocused; struct wlr_texture* marks_focused_inactive; struct wlr_texture* title_focused_inactive; struct wlr_texture* marks_focused; struct wlr_texture* title_focused; struct wlr_texture* marks_urgent; struct wlr_texture* title_urgent; } ;
struct TYPE_7__ {int width; int /*<<< orphan*/  y; } ;
struct parent_data {scalar_t__ focused; TYPE_3__ box; TYPE_2__* children; struct sway_container* active_child; } ;
struct border_colors {int dummy; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_5__ {struct border_colors unfocused; struct border_colors focused_inactive; struct border_colors focused; struct border_colors urgent; } ;
struct TYPE_8__ {TYPE_1__ border_colors; } ;
struct TYPE_6__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 TYPE_4__* config ; 
 int container_has_urgent_child (struct sway_container*) ; 
 int /*<<< orphan*/  render_container (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,int) ; 
 int /*<<< orphan*/  render_titlebar (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,int,int /*<<< orphan*/ ,int,struct border_colors*,struct wlr_texture*,struct wlr_texture*) ; 
 int /*<<< orphan*/  render_view (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,struct border_colors*) ; 
 int view_is_urgent (struct sway_view*) ; 

__attribute__((used)) static void render_containers_tabbed(struct sway_output *output,
		pixman_region32_t *damage, struct parent_data *parent) {
	if (!parent->children->length) {
		return;
	}
	struct sway_container *current = parent->active_child;
	struct border_colors *current_colors = &config->border_colors.unfocused;
	int tab_width = parent->box.width / parent->children->length;

	// Render tabs
	for (int i = 0; i < parent->children->length; ++i) {
		struct sway_container *child = parent->children->items[i];
		struct sway_view *view = child->view;
		struct sway_container_state *cstate = &child->current;
		struct border_colors *colors;
		struct wlr_texture *title_texture;
		struct wlr_texture *marks_texture;
		bool urgent = view ?
			view_is_urgent(view) : container_has_urgent_child(child);

		if (urgent) {
			colors = &config->border_colors.urgent;
			title_texture = child->title_urgent;
			marks_texture = child->marks_urgent;
		} else if (cstate->focused || parent->focused) {
			colors = &config->border_colors.focused;
			title_texture = child->title_focused;
			marks_texture = child->marks_focused;
		} else if (child == parent->active_child) {
			colors = &config->border_colors.focused_inactive;
			title_texture = child->title_focused_inactive;
			marks_texture = child->marks_focused_inactive;
		} else {
			colors = &config->border_colors.unfocused;
			title_texture = child->title_unfocused;
			marks_texture = child->marks_unfocused;
		}

		int x = cstate->x + tab_width * i;

		// Make last tab use the remaining width of the parent
		if (i == parent->children->length - 1) {
			tab_width = parent->box.width - tab_width * i;
		}

		render_titlebar(output, damage, child, x, parent->box.y, tab_width,
				colors, title_texture, marks_texture);

		if (child == current) {
			current_colors = colors;
		}
	}

	// Render surface and left/right/bottom borders
	if (current->view) {
		render_view(output, damage, current, current_colors);
	} else {
		render_container(output, damage, current,
				parent->focused || current->current.focused);
	}
}