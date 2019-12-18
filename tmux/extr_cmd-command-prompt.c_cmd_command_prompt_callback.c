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
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;
struct cmd_command_prompt_cdata {int flags; char* template; int /*<<< orphan*/  idx; int /*<<< orphan*/  next_input; int /*<<< orphan*/  next_prompt; } ;
struct client {scalar_t__ prompt_inputcb; } ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int PROMPT_INCREMENTAL ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 struct cmd_parse_result* cmd_parse_from_string (char*,int /*<<< orphan*/ *) ; 
 char* cmd_template_replace (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,struct cmdq_item*) ; 
 struct cmdq_item* cmdq_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cmdq_item* cmdq_get_error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_prompt_update (struct client*,char*,char*) ; 
 char* strsep (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 

__attribute__((used)) static int
cmd_command_prompt_callback(struct client *c, void *data, const char *s,
    int done)
{
	struct cmd_command_prompt_cdata	*cdata = data;
	struct cmdq_item		*new_item;
	char				*new_template, *prompt, *ptr;
	char				*input = NULL;
	struct cmd_parse_result		*pr;

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

	pr = cmd_parse_from_string(new_template, NULL);
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

	if (!done)
		free(new_template);
	if (c->prompt_inputcb != cmd_command_prompt_callback)
		return (1);
	return (0);
}