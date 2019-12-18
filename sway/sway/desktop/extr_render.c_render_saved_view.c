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
struct wlr_output {int /*<<< orphan*/  transform_matrix; int /*<<< orphan*/  scale; } ;
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct sway_view {TYPE_3__* saved_buffer; int /*<<< orphan*/  saved_buffer_height; int /*<<< orphan*/  saved_buffer_width; TYPE_2__ saved_geometry; TYPE_1__* container; } ;
struct sway_output {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ ly; scalar_t__ lx; struct wlr_output* wlr_output; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_6__ {int /*<<< orphan*/  texture; } ;
struct TYPE_4__ {scalar_t__ surface_y; scalar_t__ surface_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL_OUTPUT_TRANSFORM_NORMAL ; 
 int /*<<< orphan*/  render_texture (struct wlr_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wlr_box*,float*,float) ; 
 int /*<<< orphan*/  scale_box (struct wlr_box*,int /*<<< orphan*/ ) ; 
 int wlr_box_intersection (struct wlr_box*,struct wlr_box*,struct wlr_box*) ; 
 int /*<<< orphan*/  wlr_matrix_project_box (float*,struct wlr_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_saved_view(struct sway_view *view,
		struct sway_output *output, pixman_region32_t *damage, float alpha) {
	struct wlr_output *wlr_output = output->wlr_output;

	if (!view->saved_buffer || !view->saved_buffer->texture) {
		return;
	}
	struct wlr_box box = {
		.x = view->container->surface_x - output->lx -
			view->saved_geometry.x,
		.y = view->container->surface_y - output->ly -
			view->saved_geometry.y,
		.width = view->saved_buffer_width,
		.height = view->saved_buffer_height,
	};

	struct wlr_box output_box = {
		.width = output->width,
		.height = output->height,
	};

	struct wlr_box intersection;
	bool intersects = wlr_box_intersection(&intersection, &output_box, &box);
	if (!intersects) {
		return;
	}

	scale_box(&box, wlr_output->scale);

	float matrix[9];
	wlr_matrix_project_box(matrix, &box, WL_OUTPUT_TRANSFORM_NORMAL, 0,
		wlr_output->transform_matrix);

	render_texture(wlr_output, damage, view->saved_buffer->texture,
			&box, matrix, alpha);

	// FIXME: we should set the surface that this saved buffer originates from
	// as sampled here.
	// https://github.com/swaywm/sway/pull/4465#discussion_r321082059
}