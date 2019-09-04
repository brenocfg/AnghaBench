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
struct cmdq_item {int dummy; } ;
struct cmd_list {int dummy; } ;
struct cmd_command_prompt_cdata {int flags; char* template; int /*<<< orphan*/  idx; int /*<<< orphan*/  next_input; int /*<<< orphan*/  next_prompt; } ;
struct client {scalar_t__ prompt_inputcb; } ;

/* Variables and functions */
 int PROMPT_INCREMENTAL ; 
 int /*<<< orphan*/  cmd_command_prompt_error ; 
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd_list* cmd_string_parse (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 char* cmd_template_replace (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_callback (int /*<<< orphan*/ ,char*) ; 
 struct cmdq_item* cmdq_get_command (struct cmd_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_prompt_update (struct client*,char*,char*) ; 
 char* strsep (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 

__attribute__((used)) static int
cmd_command_prompt_callback(struct client *c, void *data, const char *s,
    int done)
{
	struct cmd_command_prompt_cdata	*cdata = data;
	struct cmd_list			*cmdlist;
	struct cmdq_item		*new_item;
	char				*cause, *new_template, *prompt, *ptr;
	char				*input = NULL;

	if (s == NULL)
		return (0);
	if (done && (cdata->flags & PROMPT_INCREMENTAL))
		return (0);

	new_template = cmd_template_replace(cdata->template, s, cdata->idx);
	if (done) {
		free(cdata->template);
		cdata->template = new_template;
	}

	/*
	 * Check if there are more prompts; if so, get its respective input
	 * and update the prompt data.
	 */
	if (done && (ptr = strsep(&cdata->next_prompt, ",")) != NULL) {
		xasprintf(&prompt, "%s ", ptr);
		input = strsep(&cdata->next_input, ",");
		status_prompt_update(c, prompt, input);

		free(prompt);
		cdata->idx++;
		return (1);
	}

	cmdlist = cmd_string_parse(new_template, NULL, 0, &cause);
	if (cmdlist == NULL) {
		if (cause != NULL) {
			new_item = cmdq_get_callback(cmd_command_prompt_error,
			    cause);
		} else
			new_item = NULL;
	} else {
		new_item = cmdq_get_command(cmdlist, NULL, NULL, 0);
		cmd_list_free(cmdlist);
	}

	if (new_item != NULL)
		cmdq_append(c, new_item);

	if (!done)
		free(new_template);
	if (c->prompt_inputcb != cmd_command_prompt_callback)
		return (1);
	return (0);
}