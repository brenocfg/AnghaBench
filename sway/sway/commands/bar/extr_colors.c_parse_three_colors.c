#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmd_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* add_color (char*,char*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 char* malloc (int) ; 

__attribute__((used)) static struct cmd_results *parse_three_colors(char ***colors,
		const char *cmd_name, int argc, char **argv) {
	struct cmd_results *error = NULL;
	if (argc != 3) {
		return cmd_results_new(CMD_INVALID,
				"Command '%s' requires exactly three color values", cmd_name);
	}
	for (size_t i = 0; i < 3; i++) {
		if (!*colors[i] && !(*(colors[i]) = malloc(10))) {
			return NULL;
		}
		error = add_color(*(colors[i]), argv[i]);
		if (error) {
			return error;
		}
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}