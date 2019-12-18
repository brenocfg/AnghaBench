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
struct job {int dummy; } ;
struct cmd_run_shell_data {char* cmd; int /*<<< orphan*/ * item; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_DATA (int /*<<< orphan*/ ) ; 
 size_t EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  cmd_run_shell_print (struct job*,char*) ; 
 int /*<<< orphan*/  cmdq_continue (int /*<<< orphan*/ *) ; 
 char* evbuffer_readline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct cmd_run_shell_data* job_get_data (struct job*) ; 
 struct bufferevent* job_get_event (struct job*) ; 
 int job_get_status (struct job*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,int) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
cmd_run_shell_callback(struct job *job)
{
	struct cmd_run_shell_data	*cdata = job_get_data(job);
	struct bufferevent		*event = job_get_event(job);
	char				*cmd = cdata->cmd, *msg = NULL, *line;
	size_t				 size;
	int				 retcode, status;

	do {
		if ((line = evbuffer_readline(event->input)) != NULL) {
			cmd_run_shell_print(job, line);
			free(line);
		}
	} while (line != NULL);

	size = EVBUFFER_LENGTH(event->input);
	if (size != 0) {
		line = xmalloc(size + 1);
		memcpy(line, EVBUFFER_DATA(event->input), size);
		line[size] = '\0';

		cmd_run_shell_print(job, line);

		free(line);
	}

	status = job_get_status(job);
	if (WIFEXITED(status)) {
		if ((retcode = WEXITSTATUS(status)) != 0)
			xasprintf(&msg, "'%s' returned %d", cmd, retcode);
	} else if (WIFSIGNALED(status)) {
		retcode = WTERMSIG(status);
		xasprintf(&msg, "'%s' terminated by signal %d", cmd, retcode);
	}
	if (msg != NULL)
		cmd_run_shell_print(job, msg);
	free(msg);

	if (cdata->item != NULL)
		cmdq_continue(cdata->item);
}