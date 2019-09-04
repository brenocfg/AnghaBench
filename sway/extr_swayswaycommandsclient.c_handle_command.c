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
struct border_colors {int /*<<< orphan*/  child_border; int /*<<< orphan*/  indicator; int /*<<< orphan*/  text; int /*<<< orphan*/  background; int /*<<< orphan*/  border; } ;
struct TYPE_6__ {scalar_t__ active; } ;
struct TYPE_5__ {TYPE_1__* outputs; } ;
struct TYPE_4__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  output_damage_whole (struct sway_output*) ; 
 int /*<<< orphan*/  parse_color_float (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebuild_textures_iterator ; 
 TYPE_2__* root ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cmd_results *handle_command(int argc, char **argv,
		struct border_colors *class, char *cmd_name) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, cmd_name, EXPECTED_EQUAL_TO, 5))) {
		return error;
	}

	if (!parse_color_float(argv[0], class->border)) {
		return cmd_results_new(CMD_INVALID,
				"Unable to parse border color '%s'", argv[0]);
	}

	if (!parse_color_float(argv[1], class->background)) {
		return cmd_results_new(CMD_INVALID,
				"Unable to parse background color '%s'", argv[1]);
	}

	if (!parse_color_float(argv[2], class->text)) {
		return cmd_results_new(CMD_INVALID,
				"Unable to parse text color '%s'", argv[2]);
	}

	if (!parse_color_float(argv[3], class->indicator)) {
		return cmd_results_new(CMD_INVALID,
				"Unable to parse indicator color '%s'", argv[3]);
	}

	if (!parse_color_float(argv[4], class->child_border)) {
		return cmd_results_new(CMD_INVALID,
				"Unable to parse child border color '%s'", argv[4]);
	}

	if (config->active) {
		root_for_each_container(rebuild_textures_iterator, NULL);

		for (int i = 0; i < root->outputs->length; ++i) {
			struct sway_output *output = root->outputs->items[i];
			output_damage_whole(output);
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}