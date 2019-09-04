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
struct TYPE_6__ {scalar_t__ show_marks; } ;
struct TYPE_5__ {TYPE_1__* outputs; } ;
struct TYPE_4__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  output_damage_whole (struct sway_output*) ; 
 scalar_t__ parse_boolean (char*,scalar_t__) ; 
 int /*<<< orphan*/  rebuild_marks_iterator ; 
 TYPE_2__* root ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct cmd_results *cmd_show_marks(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "show_marks", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	config->show_marks = parse_boolean(argv[0], config->show_marks);

	if (config->show_marks) {
		root_for_each_container(rebuild_marks_iterator, NULL);
	}

	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		output_damage_whole(output);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}