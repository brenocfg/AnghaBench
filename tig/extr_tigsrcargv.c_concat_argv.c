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

/* Variables and functions */
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  string_nformat (char*,size_t,size_t*,char*,...) ; 

__attribute__((used)) static bool
concat_argv(const char *argv[], char *buf, size_t buflen, const char *sep, bool quoted)
{
	size_t bufpos, argc;

	for (bufpos = 0, argc = 0; argv[argc]; argc++) {
		const char *arg_sep = argc ? sep : "";
		const char *arg = argv[argc];

		if (quoted && arg[strcspn(arg, " \t\"")]) {
			if (!string_nformat(buf, buflen, &bufpos, "%s\"", arg_sep))
				return false;

			while (*arg) {
				int pos = strcspn(arg, "\"");
				const char *qesc = arg[pos] == '"' ? "\\\"" : "";

				if (!string_nformat(buf, buflen, &bufpos, "%.*s%s", pos, arg, qesc))
					return false;
				if (!arg[pos])
					break;
				else
					arg += pos + 1;
			}

			if (!string_nformat(buf, buflen, &bufpos, "\""))
				return false;

			continue;
		}

		if (!string_nformat(buf, buflen, &bufpos, "%s%s", arg_sep, arg))
			return false;
	}

	return true;
}