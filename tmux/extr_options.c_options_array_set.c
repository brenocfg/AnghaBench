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
typedef  int /*<<< orphan*/  u_int ;
struct options_entry {int dummy; } ;
struct TYPE_2__ {char* string; int /*<<< orphan*/  cmdlist; } ;
struct options_array_item {TYPE_1__ value; } ;
struct cmd_parse_result {int status; char* error; int /*<<< orphan*/  cmdlist; } ;

/* Variables and functions */
#define  CMD_PARSE_EMPTY 130 
#define  CMD_PARSE_ERROR 129 
#define  CMD_PARSE_SUCCESS 128 
 int /*<<< orphan*/  OPTIONS_IS_ARRAY (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_COMMAND (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_STRING (struct options_entry*) ; 
 struct cmd_parse_result* cmd_parse_from_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  options_array_free (struct options_entry*,struct options_array_item*) ; 
 struct options_array_item* options_array_item (struct options_entry*,int /*<<< orphan*/ ) ; 
 struct options_array_item* options_array_new (struct options_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_value_free (struct options_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,char const*) ; 
 char* xstrdup (char const*) ; 

int
options_array_set(struct options_entry *o, u_int idx, const char *value,
    int append, char **cause)
{
	struct options_array_item	*a;
	char				*new;
	struct cmd_parse_result		*pr;

	if (!OPTIONS_IS_ARRAY(o)) {
		if (cause != NULL)
			*cause = xstrdup("not an array");
		return (-1);
	}

	if (value == NULL) {
		a = options_array_item(o, idx);
		if (a != NULL)
			options_array_free(o, a);
		return (0);
	}

	if (OPTIONS_IS_COMMAND(o)) {
		pr = cmd_parse_from_string(value, NULL);
		switch (pr->status) {
		case CMD_PARSE_EMPTY:
			if (cause != NULL)
				*cause = xstrdup("empty command");
			return (-1);
		case CMD_PARSE_ERROR:
			if (cause != NULL)
				*cause = pr->error;
			else
				free(pr->error);
			return (-1);
		case CMD_PARSE_SUCCESS:
			break;
		}

		a = options_array_item(o, idx);
		if (a == NULL)
			a = options_array_new(o, idx);
		else
			options_value_free(o, &a->value);
		a->value.cmdlist = pr->cmdlist;
		return (0);
	}

	if (OPTIONS_IS_STRING(o)) {
		a = options_array_item(o, idx);
		if (a != NULL && append)
			xasprintf(&new, "%s%s", a->value.string, value);
		else
			new = xstrdup(value);
		if (a == NULL)
			a = options_array_new(o, idx);
		else
			options_value_free(o, &a->value);
		a->value.string = new;
		return (0);
	}

	if (cause != NULL)
		*cause = xstrdup("wrong array type");
	return (-1);
}