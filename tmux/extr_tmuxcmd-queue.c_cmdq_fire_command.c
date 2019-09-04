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
struct cmd_find_state {int /*<<< orphan*/  s; } ;
struct cmdq_item {struct client* client; TYPE_1__* shared; struct cmd_find_state target; struct cmd_find_state source; struct cmd* cmd; } ;
struct cmd_entry {int (* exec ) (struct cmd*,struct cmdq_item*) ;int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  target; int /*<<< orphan*/  source; } ;
struct cmd {int flags; struct cmd_entry* entry; } ;
struct client {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_2__ {struct cmd_find_state current; } ;

/* Variables and functions */
 int CMD_AFTERHOOK ; 
 int CMD_CONTROL ; 
 int CMD_RETURN_ERROR ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cmd_find_from_client (struct cmd_find_state*,struct client*,int /*<<< orphan*/ ) ; 
 scalar_t__ cmd_find_valid_state (struct cmd_find_state*) ; 
 int cmdq_find_flag (struct cmdq_item*,struct cmd_find_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_guard (struct cmdq_item*,char*,int) ; 
 int /*<<< orphan*/  cmdq_insert_hook (int /*<<< orphan*/ ,struct cmdq_item*,struct cmd_find_state*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct cmd*,struct cmdq_item*) ; 

__attribute__((used)) static enum cmd_retval
cmdq_fire_command(struct cmdq_item *item)
{
	struct client		*c = item->client;
	struct cmd		*cmd = item->cmd;
	const struct cmd_entry	*entry = cmd->entry;
	enum cmd_retval		 retval;
	struct cmd_find_state	*fsp, fs;
	int			 flags;

	flags = !!(cmd->flags & CMD_CONTROL);
	cmdq_guard(item, "begin", flags);

	if (item->client == NULL)
		item->client = cmd_find_client(item, NULL, 1);
	retval = cmdq_find_flag(item, &item->source, &entry->source);
	if (retval == CMD_RETURN_ERROR)
		goto out;
	retval = cmdq_find_flag(item, &item->target, &entry->target);
	if (retval == CMD_RETURN_ERROR)
		goto out;

	retval = entry->exec(cmd, item);
	if (retval == CMD_RETURN_ERROR)
		goto out;

	if (entry->flags & CMD_AFTERHOOK) {
		if (cmd_find_valid_state(&item->target))
			fsp = &item->target;
		else if (cmd_find_valid_state(&item->shared->current))
			fsp = &item->shared->current;
		else if (cmd_find_from_client(&fs, item->client, 0) == 0)
			fsp = &fs;
		else
			goto out;
		cmdq_insert_hook(fsp->s, item, fsp, "after-%s", entry->name);
	}

out:
	item->client = c;
	if (retval == CMD_RETURN_ERROR)
		cmdq_guard(item, "error", flags);
	else
		cmdq_guard(item, "end", flags);
	return (retval);
}