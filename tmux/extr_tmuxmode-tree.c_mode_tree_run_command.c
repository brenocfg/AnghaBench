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
struct cmd_list {int dummy; } ;
struct cmd_find_state {int dummy; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd_list* cmd_string_parse (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 char* cmd_template_replace (char const*,char const*,int) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_command (struct cmd_list*,struct cmd_find_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_message_set (struct client*,char*,char*) ; 
 char toupper (int /*<<< orphan*/ ) ; 

void
mode_tree_run_command(struct client *c, struct cmd_find_state *fs,
    const char *template, const char *name)
{
	struct cmdq_item	*new_item;
	struct cmd_list		*cmdlist;
	char			*command, *cause;

	command = cmd_template_replace(template, name, 1);
	if (command == NULL || *command == '\0') {
		free(command);
		return;
	}

	cmdlist = cmd_string_parse(command, NULL, 0, &cause);
	if (cmdlist == NULL) {
		if (cause != NULL && c != NULL) {
			*cause = toupper((u_char)*cause);
			status_message_set(c, "%s", cause);
		}
		free(cause);
	} else {
		new_item = cmdq_get_command(cmdlist, fs, NULL, 0);
		cmdq_append(c, new_item);
		cmd_list_free(cmdlist);
	}

	free(command);
}