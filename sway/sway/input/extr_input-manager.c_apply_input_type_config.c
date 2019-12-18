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
struct sway_input_device {char const* identifier; } ;
struct input_config {char const* identifier; char const* input_type; } ;
struct TYPE_6__ {TYPE_2__* input_configs; TYPE_1__* input_type_configs; } ;
struct TYPE_5__ {int length; struct input_config** items; } ;
struct TYPE_4__ {int length; struct input_config** items; } ;

/* Variables and functions */
 TYPE_3__* config ; 
 int /*<<< orphan*/  free_input_config (struct input_config*) ; 
 char* input_device_get_type (struct sway_input_device*) ; 
 int /*<<< orphan*/  merge_input_config (struct input_config*,struct input_config*) ; 
 struct input_config* new_input_config (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void apply_input_type_config(struct sway_input_device *input_device) {
	const char *device_type = input_device_get_type(input_device);
	struct input_config *type_config = NULL;
	for (int i = 0; i < config->input_type_configs->length; i++) {
		struct input_config *ic = config->input_type_configs->items[i];
		if (strcmp(ic->identifier + 5, device_type) == 0) {
			type_config = ic;
			break;
		}
	}
	if (type_config == NULL) {
		return;
	}

	for (int i = 0; i < config->input_configs->length; i++) {
		struct input_config *ic = config->input_configs->items[i];
		if (strcmp(input_device->identifier, ic->identifier) == 0) {
			struct input_config *current = new_input_config(ic->identifier);
			merge_input_config(current, type_config);
			merge_input_config(current, ic);

			current->input_type = device_type;
			config->input_configs->items[i] = current;
			free_input_config(ic);
			ic = NULL;

			break;
		}
	}
}