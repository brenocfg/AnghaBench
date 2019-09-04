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
struct cmd_confirm_before_data {void* cmd; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  PROMPT_SINGLE ; 
 char* args_get (struct args*,char) ; 
 int /*<<< orphan*/  cmd_confirm_before_callback ; 
 int /*<<< orphan*/  cmd_confirm_before_free ; 
 struct client* cmd_find_client (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  status_prompt_set (struct client*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_confirm_before_data*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 
 struct cmd_confirm_before_data* xmalloc (int) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmd_confirm_before_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args			*args = self->args;
	struct cmd_confirm_before_data	*cdata;
	struct client			*c;
	char				*cmd, *copy, *new_prompt, *ptr;
	const char			*prompt;

	if ((c = cmd_find_client(item, args_get(args, 't'), 0)) == NULL)
		return (CMD_RETURN_ERROR);

	if ((prompt = args_get(args, 'p')) != NULL)
		xasprintf(&new_prompt, "%s ", prompt);
	else {
		ptr = copy = xstrdup(args->argv[0]);
		cmd = strsep(&ptr, " \t");
		xasprintf(&new_prompt, "Confirm '%s'? (y/n) ", cmd);
		free(copy);
	}

	cdata = xmalloc(sizeof *cdata);
	cdata->cmd = xstrdup(args->argv[0]);

	status_prompt_set(c, new_prompt, NULL,
	    cmd_confirm_before_callback, cmd_confirm_before_free, cdata,
	    PROMPT_SINGLE);

	free(new_prompt);
	return (CMD_RETURN_NORMAL);
}