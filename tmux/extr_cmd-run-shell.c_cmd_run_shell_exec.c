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
struct winlink {int dummy; } ;
struct window_pane {int id; } ;
struct session {int dummy; } ;
struct TYPE_2__ {struct window_pane* wp; struct winlink* wl; struct session* s; } ;
struct cmdq_item {int /*<<< orphan*/  client; TYPE_1__ target; } ;
struct cmd_run_shell_data {int wp_id; int /*<<< orphan*/  cmd; struct cmdq_item* item; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int CMD_RETURN_WAIT ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_run_shell_callback ; 
 int /*<<< orphan*/  cmd_run_shell_free ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (struct cmd_run_shell_data*) ; 
 int /*<<< orphan*/ * job_run (int /*<<< orphan*/ ,struct session*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_run_shell_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_client_get_cwd (int /*<<< orphan*/ ,struct session*) ; 
 struct cmd_run_shell_data* xcalloc (int,int) ; 

__attribute__((used)) static enum cmd_retval
cmd_run_shell_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	struct cmd_run_shell_data	*cdata;
	struct client			*c = cmd_find_client(item, NULL, 1);
	struct session			*s = item->target.s;
	struct winlink			*wl = item->target.wl;
	struct window_pane		*wp = item->target.wp;

	cdata = xcalloc(1, sizeof *cdata);
	cdata->cmd = format_single(item, args->argv[0], c, s, wl, wp);

	if (args_has(args, 't') && wp != NULL)
		cdata->wp_id = wp->id;
	else
		cdata->wp_id = -1;

	if (!args_has(args, 'b'))
		cdata->item = item;

	if (job_run(cdata->cmd, s, server_client_get_cwd(item->client, s), NULL,
	    cmd_run_shell_callback, cmd_run_shell_free, cdata, 0) == NULL) {
		cmdq_error(item, "failed to run command: %s", cdata->cmd);
		free(cdata);
		return (CMD_RETURN_ERROR);
	}

	if (args_has(args, 'b'))
		return (CMD_RETURN_NORMAL);
	return (CMD_RETURN_WAIT);
}