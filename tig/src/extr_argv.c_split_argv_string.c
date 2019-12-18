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
 int SIZEOF_ARG ; 
 char* parse_arg (char**,int) ; 
 char* string_trim (char*) ; 

__attribute__((used)) static bool
split_argv_string(const char *argv[SIZEOF_ARG], int *argc, char *cmd, bool remove_quotes)
{
	while (*cmd && *argc < SIZEOF_ARG) {
		char *arg = parse_arg(&cmd, remove_quotes);

		if (!arg)
			break;
		argv[(*argc)++] = arg;
		cmd = string_trim(cmd);
	}

	if (*argc < SIZEOF_ARG)
		argv[*argc] = NULL;
	return *argc < SIZEOF_ARG;
}