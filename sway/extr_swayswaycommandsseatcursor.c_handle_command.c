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
struct sway_cursor {int /*<<< orphan*/  cursor; } ;
struct cmd_results {int dummy; } ;
struct TYPE_2__ {float width; float height; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cursor_rebase (struct sway_cursor*) ; 
 int /*<<< orphan*/ * expected_syntax ; 
 struct cmd_results* press_or_release (struct sway_cursor*,char*,char*) ; 
 TYPE_1__* root ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 float strtof (char*,int /*<<< orphan*/ *) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wlr_cursor_move (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wlr_cursor_warp_absolute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float,float) ; 

__attribute__((used)) static struct cmd_results *handle_command(struct sway_cursor *cursor,
		int argc, char **argv) {
	if (strcasecmp(argv[0], "move") == 0) {
		if (argc < 3) {
			return cmd_results_new(CMD_INVALID, expected_syntax);
		}
		int delta_x = strtol(argv[1], NULL, 10);
		int delta_y = strtol(argv[2], NULL, 10);
		wlr_cursor_move(cursor->cursor, NULL, delta_x, delta_y);
		cursor_rebase(cursor);
	} else if (strcasecmp(argv[0], "set") == 0) {
		if (argc < 3) {
			return cmd_results_new(CMD_INVALID, expected_syntax);
		}
		// map absolute coords (0..1,0..1) to root container coords
		float x = strtof(argv[1], NULL) / root->width;
		float y = strtof(argv[2], NULL) / root->height;
		wlr_cursor_warp_absolute(cursor->cursor, NULL, x, y);
		cursor_rebase(cursor);
	} else {
		if (argc < 2) {
			return cmd_results_new(CMD_INVALID, expected_syntax);
		}
		struct cmd_results *error = NULL;
		if ((error = press_or_release(cursor, argv[0], argv[1]))) {
			return error;
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}