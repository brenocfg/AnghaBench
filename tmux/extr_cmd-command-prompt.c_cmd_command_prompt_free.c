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
struct cmd_command_prompt_cdata {struct cmd_command_prompt_cdata* template; struct cmd_command_prompt_cdata* prompts; struct cmd_command_prompt_cdata* inputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cmd_command_prompt_cdata*) ; 

__attribute__((used)) static void
cmd_command_prompt_free(void *data)
{
	struct cmd_command_prompt_cdata	*cdata = data;

	free(cdata->inputs);
	free(cdata->prompts);
	free(cdata->template);
	free(cdata);
}