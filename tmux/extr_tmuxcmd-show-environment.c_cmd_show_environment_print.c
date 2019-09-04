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
struct environ_entry {int /*<<< orphan*/  name; int /*<<< orphan*/ * value; } ;
struct cmdq_item {int dummy; } ;
struct cmd {int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  args_has (int /*<<< orphan*/ ,char) ; 
 char* cmd_show_environment_escape (struct environ_entry*) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
cmd_show_environment_print(struct cmd *self, struct cmdq_item *item,
    struct environ_entry *envent)
{
	char	*escaped;

	if (!args_has(self->args, 's')) {
		if (envent->value != NULL)
			cmdq_print(item, "%s=%s", envent->name, envent->value);
		else
			cmdq_print(item, "-%s", envent->name);
		return;
	}

	if (envent->value != NULL) {
		escaped = cmd_show_environment_escape(envent);
		cmdq_print(item, "%s=\"%s\"; export %s;", envent->name, escaped,
		    envent->name);
		free(escaped);
	} else
		cmdq_print(item, "unset %s;", envent->name);
}