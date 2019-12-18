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
typedef  int /*<<< orphan*/  u_char ;
struct cmdq_item {int dummy; } ;
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;
struct cmd_find_state {int dummy; } ;
struct client {int dummy; } ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 struct cmd_parse_result* cmd_parse_from_string (char*,int /*<<< orphan*/ *) ; 
 char* cmd_template_replace (char const*,char const*,int) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_command (int /*<<< orphan*/ ,struct cmd_find_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_message_set (struct client*,char*,char*) ; 
 char toupper (int /*<<< orphan*/ ) ; 

void
mode_tree_run_command(struct client *c, struct cmd_find_state *fs,
    const char *template, const char *name)
{
	struct cmdq_item	*new_item;
	char			*command;
	struct cmd_parse_result	*pr;

	command = cmd_template_replace(template, name, 1);
	if (command == NULL || *command == '\0') {
		free(command);
		return;
	}

	pr = cmd_parse_from_string(command, NULL);
	switch (pr->status) {
	case CMD_PARSE_EMPTY:
		break;
	case CMD_PARSE_ERROR:
		if (c != NULL) {
			*pr->error = toupper((u_char)*pr->error);
			status_message_set(c, "%s", pr->error);
		}
		free(pr->error);
		break;
	case CMD_PARSE_SUCCESS:
		new_item = cmdq_get_command(pr->cmdlist, fs, NULL, 0);
		cmdq_append(c, new_item);
		cmd_list_free(pr->cmdlist);
		break;
	}

	free(command);
}