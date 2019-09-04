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
struct format_var {int (* formatter ) (struct format_context*,struct format_var*) ;int /*<<< orphan*/ * value_ref; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct format_context {int vars_size; int /*<<< orphan*/  file_filter; int /*<<< orphan*/  bufpos; int /*<<< orphan*/  buf; struct format_var* vars; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int SIZEOF_STR ; 
 int STRING_SIZE (char*) ; 
 TYPE_1__ argv_env ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 char* read_prompt (char const*) ; 
 scalar_t__ string_enum_compare (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_format (char*,char*,int const,char const*) ; 
 int string_format_from (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int stub1 (struct format_context*,struct format_var*) ; 

__attribute__((used)) static bool
format_expand_arg(struct format_context *format, const char *name, const char *end)
{
	struct format_var *vars = format->vars;
	int i;

	if (!prefixcmp(name, "%(prompt")) {
		const char *prompt = "Command argument: ";
		char msgbuf[SIZEOF_STR];
		const char *value;
		const char *msgstart = name + STRING_SIZE("%(prompt");
		const int msglen = end - msgstart - 1;

		if (end && msglen > 0 && string_format(msgbuf, "%.*s", msglen, msgstart)) {
			const char *msg = msgbuf;

			while (isspace(*msg))
				msg++;
			if (*msg)
				prompt = msg;
		}

		value = read_prompt(prompt);
		if (value == NULL)
			return false;
		return string_format_from(format->buf, &format->bufpos, "%s", value);
	}

	for (i = 0; i < format->vars_size; i++) {
		if (string_enum_compare(name, vars[i].name, vars[i].namelen))
			continue;

		if (vars[i].value_ref == &argv_env.file && !format->file_filter)
			return true;

		return vars[i].formatter(format, &vars[i]);
	}

	return false;
}