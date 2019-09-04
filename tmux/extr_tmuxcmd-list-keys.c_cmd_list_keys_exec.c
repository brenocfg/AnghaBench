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
struct key_table {char const* name; } ;
struct key_binding {int flags; int /*<<< orphan*/  cmdlist; int /*<<< orphan*/  key; } ;
struct cmdq_item {int dummy; } ;
struct cmd {int /*<<< orphan*/ * entry; struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int BUFSIZ ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int KEY_BINDING_REPEAT ; 
 char* args_get (struct args*,char) ; 
 int /*<<< orphan*/  cmd_list_commands_entry ; 
 int cmd_list_keys_commands (struct cmd*,struct cmdq_item*) ; 
 char* cmd_list_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char const*) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct key_binding* key_bindings_first (struct key_table*) ; 
 struct key_table* key_bindings_first_table () ; 
 int /*<<< orphan*/ * key_bindings_get_table (char const*,int /*<<< orphan*/ ) ; 
 struct key_binding* key_bindings_next (struct key_table*,struct key_binding*) ; 
 struct key_table* key_bindings_next_table (struct key_table*) ; 
 char* key_string_lookup_key (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int utf8_cstrwidth (char const*) ; 
 char* utf8_padcstr (char const*,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static enum cmd_retval
cmd_list_keys_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct key_table	*table;
	struct key_binding	*bd;
	const char		*key, *tablename, *r;
	char			*cp, tmp[BUFSIZ];
	int			 repeat, width, tablewidth, keywidth;

	if (self->entry == &cmd_list_commands_entry)
		return (cmd_list_keys_commands(self, item));

	tablename = args_get(args, 'T');
	if (tablename != NULL && key_bindings_get_table(tablename, 0) == NULL) {
		cmdq_error(item, "table %s doesn't exist", tablename);
		return (CMD_RETURN_ERROR);
	}

	repeat = 0;
	tablewidth = keywidth = 0;
	table = key_bindings_first_table ();
	while (table != NULL) {
		if (tablename != NULL && strcmp(table->name, tablename) != 0) {
			table = key_bindings_next_table(table);
			continue;
		}
		bd = key_bindings_first(table);
		while (bd != NULL) {
			key = key_string_lookup_key(bd->key);

			if (bd->flags & KEY_BINDING_REPEAT)
				repeat = 1;

			width = utf8_cstrwidth(table->name);
			if (width > tablewidth)
				tablewidth = width;
			width = utf8_cstrwidth(key);
			if (width > keywidth)
				keywidth = width;

			bd = key_bindings_next(table, bd);
		}
		table = key_bindings_next_table(table);
	}

	table = key_bindings_first_table ();
	while (table != NULL) {
		if (tablename != NULL && strcmp(table->name, tablename) != 0) {
			table = key_bindings_next_table(table);
			continue;
		}
		bd = key_bindings_first(table);
		while (bd != NULL) {
			key = key_string_lookup_key(bd->key);

			if (!repeat)
				r = "";
			else if (bd->flags & KEY_BINDING_REPEAT)
				r = "-r ";
			else
				r = "   ";
			xsnprintf(tmp, sizeof tmp, "%s-T ", r);

			cp = utf8_padcstr(table->name, tablewidth);
			strlcat(tmp, cp, sizeof tmp);
			strlcat(tmp, " ", sizeof tmp);
			free(cp);

			cp = utf8_padcstr(key, keywidth);
			strlcat(tmp, cp, sizeof tmp);
			strlcat(tmp, " ", sizeof tmp);
			free(cp);

			cp = cmd_list_print(bd->cmdlist);
			strlcat(tmp, cp, sizeof tmp);
			free(cp);

			cmdq_print(item, "bind-key %s", tmp);
			bd = key_bindings_next(table, bd);
		}
		table = key_bindings_next_table(table);
	}

	return (CMD_RETURN_NORMAL);
}