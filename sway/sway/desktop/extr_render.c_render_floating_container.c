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
struct TYPE_5__ {scalar_t__ border; scalar_t__ focused; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_container {TYPE_2__ current; struct wlr_texture* marks_unfocused; struct wlr_texture* title_unfocused; struct wlr_texture* marks_focused; struct wlr_texture* title_focused; struct wlr_texture* marks_urgent; struct wlr_texture* title_urgent; struct sway_view* view; } ;
struct border_colors {int dummy; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_4__ {struct border_colors unfocused; struct border_colors focused; struct border_colors urgent; } ;
struct TYPE_6__ {TYPE_1__ border_colors; } ;

/* Variables and functions */
 scalar_t__ B_NORMAL ; 
 scalar_t__ B_PIXEL ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  render_container (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,scalar_t__) ; 
 int /*<<< orphan*/  render_titlebar (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct border_colors*,struct wlr_texture*,struct wlr_texture*) ; 
 int /*<<< orphan*/  render_top_border (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,struct border_colors*) ; 
 int /*<<< orphan*/  render_view (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*,struct border_colors*) ; 
 scalar_t__ view_is_urgent (struct sway_view*) ; 

__attribute__((used)) static void render_floating_container(struct sway_output *soutput,
		pixman_region32_t *damage, struct sway_container *con) {
	if (con->view) {
		struct sway_view *view = con->view;
		struct border_colors *colors;
		struct wlr_texture *title_texture;
		struct wlr_texture *marks_texture;

		if (view_is_urgent(view)) {
			colors = &config->border_colors.urgent;
			title_texture = con->title_urgent;
			marks_texture = con->marks_urgent;
		} else if (con->current.focused) {
			colors = &config->border_colors.focused;
			title_texture = con->title_focused;
			marks_texture = con->marks_focused;
		} else {
			colors = &config->border_colors.unfocused;
			title_texture = con->title_unfocused;
			marks_texture = con->marks_unfocused;
		}

		if (con->current.border == B_NORMAL) {
			render_titlebar(soutput, damage, con, con->current.x,
					con->current.y, con->current.width, colors,
					title_texture, marks_texture);
		} else if (con->current.border == B_PIXEL) {
			render_top_border(soutput, damage, con, colors);
		}
		render_view(soutput, damage, con, colors);
	} else {
		render_container(soutput, damage, con, con->current.focused);
	}
}