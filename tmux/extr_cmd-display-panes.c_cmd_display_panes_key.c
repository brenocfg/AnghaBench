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
struct window_pane {int /*<<< orphan*/  id; } ;
struct window {int dummy; } ;
struct key_event {char key; } ;
struct cmdq_item {int dummy; } ;
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;
struct cmd_display_panes_data {int /*<<< orphan*/  command; } ;
struct client {TYPE_2__* session; struct cmd_display_panes_data* overlay_data; } ;
struct TYPE_4__ {TYPE_1__* curw; } ;
struct TYPE_3__ {struct window* window; } ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 struct cmd_parse_result* cmd_parse_from_string (char*,int /*<<< orphan*/ *) ; 
 char* cmd_template_replace (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cmdq_item* cmdq_get_error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct window_pane* window_pane_at_index (struct window*,char) ; 
 int /*<<< orphan*/  window_unzoom (struct window*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmd_display_panes_key(struct client *c, struct key_event *event)
{
	struct cmd_display_panes_data	*cdata = c->overlay_data;
	struct cmdq_item		*new_item;
	char				*cmd, *expanded;
	struct window			*w = c->session->curw->window;
	struct window_pane		*wp;
	struct cmd_parse_result		*pr;

	if (event->key < '0' || event->key > '9')
		return (-1);

	wp = window_pane_at_index(w, event->key - '0');
	if (wp == NULL)
		return (1);
	window_unzoom(w);

	xasprintf(&expanded, "%%%u", wp->id);
	cmd = cmd_template_replace(cdata->command, expanded, 1);

	pr = cmd_parse_from_string(cmd, NULL);
	switch (pr->status) {
	case CMD_PARSE_EMPTY:
		new_item = NULL;
		break;
	case CMD_PARSE_ERROR:
		new_item = cmdq_get_error(pr->error);
		free(pr->error);
		cmdq_append(c, new_item);
		break;
	case CMD_PARSE_SUCCESS:
		new_item = cmdq_get_command(pr->cmdlist, NULL, NULL, 0);
		cmd_list_free(pr->cmdlist);
		cmdq_append(c, new_item);
		break;
	}

	free(cmd);
	free(expanded);
	return (1);
}