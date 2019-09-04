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
typedef  int u_int ;
struct options_table_entry {int flags; } ;
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;
struct options {int dummy; } ;
struct cmdq_item {int dummy; } ;
struct cmd {int /*<<< orphan*/  args; int /*<<< orphan*/ * entry; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_NORMAL ; 
 int OPTIONS_TABLE_IS_HOOK ; 
 int /*<<< orphan*/  args_has (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  cmd_show_hooks_entry ; 
 int /*<<< orphan*/  cmd_show_options_print (struct cmd*,struct cmdq_item*,struct options_entry*,int) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 int options_array_item_index (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 struct options_entry* options_first (struct options*) ; 
 int /*<<< orphan*/  options_isarray (struct options_entry*) ; 
 int /*<<< orphan*/  options_name (struct options_entry*) ; 
 struct options_entry* options_next (struct options_entry*) ; 
 struct options_table_entry* options_table_entry (struct options_entry*) ; 

__attribute__((used)) static enum cmd_retval
cmd_show_options_all(struct cmd *self, struct cmdq_item *item,
    struct options *oo)
{
	struct options_entry			*o;
	struct options_array_item		*a;
	u_int					 idx;
	const struct options_table_entry	*oe;

	o = options_first(oo);
	while (o != NULL) {
		oe = options_table_entry(o);
		if ((self->entry != &cmd_show_hooks_entry &&
		    !args_has(self->args, 'H') &&
		    oe != NULL &&
		    (oe->flags & OPTIONS_TABLE_IS_HOOK)) ||
		    (self->entry == &cmd_show_hooks_entry &&
		    (oe == NULL ||
		    (~oe->flags & OPTIONS_TABLE_IS_HOOK)))) {
			o = options_next(o);
			continue;
		}
		if (!options_isarray(o))
			cmd_show_options_print(self, item, o, -1);
		else if ((a = options_array_first(o)) == NULL) {
			if (!args_has(self->args, 'v'))
				cmdq_print(item, "%s", options_name(o));
		} else {
			while (a != NULL) {
				idx = options_array_item_index(a);
				cmd_show_options_print(self, item, o, idx);
				a = options_array_next(a);
			}
		}
		o = options_next(o);
	}
	return (CMD_RETURN_NORMAL);
}