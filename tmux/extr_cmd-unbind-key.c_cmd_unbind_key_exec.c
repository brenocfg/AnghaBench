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
struct cmdq_item {int dummy; } ;
struct cmd {struct args* args; } ;
struct args {int argc; char const** argv; } ;
typedef  scalar_t__ key_code ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 scalar_t__ KEYC_NONE ; 
 scalar_t__ KEYC_UNKNOWN ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/ * key_bindings_get_table (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_bindings_remove (char const*,scalar_t__) ; 
 int /*<<< orphan*/  key_bindings_remove_table (char const*) ; 
 scalar_t__ key_string_lookup_string (char const*) ; 

__attribute__((used)) static enum cmd_retval
cmd_unbind_key_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	key_code	 key;
	const char	*tablename;

	if (!args_has(args, 'a')) {
		if (args->argc != 1) {
			cmdq_error(item, "missing key");
			return (CMD_RETURN_ERROR);
		}
		key = key_string_lookup_string(args->argv[0]);
		if (key == KEYC_NONE || key == KEYC_UNKNOWN) {
			cmdq_error(item, "unknown key: %s", args->argv[0]);
			return (CMD_RETURN_ERROR);
		}
	} else {
		if (args->argc != 0) {
			cmdq_error(item, "key given with -a");
			return (CMD_RETURN_ERROR);
		}
		key = KEYC_UNKNOWN;
	}

	if (key == KEYC_UNKNOWN) {
		tablename = args_get(args, 'T');
		if (tablename == NULL) {
			key_bindings_remove_table("root");
			key_bindings_remove_table("prefix");
			return (CMD_RETURN_NORMAL);
		}
		if (key_bindings_get_table(tablename, 0) == NULL) {
			cmdq_error(item, "table %s doesn't exist", tablename);
			return (CMD_RETURN_ERROR);
		}
		key_bindings_remove_table(tablename);
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'T')) {
		tablename = args_get(args, 'T');
		if (key_bindings_get_table(tablename, 0) == NULL) {
			cmdq_error(item, "table %s doesn't exist", tablename);
			return (CMD_RETURN_ERROR);
		}
	} else if (args_has(args, 'n'))
		tablename = "root";
	else
		tablename = "prefix";
	key_bindings_remove(tablename, key);
	return (CMD_RETURN_NORMAL);
}