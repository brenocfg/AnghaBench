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
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* add_color (char*,char*) ; 
 struct cmd_results* checkarg (int,char const*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 

__attribute__((used)) static struct cmd_results *parse_single_color(char **color,
		const char *cmd_name, int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, cmd_name, EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	if (!*color && !(*color = malloc(10))) {
		return NULL;
	}
	error = add_color(*color, argv[0]);
	if (error) {
		return error;
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}