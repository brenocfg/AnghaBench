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
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

struct cmd_results *add_color(char *buffer, const char *color) {
	int len = strlen(color);
	if (len != 7 && len != 9) {
		return cmd_results_new(CMD_INVALID,
				"Invalid color definition %s", color);
	}
	if (color[0] != '#') {
		return cmd_results_new(CMD_INVALID,
				"Invalid color definition %s", color);
	}
	for (int i = 1; i < len; ++i) {
		if (!isxdigit(color[i])) {
			return cmd_results_new(CMD_INVALID,
					"Invalid color definition %s", color);
		}
	}
	strcpy(buffer, color);
	// add default alpha channel if color was defined without it
	if (len == 7) {
		buffer[7] = 'f';
		buffer[8] = 'f';
	}
	buffer[9] = '\0';
	return NULL;
}