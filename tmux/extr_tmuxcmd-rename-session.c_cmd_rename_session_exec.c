#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct session {char* name; } ;
struct TYPE_2__ {struct session* s; } ;
struct cmdq_item {TYPE_1__ target; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 char* format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  notify_session (char*,struct session*) ; 
 int /*<<< orphan*/  server_status_session (struct session*) ; 
 int /*<<< orphan*/  session_check_name (char*) ; 
 int /*<<< orphan*/ * session_find (char*) ; 
 int /*<<< orphan*/  sessions ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_rename_session_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct session		*s = item->target.s;
	char			*newname;

	newname = format_single(item, args->argv[0], c, s, NULL, NULL);
	if (strcmp(newname, s->name) == 0) {
		free(newname);
		return (CMD_RETURN_NORMAL);
	}

	if (!session_check_name(newname)) {
		cmdq_error(item, "bad session name: %s", newname);
		free(newname);
		return (CMD_RETURN_ERROR);
	}
	if (session_find(newname) != NULL) {
		cmdq_error(item, "duplicate session: %s", newname);
		free(newname);
		return (CMD_RETURN_ERROR);
	}

	RB_REMOVE(sessions, &sessions, s);
	free(s->name);
	s->name = newname;
	RB_INSERT(sessions, &sessions, s);

	server_status_session(s);
	notify_session("session-renamed", s);

	return (CMD_RETURN_NORMAL);
}