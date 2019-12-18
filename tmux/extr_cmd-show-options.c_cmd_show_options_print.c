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
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;
struct cmdq_item {int dummy; } ;
struct cmd {int /*<<< orphan*/  args; } ;

/* Variables and functions */
 char* args_escape (char*) ; 
 scalar_t__ args_has (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 int options_array_item_index (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 scalar_t__ options_isarray (struct options_entry*) ; 
 scalar_t__ options_isstring (struct options_entry*) ; 
 char* options_name (struct options_entry*) ; 
 char* options_tostring (struct options_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,int) ; 

__attribute__((used)) static void
cmd_show_options_print(struct cmd *self, struct cmdq_item *item,
    struct options_entry *o, int idx, int parent)
{
	struct options_array_item	*a;
	const char			*name = options_name(o);
	char				*value, *tmp = NULL, *escaped;

	if (idx != -1) {
		xasprintf(&tmp, "%s[%d]", name, idx);
		name = tmp;
	} else {
		if (options_isarray(o)) {
			a = options_array_first(o);
			if (a == NULL) {
				if (!args_has(self->args, 'v'))
					cmdq_print(item, "%s", name);
				return;
			}
			while (a != NULL) {
				idx = options_array_item_index(a);
				cmd_show_options_print(self, item, o, idx,
				    parent);
				a = options_array_next(a);
			}
			return;
		}
	}

	value = options_tostring(o, idx, 0);
	if (args_has(self->args, 'v'))
		cmdq_print(item, "%s", value);
	else if (options_isstring(o)) {
		escaped = args_escape(value);
		if (parent)
			cmdq_print(item, "%s* %s", name, escaped);
		else
			cmdq_print(item, "%s %s", name, escaped);
		free(escaped);
	} else {
		if (parent)
			cmdq_print(item, "%s* %s", name, value);
		else
			cmdq_print(item, "%s %s", name, value);
	}
	free(value);

	free(tmp);
}