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
struct mouse_event {int dummy; } ;
struct job {int dummy; } ;
struct cmdq_item {int dummy; } ;
struct cmd_parse_result {int status; int /*<<< orphan*/  cmdlist; int /*<<< orphan*/  error; } ;
struct cmd_if_shell_data {char* cmd_else; char* cmd_if; int /*<<< orphan*/ * item; int /*<<< orphan*/  input; struct mouse_event mouse; struct client* client; } ;
struct client {int dummy; } ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 struct cmd_parse_result* cmd_parse_from_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 int /*<<< orphan*/  cmdq_continue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct cmdq_item* cmdq_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mouse_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_insert_after (int /*<<< orphan*/ *,struct cmdq_item*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct cmd_if_shell_data* job_get_data (struct job*) ; 
 int job_get_status (struct job*) ; 

__attribute__((used)) static void
cmd_if_shell_callback(struct job *job)
{
	struct cmd_if_shell_data	*cdata = job_get_data(job);
	struct client			*c = cdata->client;
	struct mouse_event		*m = &cdata->mouse;
	struct cmdq_item		*new_item = NULL;
	char				*cmd;
	int				 status;
	struct cmd_parse_result		*pr;

	status = job_get_status(job);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		cmd = cdata->cmd_else;
	else
		cmd = cdata->cmd_if;
	if (cmd == NULL)
		goto out;

	pr = cmd_parse_from_string(cmd, &cdata->input);
	switch (pr->status) {
	case CMD_PARSE_EMPTY:
		break;
	case CMD_PARSE_ERROR:
		if (cdata->item != NULL)
		       cmdq_error(cdata->item, "%s", pr->error);
		free(pr->error);
		break;
	case CMD_PARSE_SUCCESS:
		new_item = cmdq_get_command(pr->cmdlist, NULL, m, 0);
		cmd_list_free(pr->cmdlist);
		break;
	}
	if (new_item != NULL) {
		if (cdata->item == NULL)
			cmdq_append(c, new_item);
		else
			cmdq_insert_after(cdata->item, new_item);
	}

out:
	if (cdata->item != NULL)
		cmdq_continue(cdata->item);
}