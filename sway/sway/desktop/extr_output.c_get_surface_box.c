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
struct TYPE_2__ {int width; int height; } ;
struct wlr_surface {int sx; int sy; TYPE_1__ current; } ;
struct wlr_box {int width; int height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_output {int width; int height; } ;
struct surface_iterator_data {int /*<<< orphan*/  rotation; int /*<<< orphan*/  oy; int /*<<< orphan*/  ox; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct sway_output* output; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct wlr_box*,struct wlr_box*,int) ; 
 int /*<<< orphan*/  rotate_child_position (double*,double*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wlr_box_intersection (struct wlr_box*,struct wlr_box*,struct wlr_box*) ; 
 int /*<<< orphan*/  wlr_box_rotated_bounds (struct wlr_box*,struct wlr_box*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_surface_has_buffer (struct wlr_surface*) ; 

__attribute__((used)) static bool get_surface_box(struct surface_iterator_data *data,
		struct wlr_surface *surface, int sx, int sy,
		struct wlr_box *surface_box) {
	struct sway_output *output = data->output;

	if (!wlr_surface_has_buffer(surface)) {
		return false;
	}

	int sw = surface->current.width;
	int sh = surface->current.height;

	double _sx = sx + surface->sx;
	double _sy = sy + surface->sy;
	rotate_child_position(&_sx, &_sy, sw, sh, data->width, data->height,
		data->rotation);

	struct wlr_box box = {
		.x = data->ox + _sx,
		.y = data->oy + _sy,
		.width = sw,
		.height = sh,
	};
	if (surface_box != NULL) {
		memcpy(surface_box, &box, sizeof(struct wlr_box));
	}

	struct wlr_box rotated_box;
	wlr_box_rotated_bounds(&rotated_box, &box, data->rotation);

	struct wlr_box output_box = {
		.width = output->width,
		.height = output->height,
	};

	struct wlr_box intersection;
	return wlr_box_intersection(&intersection, &output_box, &rotated_box);
}