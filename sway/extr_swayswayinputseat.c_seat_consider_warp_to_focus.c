#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wlr_box {int dummy; } ;
struct sway_seat {TYPE_2__* cursor; } ;
struct sway_output {int dummy; } ;
struct sway_node {scalar_t__ type; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_container; } ;
struct TYPE_9__ {scalar_t__ mouse_warping; } ;
struct TYPE_8__ {int /*<<< orphan*/  hide_source; scalar_t__ hidden; TYPE_1__* cursor; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 scalar_t__ WARP_NO ; 
 scalar_t__ WARP_OUTPUT ; 
 TYPE_6__* config ; 
 int /*<<< orphan*/  cursor_get_timeout (TYPE_2__*) ; 
 int /*<<< orphan*/  cursor_unhide (TYPE_2__*) ; 
 int /*<<< orphan*/  cursor_warp_to_container (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_warp_to_workspace (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct sway_output* node_get_output (struct sway_node*) ; 
 int /*<<< orphan*/  output_get_box (struct sway_output*,struct wlr_box*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  wl_event_source_timer_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wlr_box_contains_point (struct wlr_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void seat_consider_warp_to_focus(struct sway_seat *seat) {
	struct sway_node *focus = seat_get_focus(seat);
	if (config->mouse_warping == WARP_NO || !focus) {
		return;
	}
	if (config->mouse_warping == WARP_OUTPUT) {
		struct sway_output *output = node_get_output(focus);
		if (output) {
			struct wlr_box box;
			output_get_box(output, &box);
			if (wlr_box_contains_point(&box,
						seat->cursor->cursor->x, seat->cursor->cursor->y)) {
				return;
			}
		}
	}

	if (focus->type == N_CONTAINER) {
		cursor_warp_to_container(seat->cursor, focus->sway_container);
	} else {
		cursor_warp_to_workspace(seat->cursor, focus->sway_workspace);
	}
	if (seat->cursor->hidden){
		cursor_unhide(seat->cursor);
		wl_event_source_timer_update(seat->cursor->hide_source, cursor_get_timeout(seat->cursor));
	}
}