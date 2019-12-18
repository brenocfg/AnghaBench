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
struct cmd_run_shell_data {struct cmd_run_shell_data* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cmd_run_shell_data*) ; 

__attribute__((used)) static void
cmd_run_shell_free(void *data)
{
	struct cmd_run_shell_data	*cdata = data;

	free(cdata->cmd);
	free(cdata);
}