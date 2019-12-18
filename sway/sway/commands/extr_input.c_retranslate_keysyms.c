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
struct input_config {scalar_t__ identifier; scalar_t__ xkb_file; scalar_t__ xkb_layout; } ;
struct TYPE_4__ {TYPE_1__* input_configs; } ;
struct TYPE_3__ {int length; struct input_config** items; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int /*<<< orphan*/  translate_keysyms (struct input_config*) ; 

__attribute__((used)) static void retranslate_keysyms(struct input_config *input_config) {
	for (int i = 0; i < config->input_configs->length; ++i) {
		struct input_config *ic = config->input_configs->items[i];
		if (ic->xkb_layout || ic->xkb_file) {
			// this is the first config with xkb_layout or xkb_file
			if (ic->identifier == input_config->identifier) {
				translate_keysyms(ic);
			}

			return;
		}
	}
}