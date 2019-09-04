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
struct sway_seat_device {TYPE_4__* input_device; } ;
struct sway_seat {TYPE_1__* cursor; } ;
struct sway_output {TYPE_3__* wlr_output; } ;
struct input_config {char* mapped_to_output; } ;
struct TYPE_8__ {TYPE_2__* wlr_device; int /*<<< orphan*/  identifier; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {char* output_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct input_config* input_device_get_config (TYPE_4__*) ; 
 struct sway_output* output_by_name_or_id (char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wlr_cursor_map_input_to_output (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void seat_apply_input_config(struct sway_seat *seat,
		struct sway_seat_device *sway_device) {
	const char *mapped_to_output = NULL;

	struct input_config *ic = input_device_get_config(
			sway_device->input_device);
	if (ic != NULL) {
		sway_log(SWAY_DEBUG, "Applying input config to %s",
			sway_device->input_device->identifier);

		mapped_to_output = ic->mapped_to_output;
	}

	if (mapped_to_output == NULL) {
		mapped_to_output = sway_device->input_device->wlr_device->output_name;
	}
	if (mapped_to_output != NULL) {
		sway_log(SWAY_DEBUG, "Mapping input device %s to output %s",
			sway_device->input_device->identifier, mapped_to_output);
		if (strcmp("*", mapped_to_output) == 0) {
			wlr_cursor_map_input_to_output(seat->cursor->cursor,
				sway_device->input_device->wlr_device, NULL);
			sway_log(SWAY_DEBUG, "Reset output mapping");
			return;
		}
		struct sway_output *output = output_by_name_or_id(mapped_to_output);
		if (output) {
			wlr_cursor_map_input_to_output(seat->cursor->cursor,
				sway_device->input_device->wlr_device, output->wlr_output);
			sway_log(SWAY_DEBUG, "Mapped to output %s", output->wlr_output->name);
		}
	}
}