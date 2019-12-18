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
struct cmd {int /*<<< orphan*/  args; struct cmd* file; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; struct cmd* alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  args_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_free_argv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cmd*) ; 

void
cmd_free(struct cmd *cmd)
{
	free(cmd->alias);
	cmd_free_argv(cmd->argc, cmd->argv);

	free(cmd->file);

	args_free(cmd->args);
	free(cmd);
}