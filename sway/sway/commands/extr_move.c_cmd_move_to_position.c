#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int x; int width; int y; int height; } ;
struct sway_seat {TYPE_2__* cursor; } ;
struct sway_container {int width; int height; struct sway_workspace* workspace; } ;
struct cmd_results {int dummy; } ;
struct TYPE_8__ {struct sway_seat* seat; struct sway_container* container; } ;
struct TYPE_10__ {TYPE_3__ handler_context; } ;
struct TYPE_9__ {int x; int width; int y; int height; } ;
struct TYPE_7__ {TYPE_1__* cursor; } ;
struct TYPE_6__ {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* config ; 
 int /*<<< orphan*/  container_floating_move_to (struct sway_container*,double,double) ; 
 int /*<<< orphan*/  container_is_floating (struct sway_container*) ; 
 char* expected_position_syntax ; 
 TYPE_4__* root ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static struct cmd_results *cmd_move_to_position(int argc, char **argv) {
	struct sway_container *container = config->handler_context.container;
	if (!container || !container_is_floating(container)) {
		return cmd_results_new(CMD_FAILURE, "Only floating containers "
				"can be moved to an absolute position");
	}

	if (!argc) {
		return cmd_results_new(CMD_INVALID, expected_position_syntax);
	}

	bool absolute = false;
	if (strcmp(argv[0], "absolute") == 0) {
		absolute = true;
		--argc;
		++argv;
	}
	if (!argc) {
		return cmd_results_new(CMD_INVALID, expected_position_syntax);
	}
	if (strcmp(argv[0], "position") == 0) {
		--argc;
		++argv;
	}
	if (!argc) {
		return cmd_results_new(CMD_INVALID, expected_position_syntax);
	}
	if (strcmp(argv[0], "cursor") == 0 || strcmp(argv[0], "mouse") == 0 ||
			strcmp(argv[0], "pointer") == 0) {
		if (absolute) {
			return cmd_results_new(CMD_INVALID, expected_position_syntax);
		}
		struct sway_seat *seat = config->handler_context.seat;
		if (!seat->cursor) {
			return cmd_results_new(CMD_FAILURE, "No cursor device");
		}
		double lx = seat->cursor->cursor->x - container->width / 2;
		double ly = seat->cursor->cursor->y - container->height / 2;
		container_floating_move_to(container, lx, ly);
		return cmd_results_new(CMD_SUCCESS, NULL);
	} else if (strcmp(argv[0], "center") == 0) {
		double lx, ly;
		if (absolute) {
			lx = root->x + (root->width - container->width) / 2;
			ly = root->y + (root->height - container->height) / 2;
		} else {
			struct sway_workspace *ws = container->workspace;
			if (!ws) {
				struct sway_seat *seat = config->handler_context.seat;
				ws = seat_get_focused_workspace(seat);
			}
			lx = ws->x + (ws->width - container->width) / 2;
			ly = ws->y + (ws->height - container->height) / 2;
		}
		container_floating_move_to(container, lx, ly);
		return cmd_results_new(CMD_SUCCESS, NULL);
	}

	if (argc < 2) {
		return cmd_results_new(CMD_FAILURE, expected_position_syntax);
	}

	double lx, ly;
	char *inv;
	lx = (double)strtol(argv[0], &inv, 10);
	if (*inv != '\0' && strcasecmp(inv, "px") != 0) {
		return cmd_results_new(CMD_FAILURE, "Invalid position specified");
	}
	if (strcmp(argv[1], "px") == 0) {
		--argc;
		++argv;
	}

	if (argc > 3) {
		return cmd_results_new(CMD_FAILURE, expected_position_syntax);
	}

	ly = (double)strtol(argv[1], &inv, 10);
	if ((*inv != '\0' && strcasecmp(inv, "px") != 0) ||
			(argc == 3 && strcmp(argv[2], "px") != 0)) {
		return cmd_results_new(CMD_FAILURE, "Invalid position specified");
	}

	if (!absolute) {
		struct sway_workspace *ws = container->workspace;
		if (!ws) {
			struct sway_seat *seat = config->handler_context.seat;
			ws = seat_get_focused_workspace(seat);
		}
		lx += ws->x;
		ly += ws->y;
	}
	container_floating_move_to(container, lx, ly);
	return cmd_results_new(CMD_SUCCESS, NULL);
}