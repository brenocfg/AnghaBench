#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_binding {int /*<<< orphan*/  input; } ;
struct cmd_results {int dummy; } ;
struct TYPE_4__ {int length; struct sway_binding** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 scalar_t__ binding_key_compare (struct sway_binding*,struct sway_binding*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_sway_binding (struct sway_binding*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmd_results *binding_remove(struct sway_binding *binding,
		list_t *mode_bindings, const char *bindtype,
		const char *keycombo) {
	for (int i = 0; i < mode_bindings->length; ++i) {
		struct sway_binding *config_binding = mode_bindings->items[i];
		if (binding_key_compare(binding, config_binding)) {
			sway_log(SWAY_DEBUG, "%s - Unbound `%s` from device '%s'",
					bindtype, keycombo, binding->input);
			free_sway_binding(config_binding);
			free_sway_binding(binding);
			list_del(mode_bindings, i);
			return cmd_results_new(CMD_SUCCESS, NULL);
		}
	}
	free_sway_binding(binding);
	return cmd_results_new(CMD_FAILURE, "Could not find binding `%s` "
			"for the given flags", keycombo);
}