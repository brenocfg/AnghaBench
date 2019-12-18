#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct environ {int dummy; } ;
struct TYPE_4__ {TYPE_1__* s; } ;
struct cmdq_item {TYPE_2__ target; } ;
struct cmd {struct args* args; } ;
struct args {char** argv; int argc; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_3__ {struct environ* environ; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  environ_clear (struct environ*,char const*) ; 
 int /*<<< orphan*/  environ_set (struct environ*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  environ_unset (struct environ*,char const*) ; 
 struct environ* global_environ ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static enum cmd_retval
cmd_set_environment_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	struct environ	*env;
	const char	*name, *value, *target;

	name = args->argv[0];
	if (*name == '\0') {
		cmdq_error(item, "empty variable name");
		return (CMD_RETURN_ERROR);
	}
	if (strchr(name, '=') != NULL) {
		cmdq_error(item, "variable name contains =");
		return (CMD_RETURN_ERROR);
	}

	if (args->argc < 2)
		value = NULL;
	else
		value = args->argv[1];

	if (args_has(self->args, 'g'))
		env = global_environ;
	else {
		if (item->target.s == NULL) {
			target = args_get(args, 't');
			if (target != NULL)
				cmdq_error(item, "no such session: %s", target);
			else
				cmdq_error(item, "no current session");
			return (CMD_RETURN_ERROR);
		}
		env = item->target.s->environ;
	}

	if (args_has(self->args, 'u')) {
		if (value != NULL) {
			cmdq_error(item, "can't specify a value with -u");
			return (CMD_RETURN_ERROR);
		}
		environ_unset(env, name);
	} else if (args_has(self->args, 'r')) {
		if (value != NULL) {
			cmdq_error(item, "can't specify a value with -r");
			return (CMD_RETURN_ERROR);
		}
		environ_clear(env, name);
	} else {
		if (value == NULL) {
			cmdq_error(item, "no value specified");
			return (CMD_RETURN_ERROR);
		}
		environ_set(env, name, "%s", value);
	}

	return (CMD_RETURN_NORMAL);
}