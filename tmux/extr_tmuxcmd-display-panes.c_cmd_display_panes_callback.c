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
struct window_pane {int /*<<< orphan*/  id; } ;
struct cmdq_item {int dummy; } ;
struct cmd_list {int dummy; } ;
struct client {char* identify_callback_data; int /*<<< orphan*/ * identify_callback; TYPE_1__* identify_callback_item; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_WAITING ; 
 int /*<<< orphan*/  cmd_display_panes_error ; 
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd_list* cmd_string_parse (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 char* cmd_template_replace (char*,char*,int) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_callback (int /*<<< orphan*/ ,char*) ; 
 struct cmdq_item* cmdq_get_command (struct cmd_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_insert_after (TYPE_1__*,struct cmdq_item*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmd_display_panes_callback(struct client *c, struct window_pane *wp)
{
	struct cmd_list		*cmdlist;
	struct cmdq_item	*new_item;
	char			*cmd, *expanded, *cause;

	if (wp == NULL)
		goto out;

	xasprintf(&expanded, "%%%u", wp->id);
	cmd = cmd_template_replace(c->identify_callback_data, expanded, 1);

	cmdlist = cmd_string_parse(cmd, NULL, 0, &cause);
	if (cmdlist == NULL && cause != NULL)
		new_item = cmdq_get_callback(cmd_display_panes_error, cause);
	else if (cmdlist == NULL)
		new_item = NULL;
	else {
		new_item = cmdq_get_command(cmdlist, NULL, NULL, 0);
		cmd_list_free(cmdlist);
	}

	if (new_item != NULL) {
		if (c->identify_callback_item != NULL)
			cmdq_insert_after(c->identify_callback_item, new_item);
		else
			cmdq_append(c, new_item);
	}

	free(cmd);
	free(expanded);

out:
	if (c->identify_callback_item != NULL) {
		c->identify_callback_item->flags &= ~CMDQ_WAITING;
		c->identify_callback_item = NULL;
	}

	free(c->identify_callback_data);
	c->identify_callback_data = NULL;

	c->identify_callback = NULL;
}