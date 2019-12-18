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
struct format_tree {int dummy; } ;
struct cmdq_item {int /*<<< orphan*/  client; } ;
struct cmd_entry {char const* name; char* alias; char* usage; } ;
struct cmd {struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 char* args_get (struct args*,float) ; 
 struct cmd_entry** cmd_table ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,char const*) ; 
 struct format_tree* format_create (int /*<<< orphan*/ ,struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_list_keys_commands(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	const struct cmd_entry	**entryp;
	const struct cmd_entry	 *entry;
	struct format_tree	 *ft;
	const char		 *template, *s;
	char			 *line;

	if ((template = args_get(args, 'F')) == NULL) {
		template = "#{command_list_name}"
		    "#{?command_list_alias, (#{command_list_alias}),} "
		    "#{command_list_usage}";
	}

	ft = format_create(item->client, item, FORMAT_NONE, 0);
	format_defaults(ft, NULL, NULL, NULL, NULL);

	for (entryp = cmd_table; *entryp != NULL; entryp++) {
		entry = *entryp;

		format_add(ft, "command_list_name", "%s", entry->name);
		if (entry->alias != NULL)
			s = entry->alias;
		else
			s = "";
		format_add(ft, "command_list_alias", "%s", s);
		if (entry->usage != NULL)
			s = entry->usage;
		else
			s = "";
		format_add(ft, "command_list_usage", "%s", s);

		line = format_expand(ft, template);
		if (*line != '\0')
			cmdq_print(item, "%s", line);
		free(line);
	}

	format_free(ft);
	return (CMD_RETURN_NORMAL);
}