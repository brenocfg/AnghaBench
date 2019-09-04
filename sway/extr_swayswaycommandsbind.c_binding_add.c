#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_binding {char const* input; char const* command; } ;
struct cmd_results {int dummy; } ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 struct sway_binding* binding_upsert (struct sway_binding*,int /*<<< orphan*/ *) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_add_swaynag_warning (char*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free_sway_binding (struct sway_binding*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static struct cmd_results *binding_add(struct sway_binding *binding,
		list_t *mode_bindings, const char *bindtype,
		const char *keycombo, bool warn) {
	struct sway_binding *config_binding = binding_upsert(binding, mode_bindings);

	if (config_binding) {
		sway_log(SWAY_INFO, "Overwriting binding '%s' for device '%s' "
				"to `%s` from `%s`", keycombo, binding->input,
				binding->command, config_binding->command);
		if (warn) {
			config_add_swaynag_warning("Overwriting binding"
					"'%s' for device '%s' to `%s` from `%s`",
					keycombo, binding->input, binding->command,
					config_binding->command);
		}
		free_sway_binding(config_binding);
	} else {
		sway_log(SWAY_DEBUG, "%s - Bound %s to command `%s` for device '%s'",
				bindtype, keycombo, binding->command, binding->input);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}