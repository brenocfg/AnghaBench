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
struct format_context {int /*<<< orphan*/  buf; scalar_t__ bufpos; } ;

/* Variables and functions */
 int argv_append (char const***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_expand_arg (struct format_context*,char const*,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  string_format_from (int /*<<< orphan*/ ,scalar_t__*,char*,int const,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static bool
format_append_arg(struct format_context *format, const char ***dst_argv, const char *arg)
{
	memset(format->buf, 0, sizeof(format->buf));
	format->bufpos = 0;

	while (arg) {
		const char *var = strstr(arg, "%(");
		const char *closing = var ? strchr(var, ')') : NULL;
		const char *next = closing ? closing + 1 : NULL;
		const int len = var ? var - arg : strlen(arg);

		if (var && !closing)
			return false;

		if (len && !string_format_from(format->buf, &format->bufpos, "%.*s", len, arg))
			return false;

		if (var && !format_expand_arg(format, var, next))
			return false;

		arg = next;
	}

	return argv_append(dst_argv, format->buf);
}