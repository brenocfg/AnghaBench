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
struct cmd_results {int dummy; } ;
struct TYPE_6__ {int titlebar_border_thickness; int titlebar_v_padding; int titlebar_h_padding; } ;
struct TYPE_5__ {TYPE_1__* outputs; } ;
struct TYPE_4__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  arrange_workspace (int /*<<< orphan*/ ) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  output_damage_whole (struct sway_output*) ; 
 int /*<<< orphan*/  output_get_active_workspace (struct sway_output*) ; 
 TYPE_2__* root ; 
 int strtol (char*,char**,int) ; 

struct cmd_results *cmd_titlebar_padding(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "titlebar_padding", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	char *inv;
	int h_value = strtol(argv[0], &inv, 10);
	if (*inv != '\0' || h_value < 0 || h_value < config->titlebar_border_thickness) {
		return cmd_results_new(CMD_FAILURE, "Invalid size specified");
	}

	int v_value;
	if (argc == 1) {
		v_value = h_value;
	} else {
		v_value = strtol(argv[1], &inv, 10);
		if (*inv != '\0' || v_value < 0 || v_value < config->titlebar_border_thickness) {
			return cmd_results_new(CMD_FAILURE, "Invalid size specified");
		}
	}

	config->titlebar_v_padding = v_value;
	config->titlebar_h_padding = h_value;

	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		arrange_workspace(output_get_active_workspace(output));
		output_damage_whole(output);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}