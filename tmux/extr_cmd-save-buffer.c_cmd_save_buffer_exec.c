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
struct winlink {int dummy; } ;
struct window_pane {int dummy; } ;
struct session {int dummy; } ;
struct paste_buffer {int dummy; } ;
struct TYPE_2__ {struct window_pane* wp; struct winlink* wl; struct session* s; } ;
struct cmdq_item {struct client* client; TYPE_1__ target; } ;
struct cmd {struct args* args; int /*<<< orphan*/ * entry; } ;
struct client {int flags; int /*<<< orphan*/  stdout_data; int /*<<< orphan*/ * session; } ;
struct args {int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CLIENT_CONTROL ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int INT_MAX ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_show_buffer_entry ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  evbuffer_add (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char const*) ; 
 char* format_single (struct cmdq_item*,int /*<<< orphan*/ ,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 char* memchr (char const*,char,size_t) ; 
 char* paste_buffer_data (struct paste_buffer*,size_t*) ; 
 struct paste_buffer* paste_get_name (char const*) ; 
 struct paste_buffer* paste_get_top (int /*<<< orphan*/ *) ; 
 char* server_client_get_path (struct client*,char*) ; 
 int /*<<< orphan*/  server_client_push_stdout (struct client*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strvisx (char*,char const*,size_t,int) ; 
 char* xrealloc (char*,size_t) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_save_buffer_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct session		*s = item->target.s;
	struct winlink		*wl = item->target.wl;
	struct window_pane	*wp = item->target.wp;
	struct paste_buffer	*pb;
	const char		*bufname, *bufdata, *start, *end, *flags;
	char			*msg, *path, *file;
	size_t			 size, used, msglen, bufsize;
	FILE			*f;

	if (!args_has(args, 'b')) {
		if ((pb = paste_get_top(NULL)) == NULL) {
			cmdq_error(item, "no buffers");
			return (CMD_RETURN_ERROR);
		}
	} else {
		bufname = args_get(args, 'b');
		pb = paste_get_name(bufname);
		if (pb == NULL) {
			cmdq_error(item, "no buffer %s", bufname);
			return (CMD_RETURN_ERROR);
		}
	}
	bufdata = paste_buffer_data(pb, &bufsize);

	if (self->entry == &cmd_show_buffer_entry)
		path = xstrdup("-");
	else
		path = format_single(item, args->argv[0], c, s, wl, wp);
	if (strcmp(path, "-") == 0) {
		free(path);
		c = item->client;
		if (c == NULL) {
			cmdq_error(item, "can't write to stdout");
			return (CMD_RETURN_ERROR);
		}
		if (c->session == NULL || (c->flags & CLIENT_CONTROL))
			goto do_stdout;
		goto do_print;
	}

	flags = "wb";
	if (args_has(self->args, 'a'))
		flags = "ab";

	file = server_client_get_path(item->client, path);
	free(path);

	f = fopen(file, flags);
	if (f == NULL) {
		cmdq_error(item, "%s: %s", file, strerror(errno));
		free(file);
		return (CMD_RETURN_ERROR);
	}

	if (fwrite(bufdata, 1, bufsize, f) != bufsize) {
		cmdq_error(item, "%s: write error", file);
		fclose(f);
		free(file);
		return (CMD_RETURN_ERROR);
	}

	fclose(f);
	free(file);

	return (CMD_RETURN_NORMAL);

do_stdout:
	evbuffer_add(c->stdout_data, bufdata, bufsize);
	server_client_push_stdout(c);
	return (CMD_RETURN_NORMAL);

do_print:
	if (bufsize > (INT_MAX / 4) - 1) {
		cmdq_error(item, "buffer too big");
		return (CMD_RETURN_ERROR);
	}
	msg = NULL;

	used = 0;
	while (used != bufsize) {
		start = bufdata + used;
		end = memchr(start, '\n', bufsize - used);
		if (end != NULL)
			size = end - start;
		else
			size = bufsize - used;

		msglen = size * 4 + 1;
		msg = xrealloc(msg, msglen);

		strvisx(msg, start, size, VIS_OCTAL|VIS_TAB);
		cmdq_print(item, "%s", msg);

		used += size + (end != NULL);
	}

	free(msg);
	return (CMD_RETURN_NORMAL);
}