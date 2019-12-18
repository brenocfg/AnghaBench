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
struct sway_view {int /*<<< orphan*/  xdg_decoration; } ;
struct sway_container {int /*<<< orphan*/  border_thickness; struct sway_view* view; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_CSD ; 
 int /*<<< orphan*/  B_NONE ; 
 int /*<<< orphan*/  B_NORMAL ; 
 int /*<<< orphan*/  B_PIXEL ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  arrange_container (struct sway_container*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  border_toggle (struct sway_container*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_set_geometry_from_content (struct sway_container*) ; 
 int /*<<< orphan*/  set_border (struct sway_container*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_border(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "border", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	struct sway_container *container = config->handler_context.container;
	if (!container || !container->view) {
		return cmd_results_new(CMD_INVALID, "Only views can have borders");
	}
	struct sway_view *view = container->view;

	if (strcmp(argv[0], "none") == 0) {
		set_border(container, B_NONE);
	} else if (strcmp(argv[0], "normal") == 0) {
		set_border(container, B_NORMAL);
	} else if (strcmp(argv[0], "pixel") == 0) {
		set_border(container, B_PIXEL);
	} else if (strcmp(argv[0], "csd") == 0) {
		if (!view->xdg_decoration) {
			return cmd_results_new(CMD_INVALID,
					"This window doesn't support client side decorations");
		}
		set_border(container, B_CSD);
	} else if (strcmp(argv[0], "toggle") == 0) {
		border_toggle(container);
	} else {
		return cmd_results_new(CMD_INVALID,
				"Expected 'border <none|normal|pixel|csd|toggle>' "
				"or 'border pixel <px>'");
	}
	if (argc == 2) {
		container->border_thickness = atoi(argv[1]);
	}

	if (container_is_floating(container)) {
		container_set_geometry_from_content(container);
	}

	arrange_container(container);

	return cmd_results_new(CMD_SUCCESS, NULL);
}