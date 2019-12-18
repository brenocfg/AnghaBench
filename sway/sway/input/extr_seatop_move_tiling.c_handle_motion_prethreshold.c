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
struct wlr_output {int scale; } ;
struct sway_seat {TYPE_3__* cursor; struct seatop_move_tiling_event* seatop_data; } ;
struct seatop_move_tiling_event {double ref_lx; double ref_ly; int threshold_reached; } ;
struct TYPE_8__ {double tiling_drag_threshold; } ;
struct TYPE_7__ {TYPE_1__* cursor; } ;
struct TYPE_6__ {int /*<<< orphan*/  output_layout; } ;
struct TYPE_5__ {double x; double y; } ;

/* Variables and functions */
 TYPE_4__* config ; 
 int /*<<< orphan*/  cursor_set_image (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* root ; 
 struct wlr_output* wlr_output_layout_output_at (int /*<<< orphan*/ ,double,double) ; 

__attribute__((used)) static void handle_motion_prethreshold(struct sway_seat *seat) {
	struct seatop_move_tiling_event *e = seat->seatop_data;
	double cx = seat->cursor->cursor->x;
	double cy = seat->cursor->cursor->y;
	double sx = e->ref_lx;
	double sy = e->ref_ly;

	// Get the scaled threshold for the output. Even if the operation goes
	// across multiple outputs of varying scales, just use the scale for the
	// output that the cursor is currently on for simplicity.
	struct wlr_output *wlr_output = wlr_output_layout_output_at(
			root->output_layout, cx, cy);
	double output_scale = wlr_output ? wlr_output->scale : 1;
	double threshold = config->tiling_drag_threshold * output_scale;
	threshold *= threshold;

	// If the threshold has been exceeded, start the actual drag
	if ((cx - sx) * (cx - sx) + (cy - sy) * (cy - sy) > threshold) {
		e->threshold_reached = true;
		cursor_set_image(seat->cursor, "grab", NULL);
	}
}