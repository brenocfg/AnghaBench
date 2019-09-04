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
struct msg_command_data {int argc; } ;
struct TYPE_2__ {int len; } ;
struct imsg {TYPE_1__ hdr; scalar_t__ data; } ;
struct cmd_list {int dummy; } ;
struct client {int flags; } ;

/* Variables and functions */
 int CLIENT_EXIT ; 
 int /*<<< orphan*/  IMSG_HEADER_SIZE ; 
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_list_free (struct cmd_list*) ; 
 struct cmd_list* cmd_list_parse (int,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ cmd_unpack_argv (char*,size_t,int,char***) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_get_callback (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmdq_get_command (struct cmd_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  memcpy (struct msg_command_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  server_client_command_done ; 
 int /*<<< orphan*/  server_client_command_error ; 
 char** xcalloc (int,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
server_client_dispatch_command(struct client *c, struct imsg *imsg)
{
	struct msg_command_data	  data;
	char			 *buf;
	size_t			  len;
	struct cmd_list		 *cmdlist = NULL;
	int			  argc;
	char			**argv, *cause;

	if (c->flags & CLIENT_EXIT)
		return;

	if (imsg->hdr.len - IMSG_HEADER_SIZE < sizeof data)
		fatalx("bad MSG_COMMAND size");
	memcpy(&data, imsg->data, sizeof data);

	buf = (char *)imsg->data + sizeof data;
	len = imsg->hdr.len  - IMSG_HEADER_SIZE - sizeof data;
	if (len > 0 && buf[len - 1] != '\0')
		fatalx("bad MSG_COMMAND string");

	argc = data.argc;
	if (cmd_unpack_argv(buf, len, argc, &argv) != 0) {
		cause = xstrdup("command too long");
		goto error;
	}

	if (argc == 0) {
		argc = 1;
		argv = xcalloc(1, sizeof *argv);
		*argv = xstrdup("new-session");
	}

	if ((cmdlist = cmd_list_parse(argc, argv, NULL, 0, &cause)) == NULL) {
		cmd_free_argv(argc, argv);
		goto error;
	}
	cmd_free_argv(argc, argv);

	cmdq_append(c, cmdq_get_command(cmdlist, NULL, NULL, 0));
	cmdq_append(c, cmdq_get_callback(server_client_command_done, NULL));
	cmd_list_free(cmdlist);
	return;

error:
	cmdq_append(c, cmdq_get_callback(server_client_command_error, cause));

	if (cmdlist != NULL)
		cmd_list_free(cmdlist);

	c->flags |= CLIENT_EXIT;
}