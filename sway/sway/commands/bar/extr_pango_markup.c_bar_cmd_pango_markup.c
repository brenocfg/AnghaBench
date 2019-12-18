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
struct cmd_results {int dummy; } ;
struct TYPE_4__ {TYPE_1__* current_bar; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; scalar_t__ pango_markup; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* config ; 
 scalar_t__ parse_boolean (char*,scalar_t__) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct cmd_results *bar_cmd_pango_markup(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "pango_markup", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	config->current_bar->pango_markup =
		parse_boolean(argv[0], config->current_bar->pango_markup);
	if (config->current_bar->pango_markup) {
		sway_log(SWAY_DEBUG, "Enabling pango markup for bar: %s",
				config->current_bar->id);
	} else {
		sway_log(SWAY_DEBUG, "Disabling pango markup for bar: %s",
				config->current_bar->id);
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}