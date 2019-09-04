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
struct sway_workspace {int dummy; } ;
struct sway_output {int dummy; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {int titlebar_v_padding; int titlebar_border_thickness; } ;
struct TYPE_5__ {TYPE_1__* outputs; } ;
struct TYPE_4__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  output_damage_whole (struct sway_output*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 TYPE_2__* root ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 

struct cmd_results *cmd_titlebar_border_thickness(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "titlebar_border_thickness", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	char *inv;
	int value = strtol(argv[0], &inv, 10);
	if (*inv != '\0' || value < 0 || value > config->titlebar_v_padding) {
		return cmd_results_new(CMD_FAILURE, "Invalid size specified");
	}

	config->titlebar_border_thickness = value;

	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		struct sway_workspace *ws = output_get_active_workspace(output);
		if (!sway_assert(ws, "Expected output to have a workspace")) {
			return cmd_results_new(CMD_FAILURE,
					"Expected output to have a workspace");
		}
		arrange_workspace(ws);
		output_damage_whole(output);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}