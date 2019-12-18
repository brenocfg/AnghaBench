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
struct cmdq_item {int dummy; } ;
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;
struct cmd {struct args* args; } ;
struct args {char** argv; int argc; } ;
typedef  scalar_t__ key_code ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 scalar_t__ KEYC_NONE ; 
 scalar_t__ KEYC_UNKNOWN ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct cmd_parse_result* cmd_parse_from_arguments (int,char**,int /*<<< orphan*/ *) ; 
 struct cmd_parse_result* cmd_parse_from_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  key_bindings_add (char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ key_string_lookup_string (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_bind_key_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		 *args = self->args;
	key_code		  key;
	const char		 *tablename;
	struct cmd_parse_result	 *pr;
	char			**argv = args->argv;
	int			  argc = args->argc;

	key = key_string_lookup_string(argv[0]);
	if (key == KEYC_NONE || key == KEYC_UNKNOWN) {
		cmdq_error(item, "unknown key: %s", argv[0]);
		return (CMD_RETURN_ERROR);
	}

	if (args_has(args, 'T'))
		tablename = args_get(args, 'T');
	else if (args_has(args, 'n'))
		tablename = "root";
	else
		tablename = "prefix";

	if (argc == 2)
		pr = cmd_parse_from_string(argv[1], NULL);
	else
		pr = cmd_parse_from_arguments(argc - 1, argv + 1, NULL);
	switch (pr->status) {
	case CMD_PARSE_EMPTY:
		cmdq_error(item, "empty command");
		return (CMD_RETURN_ERROR);
	case CMD_PARSE_ERROR:
		cmdq_error(item, "%s", pr->error);
		free(pr->error);
		return (CMD_RETURN_ERROR);
	case CMD_PARSE_SUCCESS:
		break;
	}
	key_bindings_add(tablename, key, args_has(args, 'r'), pr->cmdlist);
	return (CMD_RETURN_NORMAL);
}