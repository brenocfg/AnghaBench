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
struct winlink {int dummy; } ;
struct session {int dummy; } ;
struct options_entry {int dummy; } ;
struct options {int dummy; } ;
struct cmd_find_state {struct winlink* wl; struct session* s; } ;
struct cmdq_item {struct cmd_find_state target; } ;
struct cmd {int /*<<< orphan*/ * entry; struct args* args; } ;
struct client {int dummy; } ;
struct args {scalar_t__ argc; int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int OPTIONS_TABLE_NONE ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int cmd_show_options_all (struct cmd*,struct cmdq_item*,int,struct options*) ; 
 int /*<<< orphan*/  cmd_show_options_print (struct cmd*,struct cmdq_item*,struct options_entry*,int,int) ; 
 int /*<<< orphan*/  cmd_show_window_options_entry ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 char* format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,struct winlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct options_entry* options_get (struct options*,char*) ; 
 struct options_entry* options_get_only (struct options*,char*) ; 
 char* options_match (char*,int*,int*) ; 
 int options_scope_from_flags (struct args*,int,struct cmd_find_state*,struct options**,char**) ; 
 int options_scope_from_name (struct args*,int,char*,struct cmd_find_state*,struct options**,char**) ; 

__attribute__((used)) static enum cmd_retval
cmd_show_options_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	struct cmd_find_state		*fs = &item->target;
	struct client			*c = cmd_find_client(item, NULL, 1);
	struct session			*s = item->target.s;
	struct winlink			*wl = item->target.wl;
	struct options			*oo;
	char				*argument, *name = NULL, *cause;
	int				 window, idx, ambiguous, parent, scope;
	struct options_entry		*o;

	window = (self->entry == &cmd_show_window_options_entry);

	if (args->argc == 0) {
		scope = options_scope_from_flags(args, window, fs, &oo, &cause);
		if (scope == OPTIONS_TABLE_NONE) {
			if (args_has(args, 'q'))
				return (CMD_RETURN_NORMAL);
			cmdq_error(item, "%s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
		return (cmd_show_options_all(self, item, scope, oo));
	}
	argument = format_single(item, args->argv[0], c, s, wl, NULL);

	name = options_match(argument, &idx, &ambiguous);
	if (name == NULL) {
		if (args_has(args, 'q'))
			goto fail;
		if (ambiguous)
			cmdq_error(item, "ambiguous option: %s", argument);
		else
			cmdq_error(item, "invalid option: %s", argument);
		goto fail;
	}
	scope = options_scope_from_name(args, window, name, fs, &oo, &cause);
	if (scope == OPTIONS_TABLE_NONE) {
		if (args_has(args, 'q'))
			goto fail;
		cmdq_error(item, "%s", cause);
		free(cause);
		goto fail;
	}
	o = options_get_only(oo, name);
	if (args_has(args, 'A') && o == NULL) {
		o = options_get(oo, name);
		parent = 1;
	} else
		parent = 0;
	if (o != NULL)
		cmd_show_options_print(self, item, o, idx, parent);

	free(name);
	free(argument);
	return (CMD_RETURN_NORMAL);

fail:
	free(name);
	free(argument);
	return (CMD_RETURN_ERROR);
}