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
struct options_table_entry {int type; int /*<<< orphan*/  name; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/ * pattern; } ;
struct options_entry {int dummy; } ;
struct options {int dummy; } ;
struct cmdq_item {int dummy; } ;
struct cmd {struct args* args; } ;
struct args {int dummy; } ;
typedef  long long key_code ;

/* Variables and functions */
 long long KEYC_UNKNOWN ; 
#define  OPTIONS_TABLE_CHOICE 135 
#define  OPTIONS_TABLE_COLOUR 134 
#define  OPTIONS_TABLE_COMMAND 133 
#define  OPTIONS_TABLE_FLAG 132 
#define  OPTIONS_TABLE_KEY 131 
#define  OPTIONS_TABLE_NUMBER 130 
#define  OPTIONS_TABLE_STRING 129 
#define  OPTIONS_TABLE_STYLE 128 
 int args_has (struct args*,char) ; 
 int cmd_set_option_choice (struct cmdq_item*,struct options_table_entry const*,struct options*,char const*) ; 
 int cmd_set_option_flag (struct cmdq_item*,struct options_table_entry const*,struct options*,char const*) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 long long colour_fromstring (char const*) ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 long long key_string_lookup_string (char const*) ; 
 char* options_get_string (struct options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_set_number (struct options*,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  options_set_string (struct options*,int /*<<< orphan*/ ,int,char*,char const*) ; 
 struct options_entry* options_set_style (struct options*,int /*<<< orphan*/ ,int,char const*) ; 
 struct options_table_entry* options_table_entry (struct options_entry*) ; 
 long long strtonum (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
cmd_set_option_set(struct cmd *self, struct cmdq_item *item, struct options *oo,
    struct options_entry *parent, const char *value)
{
	const struct options_table_entry	*oe;
	struct args				*args = self->args;
	int					 append = args_has(args, 'a');
	struct options_entry			*o;
	long long				 number;
	const char				*errstr, *new;
	char					*old;
	key_code				 key;

	oe = options_table_entry(parent);
	if (value == NULL &&
	    oe->type != OPTIONS_TABLE_FLAG &&
	    oe->type != OPTIONS_TABLE_CHOICE) {
		cmdq_error(item, "empty value");
		return (-1);
	}

	switch (oe->type) {
	case OPTIONS_TABLE_STRING:
		old = xstrdup(options_get_string(oo, oe->name));
		options_set_string(oo, oe->name, append, "%s", value);
		new = options_get_string(oo, oe->name);
		if (oe->pattern != NULL && fnmatch(oe->pattern, new, 0) != 0) {
			options_set_string(oo, oe->name, 0, "%s", old);
			free(old);
			cmdq_error(item, "value is invalid: %s", value);
			return (-1);
		}
		free(old);
		return (0);
	case OPTIONS_TABLE_NUMBER:
		number = strtonum(value, oe->minimum, oe->maximum, &errstr);
		if (errstr != NULL) {
			cmdq_error(item, "value is %s: %s", errstr, value);
			return (-1);
		}
		options_set_number(oo, oe->name, number);
		return (0);
	case OPTIONS_TABLE_KEY:
		key = key_string_lookup_string(value);
		if (key == KEYC_UNKNOWN) {
			cmdq_error(item, "bad key: %s", value);
			return (-1);
		}
		options_set_number(oo, oe->name, key);
		return (0);
	case OPTIONS_TABLE_COLOUR:
		if ((number = colour_fromstring(value)) == -1) {
			cmdq_error(item, "bad colour: %s", value);
			return (-1);
		}
		options_set_number(oo, oe->name, number);
		return (0);
	case OPTIONS_TABLE_FLAG:
		return (cmd_set_option_flag(item, oe, oo, value));
	case OPTIONS_TABLE_CHOICE:
		return (cmd_set_option_choice(item, oe, oo, value));
	case OPTIONS_TABLE_STYLE:
		o = options_set_style(oo, oe->name, append, value);
		if (o == NULL) {
			cmdq_error(item, "bad style: %s", value);
			return (-1);
		}
		return (0);
	case OPTIONS_TABLE_COMMAND:
		break;
	}
	return (-1);
}