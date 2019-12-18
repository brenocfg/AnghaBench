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
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;
struct client {int flags; } ;

/* Variables and functions */
 int CLIENT_EXIT ; 
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int /*<<< orphan*/  IMSG_HEADER_SIZE ; 
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 struct cmd_parse_result* cmd_parse_from_arguments (int,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_unpack_argv (char*,size_t,int,char***) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_get_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_get_error (char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (struct msg_command_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  server_client_command_done ; 
 char** xcalloc (int,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
server_client_dispatch_command(struct client *c, struct imsg *imsg)
{
	struct msg_command_data	  data;
	char			 *buf;
	size_t			  len;
	int			  argc;
	char			**argv, *cause;
	struct cmd_parse_result	 *pr;

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

	pr = cmd_parse_from_arguments(argc, argv, NULL);
	switch (pr->status) {
	case CMD_PARSE_EMPTY:
		cause = xstrdup("empty command");
		goto error;
	case CMD_PARSE_ERROR:
		cause = pr->error;
		goto error;
	case CMD_PARSE_SUCCESS:
		break;
	}
	cmd_free_argv(argc, argv);

	cmdq_append(c, cmdq_get_command(pr->cmdlist, NULL, NULL, 0));
	cmdq_append(c, cmdq_get_callback(server_client_command_done, NULL));

	cmd_list_free(pr->cmdlist);
	return;

error:
	cmd_free_argv(argc, argv);

	cmdq_append(c, cmdq_get_error(cause));
	free(cause);

	c->flags |= CLIENT_EXIT;
}