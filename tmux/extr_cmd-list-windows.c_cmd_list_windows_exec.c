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
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct cmdq_item {TYPE_1__ target; } ;
struct cmd {struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  cmd_list_windows_server (struct cmd*,struct cmdq_item*) ; 
 int /*<<< orphan*/  cmd_list_windows_session (struct cmd*,int /*<<< orphan*/ ,struct cmdq_item*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmd_list_windows_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;

	if (args_has(args, 'a'))
		cmd_list_windows_server(self, item);
	else
		cmd_list_windows_session(self, item->target.s, item, 0);

	return (CMD_RETURN_NORMAL);
}