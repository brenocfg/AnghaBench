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
struct cmd {int /*<<< orphan*/ * entry; struct args* args; } ;
struct client {int dummy; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  args_get (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_lock_server_entry ; 
 int /*<<< orphan*/  cmd_lock_session_entry ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_lock () ; 
 int /*<<< orphan*/  server_lock_client (struct client*) ; 
 int /*<<< orphan*/  server_lock_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmd_lock_server_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	struct client	*c;

	if (self->entry == &cmd_lock_server_entry)
		server_lock();
	else if (self->entry == &cmd_lock_session_entry)
		server_lock_session(item->target.s);
	else {
		if ((c = cmd_find_client(item, args_get(args, 't'), 0)) == NULL)
			return (CMD_RETURN_ERROR);
		server_lock_client(c);
	}
	recalculate_sizes();

	return (CMD_RETURN_NORMAL);
}