#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct job {int dummy; } ;
struct cmdq_item {int dummy; } ;
struct cmd_list {int dummy; } ;
struct cmd_if_shell_data {char* file; char* cmd_else; char* cmd_if; TYPE_1__* item; int /*<<< orphan*/  mouse; int /*<<< orphan*/  line; struct client* client; } ;
struct client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_WAITING ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd_list* cmd_string_parse (char*,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 int /*<<< orphan*/  cmdq_error (TYPE_1__*,char*,char*) ; 
 struct cmdq_item* cmdq_get_command (struct cmd_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_insert_after (TYPE_1__*,struct cmdq_item*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct cmd_if_shell_data* job_get_data (struct job*) ; 
 int job_get_status (struct job*) ; 

__attribute__((used)) static void
cmd_if_shell_callback(struct job *job)
{
	struct cmd_if_shell_data	*cdata = job_get_data(job);
	struct client			*c = cdata->client;
	struct cmd_list			*cmdlist;
	struct cmdq_item		*new_item;
	char				*cause, *cmd, *file = cdata->file;
	u_int				 line = cdata->line;
	int				 status;

	status = job_get_status(job);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		cmd = cdata->cmd_else;
	else
		cmd = cdata->cmd_if;
	if (cmd == NULL)
		goto out;

	cmdlist = cmd_string_parse(cmd, file, line, &cause);
	if (cmdlist == NULL) {
		if (cause != NULL && cdata->item != NULL)
			cmdq_error(cdata->item, "%s", cause);
		free(cause);
		new_item = NULL;
	} else {
		new_item = cmdq_get_command(cmdlist, NULL, &cdata->mouse, 0);
		cmd_list_free(cmdlist);
	}

	if (new_item != NULL) {
		if (cdata->item == NULL)
			cmdq_append(c, new_item);
		else
			cmdq_insert_after(cdata->item, new_item);
	}

out:
	if (cdata->item != NULL)
		cdata->item->flags &= ~CMDQ_WAITING;
}