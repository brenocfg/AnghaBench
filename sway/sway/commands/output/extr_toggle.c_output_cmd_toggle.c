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
struct sway_output {int dummy; } ;
struct output_config {scalar_t__ enabled; int /*<<< orphan*/  name; } ;
struct cmd_results {int dummy; } ;
struct TYPE_4__ {int argc; char** argv; } ;
struct TYPE_5__ {TYPE_1__ leftovers; struct output_config* output_config; } ;
struct TYPE_6__ {TYPE_2__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 struct sway_output* all_output_by_name_or_id (int /*<<< orphan*/ ) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* config ; 
 struct output_config* find_output_config (struct sway_output*) ; 
 int /*<<< orphan*/  free (struct output_config*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

struct cmd_results *output_cmd_toggle(int argc, char **argv) {
	if (!config->handler_context.output_config) {
		return cmd_results_new(CMD_FAILURE, "Missing output config");
	}

	struct output_config *oc = config->handler_context.output_config;

	if (strcmp(oc->name, "*") == 0) {
		return cmd_results_new(CMD_INVALID,
				"Cannot apply toggle to all outputs.");
	}

	struct sway_output *sway_output = all_output_by_name_or_id(oc->name);

	if (sway_output == NULL) {
		return cmd_results_new(CMD_FAILURE,
				"Cannot apply toggle to unknown output %s", oc->name);
	}

	oc = find_output_config(sway_output);

	if (!oc || oc->enabled != 0) {
		config->handler_context.output_config->enabled = 0;
	} else {
		config->handler_context.output_config->enabled = 1;
	}

	free(oc);
	config->handler_context.leftovers.argc = argc;
	config->handler_context.leftovers.argv = argv;
	return NULL;
}