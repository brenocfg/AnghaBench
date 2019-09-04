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
 int argv_append_array (scalar_t__*,char const**) ; 
 int /*<<< orphan*/  argv_free (scalar_t__) ; 
 int /*<<< orphan*/  argv_from_string_no_quotes (char const**,int*,char*) ; 
 scalar_t__ grep_argv ; 
 char* read_prompt (char*) ; 
 int /*<<< orphan*/  report_clear () ; 

__attribute__((used)) static bool
grep_prompt(void)
{
	const char *argv[SIZEOF_ARG];
	int argc = 0;
	char *grep = read_prompt("grep: ");

	report_clear();

	if (!grep || !*grep || !argv_from_string_no_quotes(argv, &argc, grep))
		return false;
	if (grep_argv)
		argv_free(grep_argv);
	return argv_append_array(&grep_argv, argv);
}