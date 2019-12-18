#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_7__ {TYPE_2__* seat_config; } ;
struct TYPE_8__ {TYPE_3__ handler_context; } ;
struct TYPE_5__ {unsigned int size; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ xcursor_theme; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  EXPECTED_AT_MOST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 unsigned int strtoul (char*,char**,int) ; 

struct cmd_results *seat_cmd_xcursor_theme(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "xcursor_theme", EXPECTED_AT_LEAST, 1)) ||
		(error = checkarg(argc, "xcursor_theme", EXPECTED_AT_MOST, 2))) {
		return error;
	}
	if (!config->handler_context.seat_config) {
		return cmd_results_new(CMD_FAILURE, "No seat defined");
	}

	const char *theme_name = argv[0];
	unsigned size = 24;

	if (argc == 2) {
		char *end;
		size = strtoul(argv[1], &end, 10);
		if (*end) {
			return cmd_results_new(
				CMD_INVALID, "Expected a positive integer size");
		}
	}

	free(config->handler_context.seat_config->xcursor_theme.name);
	config->handler_context.seat_config->xcursor_theme.name = strdup(theme_name);
	config->handler_context.seat_config->xcursor_theme.size = size;

	return cmd_results_new(CMD_SUCCESS, NULL);
}