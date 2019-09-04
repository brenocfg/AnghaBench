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
struct cmd_command_prompt_cdata {int idx; int /*<<< orphan*/  flags; int /*<<< orphan*/ * next_input; int /*<<< orphan*/ * inputs; int /*<<< orphan*/ * next_prompt; int /*<<< orphan*/ * prompts; int /*<<< orphan*/ * template; } ;
struct cmd {struct args* args; } ;
struct client {int /*<<< orphan*/ * prompt_string; } ;
struct args {scalar_t__ argc; char const** argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  PROMPT_INCREMENTAL ; 
 int /*<<< orphan*/  PROMPT_NUMERIC ; 
 int /*<<< orphan*/  PROMPT_SINGLE ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  cmd_command_prompt_callback ; 
 int /*<<< orphan*/  cmd_command_prompt_free ; 
 struct client* cmd_find_client (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_prompt_set (struct client*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_command_prompt_cdata*,int /*<<< orphan*/ ) ; 
 size_t strcspn (int /*<<< orphan*/ *,char*) ; 
 char* strsep (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,...) ; 
 struct cmd_command_prompt_cdata* xcalloc (int,int) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static enum cmd_retval
cmd_command_prompt_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	const char			*inputs, *prompts;
	struct cmd_command_prompt_cdata	*cdata;
	struct client			*c;
	char				*prompt, *ptr, *input = NULL;
	size_t				 n;

	if ((c = cmd_find_client(item, args_get(args, 't'), 0)) == NULL)
		return (CMD_RETURN_ERROR);

	if (c->prompt_string != NULL)
		return (CMD_RETURN_NORMAL);

	cdata = xcalloc(1, sizeof *cdata);

	cdata->inputs = NULL;
	cdata->next_input = NULL;

	cdata->prompts = NULL;
	cdata->next_prompt = NULL;

	cdata->template = NULL;
	cdata->idx = 1;

	if (args->argc != 0)
		cdata->template = xstrdup(args->argv[0]);
	else
		cdata->template = xstrdup("%1");

	if ((prompts = args_get(args, 'p')) != NULL)
		cdata->prompts = xstrdup(prompts);
	else if (args->argc != 0) {
		n = strcspn(cdata->template, " ,");
		xasprintf(&cdata->prompts, "(%.*s) ", (int) n, cdata->template);
	} else
		cdata->prompts = xstrdup(":");

	/* Get first prompt. */
	cdata->next_prompt = cdata->prompts;
	ptr = strsep(&cdata->next_prompt, ",");
	if (prompts == NULL)
		prompt = xstrdup(ptr);
	else
		xasprintf(&prompt, "%s ", ptr);

	/* Get initial prompt input. */
	if ((inputs = args_get(args, 'I')) != NULL) {
		cdata->inputs = xstrdup(inputs);
		cdata->next_input = cdata->inputs;
		input = strsep(&cdata->next_input, ",");
	}

	if (args_has(args, '1'))
		cdata->flags |= PROMPT_SINGLE;
	else if (args_has(args, 'N'))
		cdata->flags |= PROMPT_NUMERIC;
	else if (args_has(args, 'i'))
		cdata->flags |= PROMPT_INCREMENTAL;
	status_prompt_set(c, prompt, input, cmd_command_prompt_callback,
	    cmd_command_prompt_free, cdata, cdata->flags);
	free(prompt);

	return (CMD_RETURN_NORMAL);
}