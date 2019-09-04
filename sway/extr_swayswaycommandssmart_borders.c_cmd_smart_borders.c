#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
typedef  enum edge_border_types { ____Placeholder_edge_border_types } edge_border_types ;
struct TYPE_2__ {int hide_edge_borders; int saved_edge_borders; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int E_SMART ; 
 int E_SMART_NO_GAPS ; 
 int /*<<< orphan*/  arrange_root () ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 scalar_t__ parse_boolean (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_smart_borders(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "smart_borders", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	enum edge_border_types saved = config->hide_edge_borders;
	if (strcmp(argv[0], "no_gaps") == 0) {
		config->hide_edge_borders = E_SMART_NO_GAPS;
	} else {
		config->hide_edge_borders = parse_boolean(argv[0], true) ?
			E_SMART : config->saved_edge_borders;
	}
	config->saved_edge_borders = saved;

	arrange_root();

	return cmd_results_new(CMD_SUCCESS, NULL);
}