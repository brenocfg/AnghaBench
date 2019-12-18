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
struct wlr_output {struct sway_output* data; } ;
struct sway_workspace {struct sway_output* output; } ;
struct sway_output {int /*<<< orphan*/  wlr_output; } ;
typedef  int /*<<< orphan*/  names ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
struct TYPE_4__ {int /*<<< orphan*/  seat; } ;
struct TYPE_6__ {TYPE_1__ handler_context; } ;
struct TYPE_5__ {int /*<<< orphan*/  output_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLR_DIRECTION_DOWN ; 
 int /*<<< orphan*/  WLR_DIRECTION_LEFT ; 
 int /*<<< orphan*/  WLR_DIRECTION_RIGHT ; 
 int /*<<< orphan*/  WLR_DIRECTION_UP ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  opposite_direction (int) ; 
 struct sway_output* output_by_name_or_id (char const*) ; 
 TYPE_2__* root ; 
 struct sway_workspace* seat_get_focused_workspace (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 struct wlr_output* wlr_output_layout_adjacent_output (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 struct wlr_output* wlr_output_layout_farthest_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct sway_output *output_in_direction(const char *direction_string,
		struct sway_output *reference, int ref_lx, int ref_ly) {
	if (strcasecmp(direction_string, "current") == 0) {
		struct sway_workspace *active_ws =
			seat_get_focused_workspace(config->handler_context.seat);
		if (!active_ws) {
			return NULL;
		}
		return active_ws->output;
	}

	struct {
		char *name;
		enum wlr_direction direction;
	} names[] = {
		{ "up", WLR_DIRECTION_UP },
		{ "down", WLR_DIRECTION_DOWN },
		{ "left", WLR_DIRECTION_LEFT },
		{ "right", WLR_DIRECTION_RIGHT },
	};

	enum wlr_direction direction = 0;

	for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
		if (strcasecmp(names[i].name, direction_string) == 0) {
			direction = names[i].direction;
			break;
		}
	}

	if (reference && direction) {
		struct wlr_output *target = wlr_output_layout_adjacent_output(
				root->output_layout, direction, reference->wlr_output,
				ref_lx, ref_ly);

		if (!target) {
			target = wlr_output_layout_farthest_output(
					root->output_layout, opposite_direction(direction),
					reference->wlr_output, ref_lx, ref_ly);
		}

		if (target) {
			return target->data;
		}
	}

	return output_by_name_or_id(direction_string);
}