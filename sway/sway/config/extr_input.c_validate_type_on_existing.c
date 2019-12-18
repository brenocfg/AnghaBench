#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_config {scalar_t__ identifier; int /*<<< orphan*/ * input_type; } ;
struct TYPE_4__ {TYPE_1__* input_configs; } ;
struct TYPE_3__ {int length; struct input_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_2__* config ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_xkb_merge (struct input_config*,struct input_config*,char**) ; 

__attribute__((used)) static bool validate_type_on_existing(struct input_config *type_wildcard,
		char **error) {
	for (int i = 0; i < config->input_configs->length; i++) {
		struct input_config *ic = config->input_configs->items[i];
		if (ic->input_type == NULL) {
			continue;
		}

		if (strcmp(ic->input_type, type_wildcard->identifier + 5) == 0) {
			sway_log(SWAY_DEBUG, "Validating merge of %s on %s",
				type_wildcard->identifier, ic->identifier);
			if (!validate_xkb_merge(ic, type_wildcard, error)) {
				return false;
			}
		}
	}
	return true;
}