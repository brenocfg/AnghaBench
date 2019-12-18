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
typedef  int /*<<< orphan*/  u_int ;
struct session {int /*<<< orphan*/  options; } ;
struct cmdq_item {int dummy; } ;
struct cmd_display_panes_data {struct cmdq_item* item; void* command; } ;
struct cmd {struct args* args; } ;
struct client {int /*<<< orphan*/ * overlay_draw; struct session* session; } ;
struct args {scalar_t__ argc; char** argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int CMD_RETURN_WAIT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  args_strtonum (struct args*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  cmd_display_panes_draw ; 
 int /*<<< orphan*/  cmd_display_panes_free ; 
 int /*<<< orphan*/  cmd_display_panes_key ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_client_set_overlay (struct client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_display_panes_data*) ; 
 struct cmd_display_panes_data* xmalloc (int) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_display_panes_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	struct client			*c;
	struct session			*s;
	u_int		 		 delay;
	char				*cause;
	struct cmd_display_panes_data	*cdata;

	if ((c = cmd_find_client(item, args_get(args, 't'), 0)) == NULL)
		return (CMD_RETURN_ERROR);
	s = c->session;

	if (c->overlay_draw != NULL)
		return (CMD_RETURN_NORMAL);

	if (args_has(args, 'd')) {
		delay = args_strtonum(args, 'd', 0, UINT_MAX, &cause);
		if (cause != NULL) {
			cmdq_error(item, "delay %s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
	} else
		delay = options_get_number(s->options, "display-panes-time");

	cdata = xmalloc(sizeof *cdata);
	if (args->argc != 0)
		cdata->command = xstrdup(args->argv[0]);
	else
		cdata->command = xstrdup("select-pane -t '%%'");
	if (args_has(args, 'b'))
		cdata->item = NULL;
	else
		cdata->item = item;

	server_client_set_overlay(c, delay, cmd_display_panes_draw,
	    cmd_display_panes_key, cmd_display_panes_free, cdata);

	if (args_has(args, 'b'))
		return (CMD_RETURN_NORMAL);
	return (CMD_RETURN_WAIT);
}