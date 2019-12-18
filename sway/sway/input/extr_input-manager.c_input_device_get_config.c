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
struct input_config {scalar_t__ identifier; } ;
struct TYPE_6__ {TYPE_2__* input_type_configs; TYPE_1__* input_configs; } ;
struct TYPE_5__ {int length; struct input_config** items; } ;
struct TYPE_4__ {int length; struct input_config** items; } ;

/* Variables and functions */
 TYPE_3__* config ; 
 char* input_device_get_type (struct sway_input_device*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

struct input_config *input_device_get_config(struct sway_input_device *device) {
	struct input_config *wildcard_config = NULL;
	struct input_config *input_config = NULL;
	for (int i = 0; i < config->input_configs->length; ++i) {
		input_config = config->input_configs->items[i];
		if (strcmp(input_config->identifier, device->identifier) == 0) {
			return input_config;
		} else if (strcmp(input_config->identifier, "*") == 0) {
			wildcard_config = input_config;
		}
	}

	const char *device_type = input_device_get_type(device);
	for (int i = 0; i < config->input_type_configs->length; ++i) {
		input_config = config->input_type_configs->items[i];
		if (strcmp(input_config->identifier + 5, device_type) == 0) {
			return input_config;
		}
	}

	return wildcard_config;
}