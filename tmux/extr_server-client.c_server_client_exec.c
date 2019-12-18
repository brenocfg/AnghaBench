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
struct session {int /*<<< orphan*/  options; } ;
struct client {int /*<<< orphan*/  peer; struct session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_EXEC ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_s_options ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,size_t) ; 
 int strlen (char const*) ; 
 char* xmalloc (size_t) ; 

void
server_client_exec(struct client *c, const char *cmd)
{
	struct session	*s = c->session;
	char		*msg;
	const char	*shell;
	size_t		 cmdsize, shellsize;

	if (*cmd == '\0')
		return;
	cmdsize = strlen(cmd) + 1;

	if (s != NULL)
		shell = options_get_string(s->options, "default-shell");
	else
		shell = options_get_string(global_s_options, "default-shell");
	shellsize = strlen(shell) + 1;

	msg = xmalloc(cmdsize + shellsize);
	memcpy(msg, cmd, cmdsize);
	memcpy(msg + cmdsize, shell, shellsize);

	proc_send(c->peer, MSG_EXEC, -1, msg, cmdsize + shellsize);
	free(msg);
}