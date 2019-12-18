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
typedef  int uint32_t ;
struct bar_config {int modifier; int visible_by_modifier; int /*<<< orphan*/  hidden_state; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__* bars; } ;
struct TYPE_3__ {int length; struct bar_config** items; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int /*<<< orphan*/  ipc_event_bar_state_update (struct bar_config*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void determine_bar_visibility(uint32_t modifiers) {
	for (int i = 0; i < config->bars->length; ++i) {
		struct bar_config *bar = config->bars->items[i];
		if (bar->modifier == 0) {
			continue;
		}

		bool vis_by_mod = (~modifiers & bar->modifier) == 0;
		if (bar->visible_by_modifier != vis_by_mod) {
			// If visible by modifier is set, send that it is no longer visible
			// by modifier (regardless of bar mode and state). Otherwise, only
			// send the visible by modifier status if mode and state are hide
			if (bar->visible_by_modifier
					|| strcmp(bar->mode, bar->hidden_state) == 0) {
				bar->visible_by_modifier = vis_by_mod;
				ipc_event_bar_state_update(bar);
			}
		}
	}
}