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
struct format_var {char** value_ref; char* value_if_empty; } ;
struct format_context {int /*<<< orphan*/  bufpos; int /*<<< orphan*/  buf; } ;
typedef  char* argv_string ;

/* Variables and functions */
 int string_format_from (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static bool
argv_string_formatter(struct format_context *format, struct format_var *var)
{
	argv_string *value_ref = var->value_ref;
	const char *value = *value_ref;

	if (!*value)
		value = var->value_if_empty;

	if (!*value)
		return true;

	return string_format_from(format->buf, &format->bufpos, "%s", value);
}