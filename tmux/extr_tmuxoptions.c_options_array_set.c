#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct options_entry {TYPE_1__ value; } ;
struct TYPE_4__ {char* string; struct cmd_list* cmdlist; } ;
struct options_array_item {TYPE_2__ value; int /*<<< orphan*/  index; } ;
struct cmd_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONS_IS_ARRAY (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_COMMAND (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_STRING (struct options_entry*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_array_item*) ; 
 struct cmd_list* cmd_string_parse (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  options_array ; 
 int /*<<< orphan*/  options_array_free (struct options_entry*,struct options_array_item*) ; 
 struct options_array_item* options_array_item (struct options_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_value_free (struct options_entry*,TYPE_2__*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,char const*) ; 
 struct options_array_item* xcalloc (int,int) ; 
 char* xstrdup (char const*) ; 

int
options_array_set(struct options_entry *o, u_int idx, const char *value,
    int append, char **cause)
{
	struct options_array_item	*a;
	char				*new;
	struct cmd_list			*cmdlist;

	if (!OPTIONS_IS_ARRAY(o)) {
		*cause = xstrdup("not an array");
		return (-1);
	}

	if (OPTIONS_IS_COMMAND(o)) {
		cmdlist = cmd_string_parse(value, NULL, 0, cause);
		if (cmdlist == NULL && *cause != NULL)
			return (-1);
	}

	a = options_array_item(o, idx);
	if (value == NULL) {
		if (a != NULL)
			options_array_free(o, a);
		return (0);
	}

	if (OPTIONS_IS_STRING(o)) {
		if (a != NULL && append)
			xasprintf(&new, "%s%s", a->value.string, value);
		else
			new = xstrdup(value);
	}

	if (a == NULL) {
		a = xcalloc(1, sizeof *a);
		a->index = idx;
		RB_INSERT(options_array, &o->value.array, a);
	} else
		options_value_free(o, &a->value);

	if (OPTIONS_IS_STRING(o))
		a->value.string = new;
	else if (OPTIONS_IS_COMMAND(o))
		a->value.cmdlist = cmdlist;
	return (0);
}