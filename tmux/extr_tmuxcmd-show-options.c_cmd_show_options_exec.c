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
struct winlink {TYPE_1__* window; } ;
struct session {struct options* options; } ;
struct options_entry {int dummy; } ;
struct options {int dummy; } ;
struct cmd_find_state {struct winlink* wl; struct session* s; } ;
struct cmdq_item {struct cmd_find_state target; } ;
struct cmd {struct args* args; int /*<<< orphan*/ * entry; } ;
struct client {int dummy; } ;
struct args {scalar_t__ argc; int /*<<< orphan*/ * argv; } ;
typedef  enum options_table_scope { ____Placeholder_options_table_scope } options_table_scope ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_2__ {struct options* options; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int OPTIONS_TABLE_NONE ; 
 int OPTIONS_TABLE_SERVER ; 
 int OPTIONS_TABLE_SESSION ; 
 int OPTIONS_TABLE_WINDOW ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int cmd_show_options_all (struct cmd*,struct cmdq_item*,struct options*) ; 
 int /*<<< orphan*/  cmd_show_options_print (struct cmd*,struct cmdq_item*,struct options_entry*,int) ; 
 int /*<<< orphan*/  cmd_show_window_options_entry ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 char* format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,struct winlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct options* global_options ; 
 struct options* global_s_options ; 
 struct options* global_w_options ; 
 struct options_entry* options_get_only (struct options*,char*) ; 
 char* options_match (char*,int*,int*) ; 
 int options_scope_from_flags (struct args*,int,struct cmd_find_state*,struct options**,char**) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_show_options_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	struct cmd_find_state		*fs = &item->target;
	struct client			*c = cmd_find_client(item, NULL, 1);
	struct session			*s = item->target.s;
	struct winlink			*wl = item->target.wl;
	struct options			*oo;
	enum options_table_scope	 scope;
	char				*argument, *name = NULL, *cause;
	const char			*target;
	int				 window, idx, ambiguous;
	struct options_entry		*o;

	window = (self->entry == &cmd_show_window_options_entry);
	if (args->argc == 0) {
		scope = options_scope_from_flags(args, window, fs, &oo, &cause);
		return (cmd_show_options_all(self, item, oo));
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
	if (*name == '@')
		scope = options_scope_from_flags(args, window, fs, &oo, &cause);
	else {
		if (options_get_only(global_options, name) != NULL)
			scope = OPTIONS_TABLE_SERVER;
		else if (options_get_only(global_s_options, name) != NULL)
			scope = OPTIONS_TABLE_SESSION;
		else if (options_get_only(global_w_options, name) != NULL)
			scope = OPTIONS_TABLE_WINDOW;
		else {
			scope = OPTIONS_TABLE_NONE;
			xasprintf(&cause, "unknown option: %s", argument);
		}
		if (scope == OPTIONS_TABLE_SERVER)
			oo = global_options;
		else if (scope == OPTIONS_TABLE_SESSION) {
			if (args_has(self->args, 'g'))
				oo = global_s_options;
			else if (s == NULL) {
				target = args_get(args, 't');
				if (target != NULL) {
					cmdq_error(item, "no such session: %s",
					    target);
				} else
					cmdq_error(item, "no current session");
				goto fail;
			} else
				oo = s->options;
		} else if (scope == OPTIONS_TABLE_WINDOW) {
			if (args_has(self->args, 'g'))
				oo = global_w_options;
			else if (wl == NULL) {
				target = args_get(args, 't');
				if (target != NULL) {
					cmdq_error(item, "no such window: %s",
					    target);
				} else
					cmdq_error(item, "no current window");
				goto fail;
			} else
				oo = wl->window->options;
		}
	}
	if (scope == OPTIONS_TABLE_NONE) {
		if (args_has(args, 'q'))
			goto fail;
		cmdq_error(item, "%s", cause);
		free(cause);
		goto fail;
	}
	o = options_get_only(oo, name);
	if (o != NULL)
		cmd_show_options_print(self, item, o, idx);

	free(name);
	free(argument);
	return (CMD_RETURN_NORMAL);

fail:
	free(name);
	free(argument);
	return (CMD_RETURN_ERROR);
}