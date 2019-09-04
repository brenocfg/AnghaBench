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
struct paste_buffer {int dummy; } ;
struct format_tree {int dummy; } ;
struct cmdq_item {int /*<<< orphan*/  client; } ;
struct cmd {struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 char* LIST_BUFFERS_TEMPLATE ; 
 char* args_get (struct args*,float) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 struct format_tree* format_create (int /*<<< orphan*/ ,struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults_paste_buffer (struct format_tree*,struct paste_buffer*) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct paste_buffer* paste_walk (struct paste_buffer*) ; 

__attribute__((used)) static enum cmd_retval
cmd_list_buffers_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct paste_buffer	*pb;
	struct format_tree	*ft;
	char			*line;
	const char		*template;

	if ((template = args_get(args, 'F')) == NULL)
		template = LIST_BUFFERS_TEMPLATE;

	pb = NULL;
	while ((pb = paste_walk(pb)) != NULL) {
		ft = format_create(item->client, item, FORMAT_NONE, 0);
		format_defaults_paste_buffer(ft, pb);

		line = format_expand(ft, template);
		cmdq_print(item, "%s", line);
		free(line);

		format_free(ft);
	}

	return (CMD_RETURN_NORMAL);
}