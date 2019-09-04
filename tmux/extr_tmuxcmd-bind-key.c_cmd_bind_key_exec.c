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
struct cmd_list {int dummy; } ;
struct cmd {struct args* args; } ;
struct args {char** argv; scalar_t__ argc; } ;
typedef  scalar_t__ key_code ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 scalar_t__ KEYC_NONE ; 
 scalar_t__ KEYC_UNKNOWN ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct cmd_list* cmd_list_parse (scalar_t__,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  key_bindings_add (char const*,scalar_t__,scalar_t__,struct cmd_list*) ; 
 scalar_t__ key_string_lookup_string (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_bind_key_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	char		*cause;
	struct cmd_list	*cmdlist;
	key_code	 key;
	const char	*tablename;

	key = key_string_lookup_string(args->argv[0]);
	if (key == KEYC_NONE || key == KEYC_UNKNOWN) {
		cmdq_error(item, "unknown key: %s", args->argv[0]);
		return (CMD_RETURN_ERROR);
	}

	if (args_has(args, 'T'))
		tablename = args_get(args, 'T');
	else if (args_has(args, 'n'))
		tablename = "root";
	else
		tablename = "prefix";

	cmdlist = cmd_list_parse(args->argc - 1, args->argv + 1, NULL, 0,
	    &cause);
	if (cmdlist == NULL) {
		cmdq_error(item, "%s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}

	key_bindings_add(tablename, key, args_has(args, 'r'), cmdlist);
	return (CMD_RETURN_NORMAL);
}