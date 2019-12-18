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
struct input_config {int /*<<< orphan*/  identifier; } ;
struct TYPE_6__ {TYPE_1__* input_type_configs; TYPE_2__* input_configs; } ;
struct TYPE_5__ {int length; struct input_config** items; } ;
struct TYPE_4__ {int length; struct input_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  merge_input_config (struct input_config*,struct input_config*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge_wildcard_on_all(struct input_config *wildcard) {
	for (int i = 0; i < config->input_configs->length; i++) {
		struct input_config *ic = config->input_configs->items[i];
		if (strcmp(wildcard->identifier, ic->identifier) != 0) {
			sway_log(SWAY_DEBUG, "Merging input * config on %s", ic->identifier);
			merge_input_config(ic, wildcard);
		}
	}

	for (int i = 0; i < config->input_type_configs->length; i++) {
		struct input_config *ic = config->input_type_configs->items[i];
		sway_log(SWAY_DEBUG, "Merging input * config on %s", ic->identifier);
		merge_input_config(ic, wildcard);
	}
}