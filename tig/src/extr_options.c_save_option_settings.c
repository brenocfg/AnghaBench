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
struct option_info {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (struct option_info*) ; 
 int SIZEOF_STR ; 
 char* enum_name (int /*<<< orphan*/ ) ; 
 char* format_option_value (struct option_info*,char*,int) ; 
 int /*<<< orphan*/  io_fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 struct option_info* option_info ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  suffixcmp (char const*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
save_option_settings(FILE *file)
{
	char buf[SIZEOF_STR];
	int i;

	if (!io_fprintf(file, "%s", "\n## Settings\n"))
		return false;

	for (i = 0; i < ARRAY_SIZE(option_info); i++) {
		struct option_info *option = &option_info[i];
		const char *name = enum_name(option->name);
		const char *value = format_option_value(option, buf, sizeof(buf));

		if (!value)
			return false;

		if (!suffixcmp(name, strlen(name), "-args"))
			continue;

		if (!io_fprintf(file, "\nset %-25s = %s", name, value))
			return false;
	}

	return true;
}