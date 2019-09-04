#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_texture {int dummy; } ;
struct sway_view {int dummy; } ;
struct sway_output {int dummy; } ;
struct sway_container_state {scalar_t__ border; scalar_t__ focused; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_container {struct sway_container_state current; struct wlr_texture* marks_unfocused; struct wlr_texture* title_unfocused; struct wlr_texture* marks_focused_inactive; struct wlr_texture* title_focused_inactive; struct wlr_texture* marks_focused; struct wlr_texture* title_focused; struct wlr_texture* marks_urgent; struct wlr_texture* title_urgent; struct sway_view* view; } ;
struct parent_data {scalar_t__ focused; struct sway_container* active_child; TYPE_1__* children; } ;
struct border_colors {int dummy; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_5__ {struct border_colors unfocused; struct border_colors focused_inactive; struct border_colors focused; struct border_colors urgent; } ;
struct TYPE_6__ {TYPE_2__ border_colors; } ;
struct TYPE_4__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 scalar_t__ B_NORMAL ; 
 scalar_t__ B_PIXEL ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  render_container (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,int) ; 
 int /*<<< orphan*/  render_titlebar (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct border_colors*,struct wlr_texture*,struct wlr_texture*) ; 
 int /*<<< orphan*/  render_top_border (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,struct border_colors*) ; 
 int /*<<< orphan*/  render_view (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,struct border_colors*) ; 
 scalar_t__ view_is_urgent (struct sway_view*) ; 

__attribute__((used)) static void render_containers_linear(struct sway_output *output,
		pixman_region32_t *damage, struct parent_data *parent) {
	for (int i = 0; i < parent->children->length; ++i) {
		struct sway_container *child = parent->children->items[i];

		if (child->view) {
			struct sway_view *view = child->view;
			struct border_colors *colors;
			struct wlr_texture *title_texture;
			struct wlr_texture *marks_texture;
			struct sway_container_state *state = &child->current;

			if (view_is_urgent(view)) {
				colors = &config->border_colors.urgent;
				title_texture = child->title_urgent;
				marks_texture = child->marks_urgent;
			} else if (state->focused || parent->focused) {
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

			if (state->border == B_NORMAL) {
				render_titlebar(output, damage, child, state->x,
						state->y, state->width, colors,
						title_texture, marks_texture);
			} else if (state->border == B_PIXEL) {
				render_top_border(output, damage, child, colors);
			}
			render_view(output, damage, child, colors);
		} else {
			render_container(output, damage, child,
					parent->focused || child->current.focused);
		}
	}
}