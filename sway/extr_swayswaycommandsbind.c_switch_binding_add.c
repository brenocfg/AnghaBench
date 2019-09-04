#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_switch_binding {char const* command; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {int length; struct sway_switch_binding** items; } ;
typedef  TYPE_2__ list_t ;
struct TYPE_7__ {TYPE_1__* current_mode; } ;
struct TYPE_5__ {TYPE_2__* switch_bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 scalar_t__ binding_switch_compare (struct sway_switch_binding*,struct sway_switch_binding*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  config_add_swaynag_warning (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free_switch_binding (struct sway_switch_binding*) ; 
 int /*<<< orphan*/  list_add (TYPE_2__*,struct sway_switch_binding*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 

__attribute__((used)) static struct cmd_results *switch_binding_add(
		struct sway_switch_binding *binding, const char *bindtype,
		const char *switchcombo, bool warn) {
	list_t *mode_bindings = config->current_mode->switch_bindings;
	// overwrite the binding if it already exists
	bool overwritten = false;
	for (int i = 0; i < mode_bindings->length; ++i) {
		struct sway_switch_binding *config_binding = mode_bindings->items[i];
		if (binding_switch_compare(binding, config_binding)) {
			sway_log(SWAY_INFO, "Overwriting binding '%s' to `%s` from `%s`",
					switchcombo, binding->command, config_binding->command);
			if (warn) {
				config_add_swaynag_warning("Overwriting binding"
						"'%s' to `%s` from `%s`",
						switchcombo, binding->command,
						config_binding->command);
			}
			free_switch_binding(config_binding);
			mode_bindings->items[i] = binding;
			overwritten = true;
		}
	}

	if (!overwritten) {
		list_add(mode_bindings, binding);
		sway_log(SWAY_DEBUG, "%s - Bound %s to command `%s`",
				bindtype, switchcombo, binding->command);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}