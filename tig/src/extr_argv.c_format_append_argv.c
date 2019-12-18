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
struct format_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_append_arg (struct format_context*,char const***,char const*) ; 

__attribute__((used)) static bool
format_append_argv(struct format_context *format, const char ***dst_argv, const char *src_argv[])
{
	int argc;

	if (!src_argv)
		return true;

	for (argc = 0; src_argv[argc]; argc++)
		if (!format_append_arg(format, dst_argv, src_argv[argc]))
			return false;

	return src_argv[argc] == NULL;
}