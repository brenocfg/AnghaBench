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
struct cmd_handler {struct cmd_results* (* handle ) (int,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,char*) ; 
 struct cmd_handler* find_handler (char*,struct cmd_handler*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 struct cmd_results* stub1 (int,char**) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

struct cmd_results *config_subcommand(char **argv, int argc,
		struct cmd_handler *handlers, size_t handlers_size) {
	char *command = join_args(argv, argc);
	sway_log(SWAY_DEBUG, "Subcommand: %s", command);
	free(command);

	struct cmd_handler *handler = find_handler(argv[0], handlers,
			handlers_size);
	if (!handler) {
		return cmd_results_new(CMD_INVALID,
				"Unknown/invalid command '%s'", argv[0]);
	}
	if (handler->handle) {
		return handler->handle(argc - 1, argv + 1);
	}
	return cmd_results_new(CMD_INVALID,
			"The command '%s' is shimmed, but unimplemented", argv[0]);
}