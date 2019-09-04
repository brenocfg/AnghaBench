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
struct cmd_if_shell_data {struct cmd_if_shell_data* file; struct cmd_if_shell_data* cmd_if; struct cmd_if_shell_data* cmd_else; int /*<<< orphan*/ * client; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cmd_if_shell_data*) ; 
 int /*<<< orphan*/  server_client_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cmd_if_shell_free(void *data)
{
	struct cmd_if_shell_data	*cdata = data;

	if (cdata->client != NULL)
		server_client_unref(cdata->client);

	free(cdata->cmd_else);
	free(cdata->cmd_if);

	free(cdata->file);
	free(cdata);
}